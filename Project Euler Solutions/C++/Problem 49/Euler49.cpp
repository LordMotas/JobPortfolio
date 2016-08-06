/*

Project Euler #49
Problem Statement:
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: 
(i) each of the three terms are prime, and, 
(ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, 
but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?

*/

#include <iostream>
#include <algorithm>
#include <string>
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
	std::vector<int> consecutivePrimes;
	for (int i = 1000; i < 10000; i++){
		if (isPrime(i)){
			int count = 0;
			int testForPrime = i;
			std::string str = std::to_string(testForPrime);
			do{
				testForPrime = atoi(str.c_str());
				if (isPrime(testForPrime)){
					count++;
					consecutivePrimes.push_back(testForPrime);
					if (count == 3){
						if (consecutivePrimes[2] - consecutivePrimes[1] == consecutivePrimes[1] - consecutivePrimes[0]){
							std::cout << "The answer is: " << consecutivePrimes[0] << consecutivePrimes[1] << consecutivePrimes[2] << std::endl;
							system("Pause");
							return 0;
						}
					}
				}
			} while (std::next_permutation(str.begin(),str.end()));
		}
		consecutivePrimes.clear();
	}	
}