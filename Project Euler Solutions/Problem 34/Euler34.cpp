/*

	Project Euler #34
	Problem Statement: 

	145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

	Find the sum of all numbers which are equal to the sum of the factorial of their digits.

	Note: as 1! = 1 and 2! = 2 are not sums they are not included.

*/

#include <iostream>
#include <string>
#include <vector>

int factorial(int number) {
	int temp;

	if (number <= 1) return 1;
	temp = number * factorial(number - 1);
	return temp;
}

int main(){

	std::vector<int> finalSum;
	for (int i = 3; i <= 40730; i++){
		std::string numString = std::to_string(i);
		int length = numString.length();
		int sum = 0;
		for (int j = 0; j <= length - 1; j++){
			sum += factorial(numString[j] - '0');
		}
		if (sum == i)
			finalSum.push_back(i);
	}
	int sum = 0;
	for (int i = 0; i < finalSum.size(); i++){
		sum += finalSum[i];
	}

	std::cout << "The answer is: " << sum << std::endl;
	system("Pause");
	return 0;
}