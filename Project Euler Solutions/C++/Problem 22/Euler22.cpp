/*
	Project Euler #22
	Problem Statement:

	Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over 
	five-thousand first names, begin by sorting it into alphabetical order. Then working out the 
	alphabetical value for each name, multiply this value by its alphabetical position in the list 
	to obtain a name score.

	For example, when the list is sorted into alphabetical order, COLIN, which is 
	worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. 
	So, COLIN would obtain a score of 938 × 53 = 49714.

	What is the total of all the name scores in the file?

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int alphabetInteger(char letter){
	switch (letter){
	case 'A':
		return 1;
	case 'B':
		return 2;
	case 'C':
		return 3;
	case 'D':
		return 4;
	case 'E':
		return 5;
	case 'F':
		return 6;
	case 'G':
		return 7;
	case 'H':
		return 8;
	case 'I':
		return 9;
	case 'J':
		return 10;
	case 'K':
		return 11;
	case 'L':
		return 12;
	case 'M':
		return 13;
	case 'N':
		return 14;
	case 'O':
		return 15;
	case 'P':
		return 16;
	case 'Q':
		return 17;
	case 'R':
		return 18;
	case 'S':
		return 19;
	case 'T':
		return 20;
	case 'U':
		return 21;
	case 'V':
		return 22;
	case 'W':
		return 23;
	case 'X':
		return 24;
	case 'Y':
		return 25;
	case 'Z':
		return 26;
	default:
		return 0;
	}
}

int main(){

	int finalAnswer = 0;
	std::vector<std::string> nameArray;
	std::ifstream fin;
	fin.open("names.txt");
	std::cout << "Extracting data from file..." << std:endl;
	while (fin)
	{
		std::string s;
		if (!getline(fin, s)) break;
		std::istringstream ss(s);

		while (ss){
			std::string s;
			if (!getline(ss, s, ',')) break;
			nameArray.push_back(s);
		}
	}

	fin.close();
	
	//Sort the array alphabetically
	std::cout << "Sorting names in file..." << std::endl;
	std::sort(nameArray.begin(), nameArray.end());

	std::string name;
	std::cout << "Calculating name scores..." << std::endl;
	for (int i = 0; i < nameArray.size(); i++){
		name = nameArray[i];
		int alphabetTotal = 0;
		for (int j = 0; j < name.size(); j++){
			//Put name[j] into a table to get the value
			alphabetTotal += alphabetInteger(name[j]);
		}
		//Store the alphabetical value for the name
		nameArray[i] = alphabetTotal;
		//Multiply it by the position in the list and add to the final answer
		finalAnswer += (i + 1)*alphabetTotal;
	}

	std::cout << "The answer is: " << finalAnswer << std::endl;

	system("Pause");
	return 0;
}