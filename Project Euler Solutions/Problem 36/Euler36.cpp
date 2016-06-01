/*

Project Euler #36
Problem Statement:

The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)

*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main(){
	std::vector<std::string> palindromeBaseTen;
	std::vector<std::string> palindromeBaseTwo;
	int finalSum = 0;
	for (int i = 1; i < 1000000; i++){
		std::string binaryString = "";
		int number = i;
		while (number > 1)
		{
			binaryString += std::to_string(number % 2);
			number /= 2;
		}
		binaryString += std::to_string(1);
		//Checks if binaryString is a palindrome or not
		if (std::equal(binaryString.begin(), binaryString.end(), binaryString.rbegin())){
			palindromeBaseTwo.push_back(binaryString);
			//Checks if the original number is a palindrome or not
			std::string baseTenString = std::to_string(i);
			if (std::equal(baseTenString.begin(), baseTenString.end(), baseTenString.rbegin())){
				palindromeBaseTen.push_back(baseTenString);
				//This means that both numbers are palindromes
			}
		}
	}
	for (int i = 0; i < palindromeBaseTen.size(); i++){
		finalSum += atoi(palindromeBaseTen[i].c_str());
	}
	std::cout << "The answer is: " << finalSum << std::endl;
	system("Pause");
	return 0;
}