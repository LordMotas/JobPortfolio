/*
Project Euler #6
Problem Statement:
The sum of the squares of the first ten natural numbers is,

1^2 + 2^2 + ... + 10^2 = 385
The square of the sum of the first ten natural numbers is,

(1 + 2 + ... + 10)^2 = 552 = 3025
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

#include <iostream>

int main(){

	auto sumOfSqrs = 0;
	auto sqrOfSums = 0;
	for (int i = 0; i <= 100; i++){
		sumOfSqrs += pow(i, 2);
	}
	for (int j = 0; j <= 100; j++){
		sqrOfSums += j;
	}
	sqrOfSums = pow(sqrOfSums, 2);

	std::cout << "The Sum of Squares is: " << sumOfSqrs << std::endl;
	std::cout << "The Square of Sums is: " << sqrOfSums << std::endl;
	std::cout << "The difference is: " << abs(sumOfSqrs - sqrOfSums) << std::endl;

	system("Pause");
	return 0;
}