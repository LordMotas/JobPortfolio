/*
	Project Euler #31
	Problem Statement:

	In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

	1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
	It is possible to make £2 in the following way:

	1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
	How many different ways can £2 be made using any number of coins?

*/

#include <iostream>

int main(){

	int goal = 200;
	int numWays = 0;
	std::cout << "Determining permutations..." << std::endl;
	for (int e2 = goal; e2 >= 0; e2 -= 200)
		for (int e1 = e2; e1 >= 0; e1 -= 100)
			for (int p50 = e1; p50 >= 0; p50 -= 50)
				for (int p20 = p50; p20 >= 0; p20 -= 20)
					for (int p10 = p20; p10 >= 0; p10 -= 10)
						for (int p5 = p10; p5 >= 0; p5 -= 5)
							for (int p2 = p5; p2 >= 0; p2 -= 2)
								numWays++;

	std::cout << "The answer is: " << numWays << std::endl;
	system("Pause");
	return 0;
}