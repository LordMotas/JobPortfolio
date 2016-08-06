/*

Project Euler #46
Problem Statement:
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×1^2
15 = 7 + 2×2^2
21 = 3 + 2×3^2
25 = 7 + 2×3^2
27 = 19 + 2×2^2
33 = 31 + 2×1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

*/

#include <iostream>
#include <vector>

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

int main(){
	std::vector<int> notPrimes;
	std::vector<int> primes;
	std::vector<int> twiceASquare;
	for (int j = 0; j < 71; j++) {
		twiceASquare.push_back(2 * pow(j, 2));
	}
	for(int i = 1; i < 10000; i+=2){
		if(!isPrime(i))
			notPrimes.push_back(i);
		else
			primes.push_back(i);
	}
	bool satisfies = false;
	//For every composite number
	for (int i = 1; i < notPrimes.size(); i++) {
		//Check every prime
		for (int j = 0; j < primes.size(); j++) {
			//Check every twice a square
			for (int k = 0; k < twiceASquare.size(); k++) {
				if ((notPrimes[i] - primes[j] - twiceASquare[k]) == 0) {
					satisfies = true;
					goto checkCondition;
				}
			}
		}
		checkCondition:
		if (satisfies)
			satisfies = false;
		else {
			std::cout << "The answer is: " << notPrimes[i] << std::endl;
			system("Pause");
			return 0;
		}
	}
}