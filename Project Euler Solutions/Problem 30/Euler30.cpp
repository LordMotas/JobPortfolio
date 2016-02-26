/*
	Project Euler #30
	Problem Statement:

	Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

	1634 = 1^4 + 6^4 + 3^4 + 4^4
	8208 = 8^4 + 2^4 + 0^4 + 8^4
	9474 = 9^4 + 4^4 + 7^4 + 4^4
	As 1 = 1^4 is not a sum it is not included.

	The sum of these numbers is 1634 + 8208 + 9474 = 19316.

	Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

*/

#include <iostream>
#include <string>
#include <vector>

int main(){
	std::cout << "Checking numbers from 2 to 194979..." << std::endl;
	std::vector<int> answerVector;
	int compare = 0;
	for (int i = 2; i <= 194979; i++){
		std::string intString = std::to_string(i);
		for (int j = 0; j < intString.size(); j++){
			compare += pow((int)intString[j] - 48, 5);
		}
		if (compare == i)
			answerVector.push_back(i);
		compare = 0;
	}
	std::cout << "Summing all matching criteria..." << std::endl;
	int answer = 0;
	for (int i = 0; i < answerVector.size(); i++){
		answer += answerVector[i];
	}
	std::cout << "The answer is: " << answer << std::endl;
	system("Pause");
	return 0;
}