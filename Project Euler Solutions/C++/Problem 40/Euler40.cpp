/*

Project Euler #40
Problem Statement:
An irrational decimal fraction is created by concatenating the positive integers:

0.12345678910 1 112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000

*/

#include <iostream>
#include <string>

int main(){
	std::string irrationalFraction = "0.";
	for (int i = 1; i < 1000000; i++){
		irrationalFraction += std::to_string(i);
		if (irrationalFraction.size() >= 1000002)
			break;
	}
	irrationalFraction = irrationalFraction.substr(2, 1000000);
	int answer = (irrationalFraction[0] - '0')*(irrationalFraction[9] - '0')*(irrationalFraction[99] - '0')*(irrationalFraction[999] - '0')*(irrationalFraction[9999] - '0')*(irrationalFraction[99999] - '0')*(irrationalFraction[999999] - '0');
	std::cout << "The answer is: " << answer << std::endl;
	system("Pause");
	return 0;
}