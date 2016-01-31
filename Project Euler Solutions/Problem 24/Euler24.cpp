/*

	Project Euler #24
	Problem Statement:

	A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

	012   021   102   120   201   210

	What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

*/

#include <iostream>
#include <algorithm>

int main(){

	int integers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::sort(integers, integers + 10);
	int count = 0;
	std::cout << "Calculating permutations..." << std::endl;
	do{
		count++;
		if (count == 1000000){
			std::cout << "The answer is: ";
			for (int i = 0; i < 10; i++)
				std::cout << integers[i] << ' ';
			std::cout << std::endl;
			system("Pause");
			return 0;
		}
	} while (std::next_permutation(integers, integers + 10));

	return 0;
}