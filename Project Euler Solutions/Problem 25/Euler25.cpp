/*

	Project Euler #25
	Problem Statement:
	The Fibonacci sequence is defined by the recurrence relation:

	Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
	Hence the first 12 terms will be:

	F1 = 1
	F2 = 1
	F3 = 2
	F4 = 3
	F5 = 5
	F6 = 8
	F7 = 13
	F8 = 21
	F9 = 34
	F10 = 55
	F11 = 89
	F12 = 144
	The 12th term, F12, is the first term to contain three digits.

	What is the index of the first term in the Fibonacci sequence to contain 1000 digits?

*/

#include <iostream>
#include <algorithm>
#include <cmath>

int main(){
	auto answer = ceil((1000 - 1 + log10(sqrt(5))) / log10((1 + sqrt(5)) / 2));
	std::cout << "Calculating answer based on the Golden Ratio..." << std::endl;
	std::cout << "The answer is: " << answer << std::endl;

	system("Pause");
	return 0;
}