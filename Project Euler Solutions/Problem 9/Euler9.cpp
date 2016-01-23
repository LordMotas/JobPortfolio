/*
  Project Euler #9
  Problem Statement:

  A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

  a^2 + b^2 = c^2
  For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

  There exists exactly one Pythagorean triplet for which a + b + c = 1000.
  Find the product abc.

*/

#include <iostream>
#include <cmath>

int main(){

	for (int i = 0; i < 500; i++){
		for (int j = 0; j < 500; j++){
			for (int k = 0; k < 500; k++){
				if (pow(i, 2) + pow(j, 2) == pow(k, 2)){
					if (i + j + k == 1000 && i < j && j < k){
						std::cout << "Pythagorean Triple is: " << i << ", " << j << ", " << k << std::endl;
						std::cout << "Product of the triple is: " << i*j*k << std::endl;
					}
				}
			}
		}

	}

	system("Pause");
	return 0;
}