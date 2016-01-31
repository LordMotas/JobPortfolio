/*

Project Euler #23
Problem Statement:

A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum 
of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can 
be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis 
even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less 
than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	int finalAnswer = 0;
	std::vector<int> divisorArray;
	std::vector<int> abundantArray;
	std::cout << "Finding all divisors of numbers below 28123..." << std::endl;
	std::cout << "Calculating abundant numbers..." << std::endl;
	for (int i = 0; i <= 28123; i++){
		for (int j = 1; j < i; j++){
			//j is a divisor of i
			if (i % j == 0){
				divisorArray.push_back(j);
			}
		}
		int sum = 0;
		for (int k : divisorArray){
			sum += k;
		}
		if (sum > i){
			abundantArray.push_back(i);
		}
		divisorArray.clear();
	}

	//Now abundantArray has all the abundant numbers necessary
	std::vector<int> totalAbundantArray;
	std::cout << "Finding linear combinations of all abundant numbers..." << std::endl;
	for (int i = 0; i < abundantArray.size(); i++){
		for (int j = 0; j < abundantArray.size(); j++){
			if (abundantArray[i] + abundantArray[j] <= 28123)
				if (std::find(totalAbundantArray.begin(), totalAbundantArray.end(), (abundantArray[i] + abundantArray[j])) == totalAbundantArray.end())
					totalAbundantArray.push_back(abundantArray[i] + abundantArray[j]);
		}
	}

	//totalAbundantArray contains the linear combinations of all abundant numbers
	std::cout << "Sorting array of abundant numbers..." << std::endl;
	std::sort(totalAbundantArray.begin(), totalAbundantArray.end());
	std::cout << "Locating all other non-abundant number sums..." << std::endl;
	std::vector<int> answerArray;
	for (int i = 0; i < 28123; i++){
		if (std::find(totalAbundantArray.begin(), totalAbundantArray.end(), i) == totalAbundantArray.end())
			answerArray.push_back(i);
	}

	std::cout << "Calculating sum of remaining numbers..." << std::endl;
	for (int i : answerArray){
		finalAnswer += i;
	}

	std::cout << "The answer is: " << finalAnswer << std::endl;

	system("Pause");
	return 0;
}