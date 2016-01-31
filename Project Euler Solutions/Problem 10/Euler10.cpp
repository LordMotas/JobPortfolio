/*
  Project Euler #10
  Problem Statement:
	
  The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

  Find the sum of all the primes below two million.

*/

#include <iostream>

int main(){

	auto N = 1000000;
	long long int total = 0;
	std::cout << "Calculating sum of all primes..." << std::endl;
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
			if (i <= 2000000){
				total += i; 
			}
		}
	}

	std::cout << "The answer is: " << total << std::endl;
	system("Pause)");
	return 0;
}