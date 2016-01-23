/*
	Project Euler # 19
	Problem Statement:

	You are given the following information, but you may prefer to do some research for yourself.

	1 Jan 1900 was a Monday.
	Thirty days has September,
	April, June and November.
	All the rest have thirty-one,
	Saving February alone,
	Which has twenty-eight, rain or shine.
	And on leap years, twenty-nine.
	A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
	
	How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct date{
	std::string dayOfWeek; //Monday Tuesday etc
	int dayOfMonth; //1-31
	std::string monthOfYear; //Jan, Feb etc
	int numYear; // 1900-2000
};

int o = 0;

int main(){

	std::vector<std::string> daysOfWeek = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	std::vector<std::string> monthsOfYear = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	std::vector<date> dateVector;
	std::vector<int> leapYears(100);
	std::vector<int> allYears(101);
	date test;

	int i = 1900;
	std::generate(leapYears.begin(), leapYears.end(), [&](){i++; if (i % 100 == 0 && i % 400 == 0) return i; if (i % 4 == 0) return i; return NULL; });

	i = 1899;
	std::generate(allYears.begin(), allYears.end(), [&](){i++; return i;});

	std::vector<int> leapYearList(25);
	
	int k = 0;
	for (int j = 0; j < leapYears.size(); j++){
		if (leapYears[j] != 0){
			//std::cout << leapYears[j] << std::endl;
			leapYearList[k] = leapYears[j];
			k++;
		}

	}
	//leapYearList[k] contains all of the leap years
	int size = 31;

	for (int l = 0; l <= 100; l++){
		//std::cout << "Year: " << allYears[l] << std::endl;
		for (int m = 0; m < 12; m++){
			//std::cout << "Month: " << monthsOfYear[m] << std::endl;
			if (monthsOfYear[m] == "September" || monthsOfYear[m] == "April" || monthsOfYear[m] == "June" || monthsOfYear[m] == "November")
				size = 30;
			else if (monthsOfYear[m] == "February"){
				for (int j = 0; j < leapYearList.size(); j++){
					if (allYears[l] == leapYearList[j])
						size = 29;
				}
				if (size != 29)
					size = 28;
			}

			else{
				size = 31;
			}
			for (int n = 0; n < size; n++){
				o = n % 7;
				if (allYears[l] > 1900){
					test.dayOfMonth = n + 1;
					test.dayOfWeek = daysOfWeek[o];
					test.monthOfYear = monthsOfYear[m];
					test.numYear = allYears[l];
					dateVector.push_back(test);
				}
				//std::cout << "Day: " << n+1 << " " << daysOfWeek[o] << std::endl;
			}
			char check = 'x';
			if (daysOfWeek[o][0] == 'T' && daysOfWeek[o][1] == 'h')
				check = 'H';
			else if (daysOfWeek[o][0] == 'S' && daysOfWeek[o][1] == 'u')
				check = 'R';
			else
				check = daysOfWeek[o][0];

			switch (check){
			case 'R':
				daysOfWeek = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
				break;
			case 'M':
				daysOfWeek = { "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday" };
				break;
			case 'T':
				daysOfWeek = { "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday"};
				break;
			case 'W':
				daysOfWeek = { "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};
				break;
			case 'H':
				daysOfWeek = { "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"};
				break;
			case 'F':
				daysOfWeek = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
				break;
			case 'S':
				daysOfWeek = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
				break;
			}
		}

	}

	int answer = 0;
	
	for (int i = 0; i < dateVector.size(); i++){
		if (dateVector[i].dayOfMonth == 1 && dateVector[i].dayOfWeek == "Sunday" && dateVector[i].numYear > 1900)
			answer++;
	}

	std::cout << "The answer is: " << answer << std::endl;
	system("Pause");
	return 0;
}