/*
	Project Euler #33
	Problem Statement:

	The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

	We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

	There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

	If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

*/

#include <iostream>
#include <algorithm>

unsigned int gcd(unsigned int n1, unsigned int n2) {
	return (n2 == 0) ? n1 : gcd(n2, n1 % n2);
}

int main(){

	std::cout << "Solutions have the form: (10n+i)/(10i+d)=n/d" << std::endl;
	std::cout << "All solutions follow the rule: n > d > i" << std::endl;

	int denominatorProduct = 1;
	int numeratorProduct = 1;

	for (int i = 1; i < 10; i++){
		for (int denominator = 1; denominator < i; denominator++){
			for (int numerator = 1; numerator < denominator; numerator++){
				if ((numerator * 10 + i) * denominator == numerator * (i * 10 + denominator)){
					denominatorProduct *= denominator;
					numeratorProduct *= numerator;
				}
			}
		}
	}

	denominatorProduct /= gcd(numeratorProduct, denominatorProduct);

	std::cout << "The answer is: " << denominatorProduct << std::endl;
	system("Pause");
	return 0;
}