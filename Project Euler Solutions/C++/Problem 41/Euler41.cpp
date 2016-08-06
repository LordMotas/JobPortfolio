/*

Project Euler #41
Problem Statement:
We shall say that an n - digit number is pandigital if it makes use of all the digits 1 to n exactly once.
For example, 2143 is a 4 - digit pandigital and is also prime.

What is the largest n - digit pandigital prime that exists ?

*/

#include <iostream>
#include <algorithm>
#include <string>

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
	int largestPrime = 0;
	for (int i = 7654321; i > 1234567; i-=2){
		std::string searchString = std::to_string(i);
		if (searchString.end() != std::find(searchString.begin(), searchString.end(), '1') &&
			searchString.end() != std::find(searchString.begin(), searchString.end(), '2') &&
			searchString.end() != std::find(searchString.begin(), searchString.end(), '3') &&
			searchString.end() != std::find(searchString.begin(), searchString.end(), '4') &&
			searchString.end() != std::find(searchString.begin(), searchString.end(), '5') &&
			searchString.end() != std::find(searchString.begin(), searchString.end(), '6') &&
			searchString.end() != std::find(searchString.begin(), searchString.end(), '7') &&
			isPrime(i)){
				std::cout << "The answer is: " << i << std::endl;
				system("Pause");
				return 0;
		}
	}
}