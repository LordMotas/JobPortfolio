/*
Project Euler #15
Problem Statement:

Starting in the top left corner of a 2Å~2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20Å~20 grid?

*/

#include <iostream>
#include <cmath>

long long Factorial(long long x) {
	if (x == 1)
		return x;
	else
		return x * Factorial(x - 1);
}
 
int main(){

	//Given the equation (2n)!/(n!)^2
	//Still not sure why I add 1 at the end

	int n = 20;

	long long answer = exp(lgamma((n + n) + 1)) / (exp(lgamma(n + 1))*exp(lgamma(n + 1)));
	std::cout << "The answer is: " << answer+1 << std::endl;

	system("Pause");
	return 0;
}