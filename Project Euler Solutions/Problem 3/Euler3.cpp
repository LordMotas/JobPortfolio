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
	int finalAnswer;

	std::cout << "Checking divisibility for 600851475143..." << std::endl;
	for (int i = 2; i < num; i++)
	{
		while (num % i == 0) // check for divisibility
		{
			num /= i;
			finalAnswer = num;
		}
		// at this point, i cannot be a divisor of the (possibly modified) num.
	}

	std::cout << "The answer is: " << finalAnswer << std::endl;
	
	system("Pause");
	return 0;
}