/*
CS3100
Tanner Olsen
A01239510
Assignment 7

*/

#include <iostream>
#include <queue>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

//function prototypes
int generateCPUIO();
float generateNormalRandom(double, double);
float generateInitialTaskTime(float, float);
bool generateBoundType();
void runTrueSimulation(int, int, float, float, double);
void RoundRobin(int, int, float, float, double, float);
void ShortestJobFirst(int, int, float, float, double);
void ApproximateSJF(int, int, float, float, double);
std::vector<bool> createDevices(int);

//global variables
static int idleCPU;
static int numIO;
static double taskMixG;
static float latencySize = 0;
static float latencySum = 0;

static std::vector<float> fl;
static std::vector<float> fu;
static std::vector<float> fr;
static std::vector<float> ft;

//The functions from the previous assignment to time the function
template <typename S>
double deviation(S const & s){
	double sum = std::accumulate(std::begin(s), std::end(s), 0.0);
	double m = sum / s.size();
	double accum = 0.0;

	std::for_each(std::begin(s), std::end(s), [&](const double d){
		accum += (d - m) * (d - m);
	});

	double stdev = sqrt(accum / (s.size() - 1));
	std::cout << "Standard Deviation is: " << stdev << std::endl;

	return stdev;
}

template <typename M>
double mean(M const & m){
	double sum = std::accumulate(std::begin(m), std::end(m), 0.0);
	double mean = sum / m.size();

	std::cout << "The mean is: " << mean << std::endl;
	return mean;
}

std::vector<bool> createDevices(int numDevices){
	std::vector<bool> deviceNumber(numDevices);
	for (int i = 0; i < numDevices; i++){
		deviceNumber[i] = true;
	}
	return deviceNumber;
}

//Generation functions
int generateCPUIO(){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> random(1, 2);
	return random(mt);
}

int generateIODeviceNumber(int max){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> random(1, max);
	return random(mt);
}

float generateCPUIOTime(){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> random(1, 2);
	return random(mt);
}

float generateInitialTaskTime(float mean, float stddev){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::normal_distribution<float> random(mean, stddev);
	return random(mt);
}

bool generateBoundType(){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> die(1, 100);
	if (die(mt) < taskMixG)
		return true;
	else
		return false;
}

//Class and Struct declarations
class Event{
public:
	float startTime;
	float endTime;
	float latency;
	float response;
	float remainTime = 0;
	bool burst = false;
	float key = 0;
};


class Task : public Event{
public:
	char boundType;
	int CPUIOListIterator;
	struct CPUIO{
		CPUIO(char);
		CPUIO();
		int ioDeviceNumber;
		float CPUtime;
		float ioDeviceTime;
	};
	int numCPUs;
	int numIOs;
	std::vector<CPUIO> CPUIOlist;
	Task(float);
};

struct CompStr {
	bool operator() (const Task* lhs, const Task* rhs)const {
		float first = lhs->startTime;
		float second = rhs->startTime;
		if (first < second)
			return false;
		else
			return true;
	};
};

struct CompStrApprox {
	bool operator() (const Task* lhs, const Task* rhs)const {
		return lhs->key < rhs->key;
		/*float first = lhs->key;
		float second = rhs->key;
		if (first < second)
			return false;
		else
			return true;*/
	};
};

//Class and Struct function definitions
Task::CPUIO::CPUIO(char type){
	//This constructor will randomly generate the device numbers and times for both CPU and devices.
	switch (type){
	case 'c':
		ioDeviceNumber = generateIODeviceNumber(numIO);
		CPUtime = 2 * generateCPUIOTime();
		ioDeviceTime = generateCPUIOTime();
		break;
	case 'i':
		ioDeviceNumber = generateIODeviceNumber(numIO);
		CPUtime = generateCPUIOTime();
		ioDeviceTime = 2 * generateCPUIOTime();
		break;
	default:
		ioDeviceNumber = generateIODeviceNumber(numIO);
		CPUtime = generateCPUIOTime();
		ioDeviceTime = generateCPUIOTime();
		break;
	}
}

Task::CPUIO::CPUIO(){}

Task::Task(float time){
	CPUIOListIterator = 0;

	startTime = time;
	//randomly generates the type of bound for the task
	if (generateBoundType())
		boundType = 'c';
	else
		boundType = 'i';

	int i = 1;
	//count represents the number of CPU processes to do (IO is CPU-1)
	int count = 1;
	//it goes until i is an even number, which means that it can stop.
	while (i != 0){
		i = generateCPUIO();
		i = i % 2;
		count++;
	}
	numCPUs = count;
	numIOs = numCPUs - 1;

	CPUIOlist.resize(numCPUs + numIOs);
	std::generate(CPUIOlist.begin(), CPUIOlist.end(), [=](){return CPUIO(boundType); });
}

std::priority_queue<Task*, std::vector<Task*>, CompStr > generateInitialTasks(float, float);

std::priority_queue<Task*, std::vector<Task*>, CompStr > generateInitialTasks(float mean, float stddev){
	std::priority_queue<Task*, std::vector<Task*>, CompStr > eventQ;
	auto i = 0;
	auto num = generateInitialTaskTime(mean, stddev);
	Task* Ti = new Task(num);
	eventQ.push(Ti);
	while (num <= 100){
		i++;
		auto newNum = num + generateInitialTaskTime(mean, stddev);
		Task* T = new Task(newNum);
		eventQ.push(T);
		num = newNum;
	}

	return eventQ;
}

void runTrueSimulation(int numCPU, int ioDevice, float costOfContext, float jobFreq, double taskMix){
	float utilizationMin = 100, utilizationMax = 0;
	float latencyMin = 1000, latencyMax = 0;
	float responseMin = 1000, responseMax = 0; 
	//Begin the long loop here
	for (int x = 0; x < 100; x++){
		taskMixG = taskMix;
		numIO = ioDevice;
		idleCPU = numCPU;
		auto stddev = 0.5;
		float end = 100, current = 0;
		int finished = 0;
		float utilizationSum = 0, utilizationSize = 0;
		float responseSum = 0, responseSize = 0;
		//float latencySum = 0, latencySize = 0;

		std::vector<std::queue<Task*>> deviceQs(ioDevice);

		std::vector<bool> deviceNumber = createDevices(ioDevice);
		std::queue<Task*> readyQ;

		Task* temp;

		std::priority_queue<Task*, std::vector<Task*>, CompStr> eventQ = generateInitialTasks(jobFreq, stddev);

		while (current < end){
			//Recalculate the utilization
			if (abs(((numCPU - idleCPU) / numCPU) * 100) > utilizationMax)
				utilizationMax = abs(((numCPU - idleCPU) / numCPU) * 100);
				if (abs(((numCPU - idleCPU) / numCPU) * 100) < utilizationMin)
				utilizationMin = abs(((numCPU - idleCPU) / numCPU) * 100);
			utilizationSum = utilizationSum + (((numCPU - idleCPU) / numCPU) * 100);
			utilizationSize++;
			Task* T = eventQ.top();
			current = T->startTime;
			eventQ.pop();

			int choice = T->CPUIOListIterator % 2;

			switch (choice){
			case 0://0,2,4,6,8,10 (CPU time)
				readyQ.push(T);
				if (T->CPUIOListIterator == 2){
					responseSum = responseSum + abs(T->latency - current);
					if (abs(T->latency - current) > responseMax)
						responseMax = abs(T->latency - current);
					if (abs(T->latency - current) < responseMin)
						responseMin = abs(T->latency - current);
					responseSize++;
				}
				//Free up the I/O it came from
				deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = true;
				//Check to see if there is a CPU open for the one on top
				if (!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){
					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					//If it has one waiting, calculate the new value and stick it on the event queue
					eventQ.push(Tnew);
					//Pull it off the deviceQ
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					//Make the indicator false?
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;
				}
				if (idleCPU > 0){
					idleCPU--;
					//Pull it off the CPU readyQ
					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				break;
			case 1://1,3,5,7,9 (I/O Devices)
				//Increase the idleCPUs
				idleCPU++;

				if (T->CPUIOlist.size() == T->CPUIOListIterator){
					if (abs(current - T->latency) < latencyMin)
						latencyMin = abs(current - T->latency);
					if (abs(current - T->latency) > latencyMax)
						latencyMax = abs(current - T->latency);
					latencySum = latencySum + (current - T->latency);
					latencySize++;
					finished++;
					break;
				}

				//Calculate the response time

				//Put it in the appropriate deviceQ
				deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(T);
				//If something is waiting on the CPU queue
				if (!readyQ.empty()){
					idleCPU--;
					//Pull it off the CPU readyQ
					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				//If the device is available
				if (deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] == true &&
					!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){
					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					//If it has one waiting, calculate the new value and stick it on the event queue
					eventQ.push(Tnew);
					//Pull it off the deviceQ
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					//Make the indicator false?
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;
				}
				break;
			default:
				std::cout << "What did you do?" << std::endl;
				break;
			}
		}

		//Calculate Latency
		auto latency = latencySum / latencySize;
		//std::cout << "The latency is: " << latency << std::endl;
		fl.push_back(latency);
		//Calculate Response Time
		auto responseTime = responseSum / responseSize;
		//std::cout << "The response time is: " << responseTime << std::endl;
		fr.push_back(responseTime);
		//Calculate the throughput
		auto throughput = finished / end;
		//std::cout << "The throughput is: " << throughput << std::endl;
		ft.push_back(throughput);
		//Calculate the utilization
		auto utilization = utilizationSum / utilizationSize;
		//std::cout << "The utlization is: " << utilization << std::endl;
		fu.push_back(utilization);
	}
	std::cout << "Latency" << std::endl;
	mean(fl);
	deviation(fl);
	std::cout << "Min: " << latencyMin << std::endl;
	std::cout << "Max: " << latencyMax << std::endl;

	std::cout << std::endl;
	std::cout << "ResponseTime" << std::endl;
	mean(fr);
	deviation(fr);
	std::cout << "Min: " << responseMin << std::endl;
	std::cout << "Max: " << responseMax << std::endl;
	std::cout << std::endl;

	std::cout << "Throughput" << std::endl;
	mean(ft);
	deviation(ft);
	std::cout << std::endl;

	std::cout << "Utilization" << std::endl;
	mean(fu);
	deviation(fu);
	std::cout << "Min: " << utilizationMin << std::endl;
	std::cout << "Max: " << utilizationMax << std::endl;
}

void RoundRobin(int numCPU, int ioDevice, float costOfContext, float jobFreq, double taskMix, float terminateValue){
	float utilizationMin = 100, utilizationMax = 0;
	float latencyMin = 1000, latencyMax = 0;
	float responseMin = 1000, responseMax = 0;
	//Begin the long loop here
	for (int x = 0; x < 100; x++){
		taskMixG = taskMix;
		numIO = ioDevice;
		idleCPU = numCPU;
		auto stddev = 0.5;
		float end = 100, current = 0;
		int finished = 0;
		float utilizationSum = 0, utilizationSize = 0;
		float responseSum = 0, responseSize = 0;
		//float latencySum = 0, latencySize = 0;

		std::vector<std::queue<Task*>> deviceQs(ioDevice);

		std::vector<bool> deviceNumber = createDevices(ioDevice);
		std::queue<Task*> readyQ;

		Task* temp;

		std::priority_queue<Task*, std::vector<Task*>, CompStr> eventQ = generateInitialTasks(jobFreq, stddev);

		while (current < end){
			//Recalculate the utilization
			if (abs(((numCPU - idleCPU) / numCPU) * 100) > utilizationMax)
				utilizationMax = abs(((numCPU - idleCPU) / numCPU) * 100);
			if (abs(((numCPU - idleCPU) / numCPU) * 100) < utilizationMin)
				utilizationMin = abs(((numCPU - idleCPU) / numCPU) * 100);
			utilizationSum = utilizationSum + (((numCPU - idleCPU) / numCPU) * 100);
			utilizationSize++;
			Task* T = eventQ.top();
			current = T->startTime;
			eventQ.pop();

			int choice = T->CPUIOListIterator % 2;

			switch (choice){
			case 0://0,2,4,6,8,10 (CPU time)
				//This means that it came from an I/O device
				readyQ.push(T);

				//If the task finished without any leftover time
				if (T->remainTime == 0){
					T->burst = true;
				}

				//Calculate the response time if it was the first I/O device
				if (T->CPUIOListIterator == 2 && T->burst == true){
					responseSum = responseSum + abs(T->latency - current);
					if (abs(T->latency - current) > responseMax)
						responseMax = abs(T->latency - current);
					if (abs(T->latency - current) < responseMin)
						responseMin = abs(T->latency - current);
					responseSize++;
				}

				//Free up the I/O it came from
				deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = true;
				
				//Check to see if there is an I/O device queue that has things waiting
				if (!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){
					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time

					//Termination check
					if (current - newTime > terminateValue){
						temp->remainTime = (current - newTime) - terminateValue; 
						newTime = terminateValue + current;
					}
					else{
						temp->remainTime = 0;
					}

					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					if (temp->remainTime == 0)
						Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					else
						Tnew->CPUIOListIterator = temp->CPUIOListIterator;
					Tnew->remainTime = temp->remainTime;
					eventQ.push(Tnew);
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;					
				}
				if (idleCPU > 0){
					idleCPU--;
					//Pull it off the CPU readyQ
					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					
					//Termination check
					if (current - newTime > terminateValue){
						temp->remainTime = (current - newTime) - terminateValue;
						newTime = terminateValue + current;
					}
					else{
						temp->remainTime = 0;
					}

					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;

					if (temp->remainTime == 0)
						Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					else
						Tnew->CPUIOListIterator = temp->CPUIOListIterator;
					Tnew->remainTime = temp->remainTime;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				break;
			case 1://1,3,5,7,9 (I/O Devices)
				//Increase the idleCPUs
				idleCPU++;

				//Calculate the latency
				if (T->CPUIOlist.size() == T->CPUIOListIterator){
					if (abs(current - T->latency) < latencyMin)
						latencyMin = abs(current - T->latency);
					if (abs(current - T->latency) > latencyMax)
						latencyMax = abs(current - T->latency);
					latencySum = latencySum + (current - T->latency);
					latencySize++;
					finished++;
					break;
				}

				//Put it in the appropriate deviceQ
				deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(T);
				//If something is waiting on the CPU queue
				if (!readyQ.empty()){
					idleCPU--;
					//Pull it off the CPU readyQ
					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					
					//Termination check
					if (current - newTime > terminateValue){
						temp->remainTime = (current - newTime) - terminateValue;
						newTime = terminateValue + current;
					}
					else{
						temp->remainTime = 0;
					}
					
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					if (temp->remainTime == 0)
						Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					else
						Tnew->CPUIOListIterator = temp->CPUIOListIterator;
					Tnew->remainTime = temp->remainTime;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				//If the device is available
				if (deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] == true &&
					!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){
					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time
					
					//Termination check
					if (current - newTime > terminateValue){
						temp->remainTime = (current - newTime) - terminateValue;
						newTime = terminateValue + current;
					}
					else{
						temp->remainTime = 0;
					}
					
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					if (temp->remainTime == 0)
						Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					else
						Tnew->CPUIOListIterator = temp->CPUIOListIterator;
					Tnew->remainTime = temp->remainTime;

					//If it has one waiting, calculate the new value and stick it on the event queue
					eventQ.push(Tnew);
					//Pull it off the deviceQ
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					//Make the indicator false?
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;
				}
				break;
			default:
				std::cout << "What did you do?" << std::endl;
				break;
			}
		}

		//Calculate Latency
		auto latency = latencySum / latencySize;
		//std::cout << "The latency is: " << latency << std::endl;
		fl.push_back(latency);
		//Calculate Response Time
		auto responseTime = responseSum / responseSize;
		//std::cout << "The response time is: " << responseTime << std::endl;
		fr.push_back(responseTime);
		//Calculate the throughput
		auto throughput = finished / end;
		//std::cout << "The throughput is: " << throughput << std::endl;
		ft.push_back(throughput);
		//Calculate the utilization
		auto utilization = utilizationSum / utilizationSize;
		//std::cout << "The utlization is: " << utilization << std::endl;
		fu.push_back(utilization);
	}
	std::cout << std::endl;
	std::cout << "Round Robin" << std::endl;
	std::cout << std::endl;
	std::cout << "Latency" << std::endl;
	mean(fl);
	deviation(fl);
	std::cout << "Min: " << latencyMin << std::endl;
	std::cout << "Max: " << latencyMax << std::endl;

	std::cout << std::endl;
	std::cout << "ResponseTime" << std::endl;
	mean(fr);
	deviation(fr);
	std::cout << "Min: " << responseMin << std::endl;
	std::cout << "Max: " << responseMax << std::endl;
	std::cout << std::endl;

	std::cout << "Throughput" << std::endl;
	mean(ft);
	deviation(ft);
	std::cout << std::endl;

	std::cout << "Utilization" << std::endl;
	mean(fu);
	deviation(fu);
	std::cout << "Min: " << utilizationMin << std::endl;
	std::cout << "Max: " << utilizationMax << std::endl;
}

void ShortestJobFirst(int numCPU, int ioDevice, float costOfContext, float jobFreq, double taskMix){
	float utilizationMin = 100, utilizationMax = 0;
	float latencyMin = 1000, latencyMax = 0;
	float responseMin = 1000, responseMax = 0;

	for (int x = 0; x < 100; x++){
		taskMixG = taskMix;
		numIO = ioDevice;
		idleCPU = numCPU;
		auto stddev = 0.5;
		float end = 100, current = 0;
		int finished = 0;
		float utilizationSum = 0, utilizationSize = 0;
		float responseSum = 0, responseSize = 0;
		//float latencySum = 0, latencySize = 0;

		std::vector<std::queue<Task*>> deviceQs(ioDevice);

		std::vector<bool> deviceNumber = createDevices(ioDevice);
		std::queue<Task*> readyQ;

		Task* temp;

		std::priority_queue<Task*, std::vector<Task*>, CompStr> eventQ = generateInitialTasks(jobFreq, stddev);

		while (current < end){
			//Recalculate the utilization
			if (abs(((numCPU - idleCPU) / numCPU) * 100) > utilizationMax)
				utilizationMax = abs(((numCPU - idleCPU) / numCPU) * 100);
			if (abs(((numCPU - idleCPU) / numCPU) * 100) < utilizationMin)
				utilizationMin = abs(((numCPU - idleCPU) / numCPU) * 100);
			utilizationSum = utilizationSum + (((numCPU - idleCPU) / numCPU) * 100);
			utilizationSize++;
			Task* T = eventQ.top();
			current = T->startTime;
			eventQ.pop();

			int choice = T->CPUIOListIterator % 2;

			switch (choice){
			case 0://0,2,4,6,8,10 (CPU time)
				readyQ.push(T);

				//Calculate the response time
				if (T->CPUIOListIterator == 2){
					responseSum = responseSum + abs(T->latency - current);
					if (abs(T->latency - current) > responseMax)
						responseMax = abs(T->latency - current);
					if (abs(T->latency - current) < responseMin)
						responseMin = abs(T->latency - current);
					responseSize++;
				}

				//Free up the I/O it came from
				deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = true;

				//Check to see if there is a CPU open for the one on top
				if (!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){

					//Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].size(); i++){
						tempVector.push_back(deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front());
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					}

					//Sort the vector
					std::sort(tempVector.begin(), tempVector.end());
					
					for (int j = 0; j < tempVector.size(); j++){
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(tempVector[j]);
					}


					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					//If it has one waiting, calculate the new value and stick it on the event queue
					eventQ.push(Tnew);
					//Pull it off the deviceQ
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					//Make the indicator false?
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;
				}
				if (idleCPU > 0){
					idleCPU--;

					//Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < readyQ.size(); i++){
						tempVector.push_back(readyQ.front());
						readyQ.pop();
					}

					//Sort the vector
					std::sort(tempVector.begin(), tempVector.end());

					for (int j = 0; j < tempVector.size(); j++){
						readyQ.push(tempVector[j]);
					}

					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				break;
			case 1://1,3,5,7,9 (I/O Devices)
				//Increase the idleCPUs
				idleCPU++;

				if (T->CPUIOlist.size() == T->CPUIOListIterator){
					if (abs(current - T->latency) < latencyMin)
						latencyMin = abs(current - T->latency);
					if (abs(current - T->latency) > latencyMax)
						latencyMax = abs(current - T->latency);
					latencySum = latencySum + (current - T->latency);
					latencySize++;
					finished++;
					break;
				}

				//Put it in the appropriate deviceQ
				deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(T);

				//If something is waiting on the CPU queue
				if (!readyQ.empty()){
					idleCPU--;

					//Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < readyQ.size(); i++){
						tempVector.push_back(readyQ.front());
						readyQ.pop();
					}

					//Sort the vector
					std::sort(tempVector.begin(), tempVector.end());

					for (int j = 0; j < tempVector.size(); j++){
						readyQ.push(tempVector[j]);
					}

					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				//If the device is available
				if (deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] == true &&
					!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){

					//Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].size(); i++){
						tempVector.push_back(deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front());
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					}

					//Sort the vector
					std::sort(tempVector.begin(), tempVector.end());

					for (int j = 0; j < tempVector.size(); j++){
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(tempVector[j]);
					}

					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					//If it has one waiting, calculate the new value and stick it on the event queue
					eventQ.push(Tnew);
					//Pull it off the deviceQ
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					//Make the indicator false?
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;
				}
				break;
			default:
				std::cout << "What did you do?" << std::endl;
				break;
			}
		}

		//Calculate Latency
		auto latency = latencySum / latencySize;
		//std::cout << "The latency is: " << latency << std::endl;
		fl.push_back(latency);
		//Calculate Response Time
		auto responseTime = responseSum / responseSize;
		//std::cout << "The response time is: " << responseTime << std::endl;
		fr.push_back(responseTime);
		//Calculate the throughput
		auto throughput = finished / end;
		//std::cout << "The throughput is: " << throughput << std::endl;
		ft.push_back(throughput);
		//Calculate the utilization
		auto utilization = utilizationSum / utilizationSize;
		//std::cout << "The utlization is: " << utilization << std::endl;
		fu.push_back(utilization);
	}
	std::cout << std::endl;
	std::cout << "SJF" << std::endl;
	std::cout << std::endl;
	std::cout << "Latency" << std::endl;
	mean(fl);
	deviation(fl);
	std::cout << "Min: " << latencyMin << std::endl;
	std::cout << "Max: " << latencyMax << std::endl;

	std::cout << std::endl;
	std::cout << "ResponseTime" << std::endl;
	mean(fr);
	deviation(fr);
	std::cout << "Min: " << responseMin << std::endl;
	std::cout << "Max: " << responseMax << std::endl;
	std::cout << std::endl;

	std::cout << "Throughput" << std::endl;
	mean(ft);
	deviation(ft);
	std::cout << std::endl;

	std::cout << "Utilization" << std::endl;
	mean(fu);
	deviation(fu);
	std::cout << "Min: " << utilizationMin << std::endl;
	std::cout << "Max: " << utilizationMax << std::endl;
}

void ApproximateSJF(int numCPU, int ioDevice, float costOfContext, float jobFreq, double taskMix){
	float utilizationMin = 100, utilizationMax = 0;
	float latencyMin = 1000, latencyMax = 0;
	float responseMin = 1000, responseMax = 0;
	float CPUapprox = 0, CPUapproxNum = 0;
	float IOapprox = 0, IOapproxNum = 0;

	for (int x = 0; x < 100; x++){
		taskMixG = taskMix;
		numIO = ioDevice;
		idleCPU = numCPU;
		auto stddev = 0.5;
		float end = 100, current = 0;
		int finished = 0;
		float utilizationSum = 0, utilizationSize = 0;
		float responseSum = 0, responseSize = 0;
		//float latencySum = 0, latencySize = 0;

		std::vector<std::queue<Task*>> deviceQs(ioDevice);

		std::vector<bool> deviceNumber = createDevices(ioDevice);
		//std::queue<Task*> readyQ;

		std::queue<Task*> readyQ;

		Task* temp;

		std::priority_queue<Task*, std::vector<Task*>, CompStr> eventQ = generateInitialTasks(jobFreq, stddev);

		while (current < end){
			//Recalculate the utilization
			if (abs(((numCPU - idleCPU) / numCPU) * 100) > utilizationMax)
				utilizationMax = abs(((numCPU - idleCPU) / numCPU) * 100);
			if (abs(((numCPU - idleCPU) / numCPU) * 100) < utilizationMin)
				utilizationMin = abs(((numCPU - idleCPU) / numCPU) * 100);
			utilizationSum = utilizationSum + (((numCPU - idleCPU) / numCPU) * 100);
			utilizationSize++;
			Task* T = eventQ.top();
			current = T->startTime;
			eventQ.pop();

			int choice = T->CPUIOListIterator % 2;

			switch (choice){
			case 0://0,2,4,6,8,10 (CPU time)
				readyQ.push(T);

				//Calculate the response time
				if (T->CPUIOListIterator == 2){
					responseSum = responseSum + abs(T->latency - current);
					if (abs(T->latency - current) > responseMax)
						responseMax = abs(T->latency - current);
					if (abs(T->latency - current) < responseMin)
						responseMin = abs(T->latency - current);
					responseSize++;
				}

				CPUapprox += (current - T->startTime);
				CPUapproxNum++;

				//Free up the I/O it came from
				deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = true;

				//Check to see if there is a CPU open for the one on top
				if (!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){

					//Approximate Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].size(); i++){
						tempVector.push_back(deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front());
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					}

					//Sort the vector
					CompStrApprox sort;
					std::sort(tempVector.begin(), tempVector.end(), sort);

					for (int j = 0; j < tempVector.size(); j++){
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(tempVector[j]);
					}

					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->key = IOapprox / IOapproxNum;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					//If it has one waiting, calculate the new value and stick it on the event queue
					eventQ.push(Tnew);
					//Pull it off the deviceQ
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					//Make the indicator false?
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;
				}
				if (idleCPU > 0){
					idleCPU--;

					//Approximate Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < readyQ.size(); i++){
						tempVector.push_back(readyQ.front());
						readyQ.pop();
					}

					//Sort the vector
					CompStrApprox sort;
					std::sort(tempVector.begin(), tempVector.end(), sort);

					for (int j = 0; j < tempVector.size(); j++){
						readyQ.push(tempVector[j]);
					}

					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->key = CPUapprox / CPUapproxNum;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				break;
			case 1://1,3,5,7,9 (I/O Devices)
				//Increase the idleCPUs
				idleCPU++;

				IOapprox += (current - T->startTime);
			    IOapproxNum++;

				if (T->CPUIOlist.size() == T->CPUIOListIterator){
					if (abs(current - T->latency) < latencyMin)
						latencyMin = abs(current - T->latency);
					if (abs(current - T->latency) > latencyMax)
						latencyMax = abs(current - T->latency);
					latencySum = latencySum + (current - T->latency);
					latencySize++;
					finished++;
					break;
				}

				//Put it in the appropriate deviceQ
				deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(T);

				//If something is waiting on the CPU queue
				if (!readyQ.empty()){
					idleCPU--;

					//Approximate Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < readyQ.size(); i++){
						tempVector.push_back(readyQ.front());
						readyQ.pop();
					}

					//Sort the vector
					CompStrApprox sort;
					std::sort(tempVector.begin(), tempVector.end(), sort);

					for (int j = 0; j < tempVector.size(); j++){
						readyQ.push(tempVector[j]);
					}

					Task* temp = readyQ.front();
					//Calculate the new start time
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].CPUtime;
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->key = CPUapprox / CPUapproxNum;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;

					//Put it in the eventQ for when it finishes
					eventQ.push(Tnew);
					readyQ.pop();
				}
				//If the device is available
				if (deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] == true &&
					!deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].empty()){

					//Approximate Shortest Job First
					std::vector<Task*> tempVector;
					for (int i = 0; i < deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].size(); i++){
						tempVector.push_back(deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front());
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					}

					//Sort the vector
					CompStrApprox sort;
					std::sort(tempVector.begin(), tempVector.end(), sort);

					for (int j = 0; j < tempVector.size(); j++){
						deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].push(tempVector[j]);
					}

					Task* temp = deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].front();
					float newTime = current + costOfContext + T->CPUIOlist[T->CPUIOListIterator].ioDeviceTime;//Plus the device time
					Task* Tnew = new Task(newTime);
					Tnew->CPUIOlist = temp->CPUIOlist;
					Tnew->latency = temp->latency;
					Tnew->key = IOapprox / IOapproxNum;
					Tnew->CPUIOListIterator = temp->CPUIOListIterator + 1;
					//If it has one waiting, calculate the new value and stick it on the event queue
					eventQ.push(Tnew);
					//Pull it off the deviceQ
					deviceQs[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1].pop();
					//Make the indicator false?
					deviceNumber[T->CPUIOlist[T->CPUIOListIterator].ioDeviceNumber - 1] = false;
				}
				break;
			default:
				std::cout << "What did you do?" << std::endl;
				break;
			}
		}

		//Calculate Latency
		auto latency = latencySum / latencySize;
		//std::cout << "The latency is: " << latency << std::endl;
		fl.push_back(latency);
		//Calculate Response Time
		auto responseTime = responseSum / responseSize;
		//std::cout << "The response time is: " << responseTime << std::endl;
		fr.push_back(responseTime);
		//Calculate the throughput
		auto throughput = finished / end;
		//std::cout << "The throughput is: " << throughput << std::endl;
		ft.push_back(throughput);
		//Calculate the utilization
		auto utilization = utilizationSum / utilizationSize;
		//std::cout << "The utlization is: " << utilization << std::endl;
		fu.push_back(utilization);
	}
	std::cout << std::endl;
	std::cout << "Approx SJF" << std::endl;
	std::cout << std::endl;
	std::cout << "Latency" << std::endl;
	mean(fl);
	deviation(fl);
	std::cout << "Min: " << latencyMin << std::endl;
	std::cout << "Max: " << latencyMax << std::endl;

	std::cout << std::endl;
	std::cout << "ResponseTime" << std::endl;
	mean(fr);
	deviation(fr);
	std::cout << "Min: " << responseMin << std::endl;
	std::cout << "Max: " << responseMax << std::endl;
	std::cout << std::endl;

	std::cout << "Throughput" << std::endl;
	mean(ft);
	deviation(ft);
	std::cout << std::endl;

	std::cout << "Utilization" << std::endl;
	mean(fu);
	deviation(fu);
	std::cout << "Min: " << utilizationMin << std::endl;
	std::cout << "Max: " << utilizationMax << std::endl;
}

int main(){

	int choice, numCPU = 3, ioDevice = 3;
	float costOfContext = 3, jobFreq = 5;
	double taskMix = 50;
	float terminationValue = 3;

	while (1){
		std::cout << "      CPU Scheduler Menu:        " << std::endl;
		std::cout << "================================ " << std::endl;
		std::cout << "1) Input # of CPUs              = " << numCPU << std::endl;
		std::cout << "2) Input # of IO devices        = " << ioDevice << std::endl;
		std::cout << "3) Input cost of context switch = " << costOfContext << std::endl;
		std::cout << "4) Task Mix (percentage)        = " << taskMix << "%" << std::endl;
		std::cout << "5) Frequency of job creation    = " << jobFreq << std::endl;
		std::cout << "6) Set Termination Value        = " << terminationValue << std::endl;
		std::cout << "7) Run simulation(default)      " << std::endl;
		std::cout << "8) Round-Robin                  " << std::endl;
		std::cout << "9) Shortest Job First           " << std::endl;
		std::cout << "10) Approximate SJF             " << std::endl;
		std::cout << "11) Run ALL Simulations         " << std::endl;
		std::cout << "12) Exit simulation             " << std::endl;

		std::cin >> choice;

		switch (choice){
		case 1:
			std::cout << "How many CPUs? ";
			std::cin >> numCPU;
			break;
		case 2:
			std::cout << "How many devices? ";
			std::cin >> ioDevice;
			break;
		case 3:
			std::cout << "Cost of Context Switch? ";
			std::cin >> costOfContext;
			break;
		case 4:
			std::cout << "Task Mix percentage(decimal)? ";
			std::cin >> taskMix;
			break;
		case 5:
			std::cout << "Frequency of job creation? ";
			std::cin >> jobFreq;
			break;
		case 6:
			std::cout << "Termination time? ";
			std::cin >> terminationValue;
			break;
		case 7:
			runTrueSimulation(numCPU, ioDevice, costOfContext, jobFreq, taskMix);
			system("Pause");
			break;
		case 8:
			RoundRobin(numCPU, ioDevice, costOfContext, jobFreq, taskMix, terminationValue);
			system("Pause");
			break;
		case 9:
			ShortestJobFirst(numCPU, ioDevice, costOfContext, jobFreq, taskMix);
			system("Pause");
			break;
		case 10:
			ApproximateSJF(numCPU, ioDevice, costOfContext, jobFreq, taskMix);
			system("Pause");
			break;
		case 11:
			runTrueSimulation(numCPU, ioDevice, costOfContext, jobFreq, taskMix);
			RoundRobin(numCPU, ioDevice, costOfContext, jobFreq, taskMix, terminationValue);
			ShortestJobFirst(numCPU, ioDevice, costOfContext, jobFreq, taskMix);
			ApproximateSJF(numCPU, ioDevice, costOfContext, jobFreq, taskMix);
			system("Pause");
			break; 
		case 12:
			return 0;
			break;
		default:
			std::cout << "Invalid input!" << std::endl;
			break;
		}
		std::cout << std::endl;
	}
}