/*
	Project Euler #7
	Problem Statement:
	
	By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, 
	we can see that the 6th prime is 13.

	What is the 10001st prime number?
	
*/

#include <iostream>

int main(){
	auto N = 10001;
	std::cout << "Calculating prime numbers..." << std::endl;
	for (int i = 2; N > 0; ++i){
		bool  isPrime = true;
		for (int j = 2; j < i; ++j){
			if (i  % j == 0){
				isPrime = false;
				break;
			}
		}
		if (isPrime){
			--N;
			if (N == 0){
				std::cout << "The answer is: " << i << std::endl;
			}
		}
	}

	system("Pause");
	return 0;
}