/*

Project Euler #47
Problem Statement:
The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2^2 × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers?

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

std::vector<int> primes;

bool isPrime(int num)
{
	if (num <= 1)
		return false;
	else if (num == 2)
		return true;
	else if (num % 2 == 0)
		return false;
	else
	{
		bool prime = true;
		int divisor = 3;
		double num_d = static_cast<double>(num);
		int upperLimit = static_cast<int>(sqrt(num_d) + 1);

		while (divisor <= upperLimit)
		{
			if (num % divisor == 0)
				prime = false;
			divisor += 2;
		}
		return prime;
	}
}

int numPrimeFactors(int number) {
	int nod = 0;
	bool pf;
	int remain = number;

	for (int i = 0; i < (int)primes.size(); i++) {
		if (primes[i] * primes[i] > number) {
			return ++nod;
		}
		pf = false;
		while (remain % primes[i] == 0) {
			pf = true;
			remain = remain / primes[i];
		}
		if (pf) {
			nod++;
		}
		if (remain == 1) {
			return nod;
		}
	}
	return 0;
}

int main() {
	int targetpf = 4;
	int targetConsec = 4;
	int consec = 1;
	int result = 2 * 3 * 5 * 7;
	
	primes.push_back(2);
	
	for (int i = 3; i < 100000; i += 2) {
		if (isPrime((int)i))
			primes.push_back(i);
	}
	
	while (consec < targetConsec) {
		result++;
		if (numPrimeFactors(result) >= targetpf) {
			consec++;
		}
		else {
			consec = 0;
		}
	}
	std::cout << "The answer is: " << result - 4 << std::endl;
	system("Pause");
	return 0;
}