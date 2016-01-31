/*
	Project Euler #21
	Problem Statement:
	
	Let d(n) be defined as the sum of proper divisors of n 
	(numbers less than n which divide evenly into n).
	If d(a) = b and d(b) = a, where a ÅÇ b, then a and b are an amicable pair and each 
	of a and b are called amicable numbers.

	For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; 
	therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

	Evaluate the sum of all the amicable numbers under 10000.

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	std::vector<int> divisorArray;
	int finalTotal = 0;
	std::vector<int> answerArray;
		
	//Every number from 1 to 10000
	std::cout << "Finding divisors..." << std::endl;
	for (int k = 1; k < 10000; k++){
		for (int l = 1; l < k; l++){
			//If l is a proper divisor of k
			if (k % l == 0){
				divisorArray.push_back(l);
			}
		}
		//divisorArray now contains all the proper divisors of k
		int sum1 = 0;

		//Sum the values
		for (int m : divisorArray)
			sum1 += m;
		divisorArray.clear();
		
		//Find the divisors of the sum
		for (int n = 1; n < sum1; n++){
			if (sum1 % n == 0){
				divisorArray.push_back(n);
			}
		}
		int sum2 = 0;

		//Sum the divisors of the sum
		for (int m : divisorArray)
			sum2 += m;

		//If there is a match
		if (sum2 == k && sum2 != sum1){
			//If the value wasn't already in the array
			if (std::find(answerArray.begin(), answerArray.end(), k) == answerArray.end())
				answerArray.push_back(k);
		}
		//Remove all elements and start over
		divisorArray.clear();
	}

	//Sum all elements of the array
	std::cout << "Summing amicable numbers..." << std::endl;
	for (int a : answerArray)
		finalTotal += a;

	std::cout << "The answer is: " << finalTotal << std::endl;
	
	system("Pause");
	return 0;
}