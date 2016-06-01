/*

Project Euler #35
Problem Statement:

The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?

*/

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
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
	std::vector<int> circularPrimes;
	int totalPrimes = 0;
	for (int j = 0; j < 1000000; j++){
		int numPrimes = 0;
		std::string str = std::to_string(j);
		for (int i = 0; i < str.length(); i++){
			//Rotate the number
			std::rotate(str.begin(), str.begin() + 1, str.end());
			int test = atoi(str.c_str());
			//Now check if the number is prime
			if (isPrime(test)){
				numPrimes++;
			}
		}
		//If the number of primes equals the length of the string, then it's a circular prime.
		if (numPrimes == str.length()){
			circularPrimes.push_back(atoi(str.c_str()));
			totalPrimes++;
		}
	}
	std::cout << "The answer is: " << totalPrimes << std::endl;
	system("Pause");
	return 0;
}