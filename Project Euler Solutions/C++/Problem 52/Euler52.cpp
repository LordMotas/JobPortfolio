/*

Project Euler #52
Problem Statement:
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.

*/

#include <iostream>
#include <string>
#include <algorithm>

int main(){
	int numDigits = 0;
	for (int i = 125874; i < 1000000; i++){
		numDigits = 0;
		std::string baseNumber = std::to_string(i);
		std::string twoNumber = std::to_string(2*i);
		std::string threeNumber = std::to_string(3*i);
		std::string fourNumber = std::to_string(4*i);
		std::string fiveNumber = std::to_string(5*i);
		std::string sixNumber = std::to_string(6*i);
		if (baseNumber.length() == twoNumber.length() && 
			twoNumber.length() == threeNumber.length() && 
			threeNumber.length() == fourNumber.length() && 
			fourNumber.length() == fiveNumber.length() && 
			fiveNumber.length() == sixNumber.length()){

			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '0') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '0') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '0') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '0') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '0') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '0')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '1') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '1') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '1') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '1') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '1') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '1')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '2') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '2') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '2') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '2') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '2') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '2')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '3') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '3') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '3') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '3') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '3') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '3')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '4') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '4') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '4') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '4') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '4') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '4')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '5') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '5') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '5') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '5') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '5') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '5')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '6') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '6') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '6') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '6') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '6') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '6')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '7') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '7') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '7') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '7') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '7') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '7')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '8') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '8') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '8') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '8') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '8') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '8')){

				numDigits++;
			}
			if (baseNumber.end() != std::find(baseNumber.begin(), baseNumber.end(), '9') &&
				twoNumber.end() != std::find(twoNumber.begin(), twoNumber.end(), '9') &&
				threeNumber.end() != std::find(threeNumber.begin(), threeNumber.end(), '9') &&
				fourNumber.end() != std::find(fourNumber.begin(), fourNumber.end(), '9') &&
				fiveNumber.end() != std::find(fiveNumber.begin(), fiveNumber.end(), '9') &&
				sixNumber.end() != std::find(sixNumber.begin(), sixNumber.end(), '9')){

				numDigits++;
			}
		}
		if (numDigits == baseNumber.length()){
			std::cout << "The answer is: " << baseNumber << std::endl;
			system("Pause");
			return 0;
		}
	}
}