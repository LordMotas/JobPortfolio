/*

Project Euler #42
Problem Statement:
The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. 
For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. 
If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt, a 16K text file containing nearly two-thousand common English words, how many are triangle words?

*/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

int main(){
	std::vector<int> triangleNumbers(26);
	double i = 0;
	//generate the triangle numbers
	std::generate(triangleNumbers.begin(), triangleNumbers.end(), [&](){i++;int answer = (i / 2) * (i + 1);return answer;});

	//Input the word file
	std::fstream fin;
	std::stringstream sin;
	fin.open("words.txt", std::ios::out | std::ios::in);

	std::vector<std::string> wordVector;
	bool startWord = false;
	std::string word = "";
	while (!fin.eof()){
		char nextChar;
		nextChar = fin.get();
		if (nextChar == '\"' && !startWord){
			//std::cout << std::endl << "Start the word" << std::endl;
			startWord = true;
		}
		else if (nextChar == '\"' && startWord){
			//std::cout << std::endl << "End the word" << std::endl;
			wordVector.push_back(word);
			word = "";
			startWord = false;
		}
		else if (nextChar != ','){
			//std::cout << nextChar;
			word += nextChar;
		}
	}

	int numTriangleWords = 0;
	for (int i = 0; i < wordVector.size(); i++){
		int wordTotal = 0;
		for (int j = 0; j < wordVector[i].length(); j++){
			wordTotal += wordVector[i][j] - 64;
		}
		if (triangleNumbers.end() != std::find(triangleNumbers.begin(), triangleNumbers.end(), wordTotal)){
			numTriangleWords++;
		}
	}
	std::cout << "The answer is: " << numTriangleWords << std::endl;
	system("Pause");
	return 0;
}