/*
Project Euler #4
Problem Statement:
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 Å~ 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int ReverseNumber(int n, int partial = 0){
	if (n == 0)
		return partial;
	return ReverseNumber(n / 10, partial * 10 + n % 10);
}

int main(){

	std::vector<int> palindrome(899);
	auto i = 100;
	std::generate(palindrome.begin(), palindrome.end(), [&](){return i++; });
	std::vector<int> solutions;
	auto k = 0;

	for (int a = 898; a > 0; a--){
		for (int b = 898; b > 0; b--){
			if (ReverseNumber((palindrome[a] * palindrome[b])) == (palindrome[a] * palindrome[b])){
				solutions.push_back(palindrome[a] * palindrome[b]);
			}
		}
	}

	auto trueSolution = 0;
	for (int j = 0; j < solutions.size(); j++){
		if (solutions[j] > trueSolution){
			trueSolution = solutions[j];
		}
	}
	std::cout << "The answer is: " << trueSolution << std::endl;

	system("Pause");
	return 0;
}