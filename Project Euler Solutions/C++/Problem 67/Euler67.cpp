/*
	Project Euler #67
	Problem STatement:
	By starting at the top of the triangle below and moving to adjacent numbers on the row below, 
	the maximum total from top to bottom is 23.

	3
	7 4
	2 4 6
	8 5 9 3

	That is, 3 + 7 + 4 + 9 = 23.

	Find the maximum total from top to bottom in triangle.txt (right click and 'Save Link/Target As...'), 
	a 100K text file containing a triangle with one-hundred rows.

	NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route to solve this 
	problem, as there are 299 altogether! If you could check one trillion (1012) routes every second it would take over 
	twenty billion years to check them all. There is an efficient algorithm to solve it. ;o)

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <fstream>
#include <ios>

int recSumAtRow(std::array<int, 100>[100], int);

int main(){

	std::array<int, 100> rows[100];
	//Read in rows from a file

	std::cout << "Opening file of data..." << std::endl;
	std::fstream fin;
	fin.open("triangle.txt", std::ios::out | std::ios::in);

	int size = 0, i = 0;

	while (!fin.eof()){
		fin >> rows[size][i];
		if (i == size){
			i = -1;
			size++;
		}
		i++;
		if (size == 100 && i == 100){
			int yes = 0;
		}
	}
	std::cout << "Traversing triangle..." << std::endl;
	auto answer = recSumAtRow(rows, rows[size].size() - 2);

	std::cout << "The answer is: " << answer << std::endl;

	system("Pause");
	return 0;
}

int recSumAtRow(std::array<int, 100> rowData[100], int rowNum){
	for (int i = 0; i < rowData[rowNum].size() - 1; i++){
		rowData[rowNum][i] += std::max(rowData[rowNum + 1][i], rowData[rowNum + 1][i + 1]);
	}
	if (rowData[rowNum].size() == 1){
		return rowData[rowNum][0];
	}
	else{
		if (rowNum == 0){
			return rowData[rowNum][0];
		}
		return recSumAtRow(rowData, rowNum - 1);
	}
}