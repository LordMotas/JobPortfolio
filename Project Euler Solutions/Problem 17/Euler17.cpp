/*
	Project Euler #17
	Problem Statement:

	If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

	If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

	NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main(){

	std::vector<std::string> ones = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	std::vector<std::string> tens = { "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
	std::vector<std::string> teens = { "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	std::vector<std::string> hundreds = { "","onehundred", "twohundred", "threehundred", "fourhundred", "fivehundred", "sixhundred", "sevenhundred", "eighthundred", "ninehundred" };

	std::string final = "";

	for (int k = 0; k < hundreds.size(); k++){
		for (int j = 0; j < tens.size(); j++){
			if (k > 0){
				//std::cout << hundreds[k] << " ";
				final += hundreds[k];
				if (j >= 1){
					//std::cout << "and " << tens[j] << std::endl;
					final = final + "and" + tens[j];
				}
				else{
					//std::cout << std::endl;
				}
			}
			else{
				if (j > 0){
					//std::cout << tens[j] << std::endl;
					final += tens[j];
				}
			}
			for (int i = 0; i < ones.size(); i++){
				if (k > 0){
					//std::cout << hundreds[k] << " and ";
					final = final + hundreds[k] + "and";
				}if (j == 1){
					//std::cout << teens[i] << std::endl;
					final += teens[i];
				}
				else {
					if (j > 0){
						//std::cout << tens[j] << " ";
						final += tens[j];
					}
					//std::cout << ones[i] << std::endl;
					final += ones[i];
				}
			}
		}
	}
	//std::cout << "one thousand" << std::endl;
	final += "onethousand";

	//std::cout << final << std::endl;

	std::cout << "The answer is: " << final.size() << std::endl;
	system("Pause");
	return 0;
}