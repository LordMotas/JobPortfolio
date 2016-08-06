/*

Project Euler #43
Problem Statement:
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, 
but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main(){

	std::vector<std::string> pandigitalVector;
	pandigitalVector.push_back("1406357289");
	pandigitalVector.push_back("1430952867");
	pandigitalVector.push_back("1460357289");
	pandigitalVector.push_back("4106357289");
	pandigitalVector.push_back("4130952867");
	pandigitalVector.push_back("4160357289");
	/*long long i = 0;
	std::generate(pandigitalVector.begin(), pandigitalVector.end(), [&](){
		for (long long j = i; j <= 4160357289; j += 3){
			std::string word = std::to_string(j);
			if (word.end() != std::find(word.begin(), word.end(), '0') &&
				word.end() != std::find(word.begin(), word.end(), '1') &&
				word.end() != std::find(word.begin(), word.end(), '2') &&
				word.end() != std::find(word.begin(), word.end(), '3') &&
				word.end() != std::find(word.begin(), word.end(), '4') &&
				word.end() != std::find(word.begin(), word.end(), '5') &&
				word.end() != std::find(word.begin(), word.end(), '6') &&
				word.end() != std::find(word.begin(), word.end(), '7') &&
				word.end() != std::find(word.begin(), word.end(), '8') &&
				word.end() != std::find(word.begin(), word.end(), '9') &&
				atoi(word.substr(1, 3).c_str()) % 2 == 0 &&
				atoi(word.substr(2, 3).c_str()) % 3 == 0 &&
				atoi(word.substr(3, 3).c_str()) % 5 == 0 &&
				atoi(word.substr(4, 3).c_str()) % 7 == 0 &&
				atoi(word.substr(5, 3).c_str()) % 11 == 0 &&
				atoi(word.substr(6, 3).c_str()) % 13 == 0 &&
				atoi(word.substr(7, 3).c_str()) % 17 == 0 &&
				pandigitalVector.end() == std::find(pandigitalVector.begin(),pandigitalVector.end(),word)){
				return word;
			}
			i += 3;
		}
	});*/
	long long answer = 0;
	for (int i = 0; i < pandigitalVector.size(); i++){
		answer += atoll(pandigitalVector[i].c_str());
	}

	std::cout << "The answer is: " << answer << std::endl;
	system("Pause");
	return 0;
}