/*
	Project Euler #27
	Problem Statement:

	Euler discovered the remarkable quadratic formula:

	n² + n + 41

	It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. 
	However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is 
	clearly divisible by 41.

	The incredible formula  n² − 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79. 
	The product of the coefficients, −79 and 1601, is −126479.

	Considering quadratics of the form:

	n² + an + b, where |a| < 1000 and |b| < 1000

	where |n| is the modulus/absolute value of n
	e.g. |11| = 11 and |−4| = 4

	Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes 
	for consecutive values of n, starting with n = 0.

*/

#include <iostream>
#include <vector>
#include <math.h>

std::vector<int> primes;

bool isPrime(int number){
	int i = 0;
	while (primes[i] <= number){
		if (primes[i] == number){
			return true;
		}
		i++;
	}
	return false;
}

void generatePrimes(){
	auto N = 2000;
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
			primes.push_back(i);
		}
	}
}

int main(){
	int aMax = 0, bMax = 0, nMax = 0, count = 0;
	std::cout << "Generating list of primes..." << std::endl;
	generatePrimes();
	std::cout << "Applying quadratic expressions..." << std::endl;
	for (int a = -1000; a <= 1000; a++) {
		for (int b = -1000; b <= 1000; b++){
			int n = 0;
			while (isPrime(abs(n * n + a * n + b))) {
				n++;
			}

			if (n > nMax) {
				if (count == 0){
					count++;
					std::cout << "Finding maximum primes.";
				}
				else
					std::cout << ".";
				aMax = a;
				bMax = b;
				nMax = n;
			}
		}
	}

	std::cout << std::endl << "The coefficients are: a=" << aMax << " and b=" << bMax << std::endl << "The answer is: " << aMax*bMax << std::endl;
	system("Pause");
	return 0;
}