/*
	Project Euler #18
	Problem Statement:
	
	By starting at the top of the triangle below and moving to adjacent numbers on the row below, 
	the maximum total from top to bottom is 23.

	   3
	  7 4
	 2 4 6
	8 5 9 3

	That is, 3 + 7 + 4 + 9 = 23.

	Find the maximum total from top to bottom of the triangle below:

	              75
	             95 64
	            17 47 82
	           18 35 87 10
	          20 04 82 47 65
	         19 01 23 75 03 34
	        88 02 77 73 07 63 67
	       99 65 04 28 06 16 70 92
	      41 41 26 56 83 40 80 70 33
	     41 48 72 33 47 32 37 16 94 29
	    53 71 44 65 25 43 91 52 97 51 14
	   70 11 33 28 77 73 17 78 39 68 17 57
	  91 71 52 38 17 14 91 43 58 50 27 29 48
	 63 66 04 68 89 53 67 30 73 16 69 87 40 31
	04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

	NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. 
	However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot 
	be solved by brute force, and requires a clever method!
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <fstream>
#include <ios>

int recSumAtRow(std::array<int,15> [15], int);

int main(){

	std::array<int, 15> rows[15];
	//Read in rows from a file

	std::fstream fin;
	fin.open("problem-18-data.txt", std::ios::out | std::ios::in);

	int size = 0, i = 0;

	while (!fin.eof()){
		fin >> rows[size][i];
		if (i == size){
			i = -1;
			size++;
		}
		i++;
	}
	auto answer = recSumAtRow(rows, rows[size].size()-2);

	std::cout << "The answer is: " << answer << std::endl;

	system("Pause");
	return 0;
}

int recSumAtRow(std::array<int,15> rowData[15], int rowNum){
	for (int i = 0; i < rowData[rowNum].size() - 1; i++){
		rowData[rowNum][i] += std::max(rowData[rowNum+1][i],rowData[rowNum+1][i+1]);
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