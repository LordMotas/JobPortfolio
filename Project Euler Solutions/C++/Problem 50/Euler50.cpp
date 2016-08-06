/*

Project Euler #50
Problem Statement:
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?

*/

#include <iostream>
#include <vector>
#include <algorithm>

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

int main() {
	std::vector<int> primeVector;
	primeVector.push_back(2);
	int currentAnswer = 0;
	int currentCount = 0;
	std::cout << "Generating primes..." << std::endl;
	for (int i = 3; i < 1000000; i += 2) {
		if (isPrime(i))
			primeVector.push_back(i);
	}
	std::cout << "Calculating the prime sum consisting of the most consecutive primes..." << std::endl;
	for (int l = 0; l < 4; l++) {
		int answer = 0;
		int count = 0;
		for (int j = l; j < primeVector.size(); j++) {
			if ((answer + primeVector[j]) < 1000000) {
				answer += primeVector[j];
				count++;
				if (isPrime(answer) && count > currentCount){
					currentCount = count;
					currentAnswer = answer;
				}
			}
		}
	}
	std::cout << "The answer is: " << currentAnswer << " with " << currentCount << " consecutive primes." << std::endl;
	system("Pause");
	return 0;
}