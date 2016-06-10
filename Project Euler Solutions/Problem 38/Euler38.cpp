/*

Project Euler #38
Problem Statement:
Take the number 192 and multiply it by each of 1, 2, and 3:

192 × 1 = 192
192 × 2 = 384
192 × 3 = 576
By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?

*/

#include <iostream>
#include <string>
#include <algorithm>

int main(){
	int largestPandigital = 0;
	std::string testString = "";
	for (int i = 1; i < 10000; i++){
		if (i == 192){
			//Debug here
			std::cout << "";
		}
		for (int j = 1; testString.length() < 9; j++){
			testString += std::to_string(i*j);
		}
		if (testString.length() == 9){
			if (std::find(testString.begin(), testString.end(), '1') != testString.end() &&
				std::find(testString.begin(), testString.end(), '2') != testString.end() && 
				std::find(testString.begin(), testString.end(), '3') != testString.end() && 
				std::find(testString.begin(), testString.end(), '4') != testString.end() && 
				std::find(testString.begin(), testString.end(), '5') != testString.end() && 
				std::find(testString.begin(), testString.end(), '6') != testString.end() && 
				std::find(testString.begin(), testString.end(), '7') != testString.end() && 
				std::find(testString.begin(), testString.end(), '8') != testString.end() && 
				std::find(testString.begin(), testString.end(), '9') != testString.end()){
				if (atoi(testString.c_str()) > largestPandigital)
					largestPandigital = atoi(testString.c_str());
			}
		}
		testString = "";
	}
	std::cout << "The answer is: " << largestPandigital << std::endl;
	system("Pause");
	return 0;
}