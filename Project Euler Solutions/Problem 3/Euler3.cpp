/*
  Project Euler # 3
  Problem Statement:

  The prime factors of 13195 are 5, 7, 13 and 29.

  What is the largest prime factor of the number 600851475143?
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	long long int num = 600851475143;

	for (int i = 2; i <= num; i++)
	{
		while (num % i == 0) // check for divisibility
		{
			num /= i;
			std::cout << i << std::endl;
		}
		// at this point, i cannot be a divisor of the (possibly modified) num.
	}

	system("Pause");
	return 0;
}