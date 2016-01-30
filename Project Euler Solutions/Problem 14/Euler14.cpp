/*
	Project Euler #14
	Problem Statement:

	The following iterative sequence is defined for the set of positive integers:

	n Å® n/2 (n is even)
	n Å® 3n + 1 (n is odd)

	Using the rule above and starting with 13, we generate the following sequence:

	13 Å® 40 Å® 20 Å® 10 Å® 5 Å® 16 Å® 8 Å® 4 Å® 2 Å® 1
	It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. 
	Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

	Which starting number, under one million, produces the longest chain?

	NOTE: Once the chain starts the terms are allowed to go above one million.

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	std::vector<long long> collatz(1000000);
	auto i = 1000000;
	std::generate(collatz.begin(), collatz.end(), [&](){return i--; });
	
	auto chainMax = 0;
	long long answer;

	for (int i = 0; i < collatz.size(); i++){
		bool cont = true;
		auto count = 1;
		long long temp = collatz[i];
		while (cont == true){
			if (collatz[i] == 1){
				cont = false;
				if (count > chainMax && count < 1000000){
					chainMax = count;
					answer = temp;
					//std::cout << chainMax << " " << answer << std::endl;
				}
			}
			else if (collatz[i] % 2 == 0){
				//It is even
				collatz[i] = (collatz[i] / 2);
				count++;
			}
			else{
				//It is odd
				collatz[i] = (3 * collatz[i] + 1);
				count++;
			}
		}
	}

	std::cout << "The solution is: " << answer << std::endl;

	system("Pause");
	return 0;
}