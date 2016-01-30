/*
	Project Euler # 12
	Problem Statement:

	The sequence of triangle numbers is generated by adding the natural numbers. 
	So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:

	1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

	Let us list the factors of the first seven triangle numbers:

	1: 1
	3: 1,3
	6: 1,2,3,6
	10: 1,2,5,10
	15: 1,3,5,15
	21: 1,3,7,21
	28: 1,2,4,7,14,28
	We can see that 28 is the first triangle number to have over five divisors.

	What is the value of the first triangle number to have over five hundred divisors?

	WARNING: This program takes a long time to run...but the answer is: 76576500
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	//std::vector<long long> triangle(100000);
	long long sum = 0;
	auto check = 0;

	for (long long i = 0; i <= 100000; i++){
		sum += i;
		auto count = 0;
		for (long long k = 1; k <= sum; k++){
			if (sum % k == 0){
				count++;
				if (count > check){
					check = count;
					std::cout << "c: " << check << std::endl;
				}
				if (count >= 500){
					std::cout << "The solution is: " << sum << std::endl;
					system("Pause");
					return 0;
				}
			}
		}
	}
	std::cout << check << std::endl;
	system("Pause");
	return 0;
}