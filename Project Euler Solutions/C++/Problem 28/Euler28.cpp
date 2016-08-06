/*
	Project Euler #28
	Problem Statement:
	Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

	21 22 23 24 25
	20  7  8  9 10
	19  6  1  2 11
	18  5  4  3 12
	17 16 15 14 13

	It can be verified that the sum of the numbers on the diagonals is 101.

	What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

*/

#include <iostream>
#include <math.h>

long long f(long long n){
	if (n == 0)
		return n;
	return 4 * pow((2 * n + 1), 2) - 12 * n + f(n - 1);
}

int main(){
	std::cout << "The problem can be derived as a formula..." << std::endl;
	std::cout << "f(n) where n is the number of rings in the spiral..." << std::endl;
	std::cout << "The sides are 2n+1 wide..." << std::endl;
	std::cout << "The upper right corner is therefore (2n+1)^2..." << std::endl;
	std::cout << "The second corner is (2n+1)^2-2n..." << std::endl;
	std::cout << "Summing all the corners is 4(2n+1)^2-2n..." << std::endl;
	std::cout << "Summing all of the diagonals 4(2n+1)^2-12+f(n-1)..." << std::endl;
	long long answer = f(500);
	std::cout << "The answer is: " << answer << std::endl;
	system("Pause");
	return 0;
}