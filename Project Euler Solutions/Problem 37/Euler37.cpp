/*

Project Euler #37
Problem Statement:
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage:
3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

bool isPrime(int num)
{
	if (num <= 1)
		return false;
	else if (num == 2)
		return true;
	else if (num % 2 == 0)
		return false;
	else
	{
		bool prime = true;
		int divisor = 3;
		double num_d = static_cast<double>(num);
		int upperLimit = static_cast<int>(sqrt(num_d) + 1);

		while (divisor <= upperLimit)
		{
			if (num % divisor == 0)
				prime = false;
			divisor += 2;
		}
		return prime;
	}
}

int main(){
	int finalSum = 0;
	std::vector<int> truncatedPrimes;
	bool firstTest = false, secondTest = false;
	for (int i = 8; i < 9999999; i++){
		if (isPrime(i)){
			std::string test = std::to_string(i);
			std::string test1 = std::to_string(i);
			std::string test2 = std::to_string(i);
			int numPrimes = 0;
			while(test1.length() != 1){
				//Truncate left
				int truncResult = atoi(test1.substr(1,test1.length()).c_str());
				if (isPrime(truncResult))
					numPrimes++;
				else
					break;
				test1 = test1.substr(1, test1.length());
			}
			if (numPrimes == test.length() - 1)
				firstTest = true;
			numPrimes = 0;
			while (test2.length() != 1){
				//Truncate left
				int truncResult = atoi(test2.substr(0, test2.length() - 1).c_str());
				if (isPrime(truncResult))
					numPrimes++;
				else
					break;
				test2 = test2.substr(0, test2.length() - 1);
			}
			if (numPrimes == test.length() - 1)
				secondTest = true;
		}
		if (firstTest && secondTest){
			truncatedPrimes.push_back(i);
			finalSum += i;
			firstTest = false;
			secondTest = false;
		}
		firstTest = false;
		secondTest = false;
		if (truncatedPrimes.size() == 11)
			break;
	}
	std::cout << "The answer is: " << finalSum << std::endl;
	system("Pause");
	return 0;
}