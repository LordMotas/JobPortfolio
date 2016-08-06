/*
  Project Euler #1
  Problem Statement:
	
  If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. 
	The sum of these multiples is 23.

  Find the sum of all the multiples of 3 or 5 below 1000.
	
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	std::vector<int> thousandNumbers(1000);
	auto i = 0;
	std::cout << "Filling array with numbers 1-1000..." << std::endl;
	std::generate(thousandNumbers.begin(), thousandNumbers.end(), [&](){return i++; });
	auto total = 0;

	std::cout << "Finding multiples of 3 or 5..." << std::endl;
	for (int i = 0; i < 1000; i++){
		if ((thousandNumbers[i] % 3) == 0 || (thousandNumbers[i] % 5) == 0){
			total += thousandNumbers[i];
		}
	}
	std::cout << "The answer is: " << total << std::endl;

	system("Pause");
	return 0;
}