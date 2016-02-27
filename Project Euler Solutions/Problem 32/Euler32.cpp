/*
	Project Euler #32
	Problem Statement:

	We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, 
	the 5-digit number, 15234, is 1 through 5 pandigital.

	The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

	Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

	HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

*/

#include <iostream>
#include <string>
#include <vector>

int main(){
	int oneCount = 0, twoCount = 0, threeCount = 0,
		fourCount = 0, fiveCount = 0, sixCount = 0,
		sevenCount = 0, eightCount = 0, nineCount = 0,
		zeroCount = 0;
	std::vector<int> productVector;
	std::vector<int> multiplicandVector;
	std::vector<int> multiplierVector;
	std::cout << "Searching for multipliers, multiplicands, and products..." << std::endl;
	for (int i = 0; i < 2000; i++){
		for (int j = 0; j < 2000; j++){
			std::string product = std::to_string(i*j);
			std::string multiplicand = std::to_string(i);
			std::string multiplier = std::to_string(j);
			if (product.size() + multiplicand.size() + multiplier.size() == 9){
				for (int k = 0; k < multiplicand.size(); k++){
					switch (multiplicand[k]){
					case '1':
						oneCount++;
						break;
					case '2':
						twoCount++;
						break;
					case '3':
						threeCount++;
						break;
					case '4':
						fourCount++;
						break;
					case '5':
						fiveCount++;
						break;
					case '6':
						sixCount++;
						break;
					case '7':
						sevenCount++;
						break;
					case '8':
						eightCount++;
						break;
					case '9':
						nineCount++;
						break;
					case '0':
						zeroCount++;
					}
				}
				for (int l = 0; l < multiplier.size(); l++){
					switch (multiplier[l]){
					case '1':
						oneCount++;
						break;
					case '2':
						twoCount++;
						break;
					case '3':
						threeCount++;
						break;
					case '4':
						fourCount++;
						break;
					case '5':
						fiveCount++;
						break;
					case '6':
						sixCount++;
						break;
					case '7':
						sevenCount++;
						break;
					case '8':
						eightCount++;
						break;
					case '9':
						nineCount++;
						break;
					case '0':
						zeroCount++;
					}
				}
				for (int m = 0; m < product.size(); m++){
					switch (product[m]){
					case '1':
						oneCount++;
						break;
					case '2':
						twoCount++;
						break;
					case '3':
						threeCount++;
						break;
					case '4':
						fourCount++;
						break;
					case '5':
						fiveCount++;
						break;
					case '6':
						sixCount++;
						break;
					case '7':
						sevenCount++;
						break;
					case '8':
						eightCount++;
						break;
					case '9':
						nineCount++;
						break;
					case '0':
						zeroCount++;
						break;
					}
				}
				if (oneCount == 1 && twoCount == 1 && threeCount == 1 &&
					fourCount == 1 && fiveCount == 1 && sixCount == 1 &&
					sevenCount == 1 && eightCount == 1 && nineCount == 1 &&
					zeroCount == 0){
					if (std::find(productVector.begin(), productVector.end(), std::stoi(product)) == productVector.end()){
						productVector.push_back(std::stoi(product));
						multiplicandVector.push_back(std::stoi(multiplicand));
						multiplierVector.push_back(std::stoi(multiplier));
					}
				}
				zeroCount = 0;
				oneCount = 0;
				twoCount = 0;
				threeCount = 0;
				fourCount = 0;
				fiveCount = 0;
				sixCount = 0;
				sevenCount = 0;
				eightCount = 0;
				nineCount = 0;
			}
		}
	}
	std::cout << "Summing all results..." << std::endl;
	int answer = 0;
	for (int n = 0; n < productVector.size(); n++){
		answer += productVector[n];
	}
	std::cout << "The answer is: " << answer << std::endl;
	system("Pause");
	return 0;
}