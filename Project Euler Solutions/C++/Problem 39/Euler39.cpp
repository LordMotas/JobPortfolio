/*
Project Euler #39
Problem Statement:
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?

*/

#include <iostream>
#include <vector>

int main(){

	//a^2+b^2=c^2
	int maxSolutions = 0;
	int maxPerimeterValue = 0;
	int numSolutions;
	std::cout << "Current Maximums" << std::endl;
	std::vector<std::vector<int>> pythagoreanTriple;
	std::vector<int> ijkArray;
	for (int perimeter = 12; perimeter <= 1000; perimeter += 12){
		numSolutions = 0;
		for (int i = 1; i <= perimeter; i++){
			for (int j = 1; j <= perimeter; j++){
				for (int k = 1; k <= perimeter; k++){
					if (((i*i) + (j*j) == (k*k)) && i + j + k == perimeter){
						ijkArray.push_back(i);
						ijkArray.push_back(j);
						ijkArray.push_back(k);
						pythagoreanTriple.push_back(ijkArray);
						numSolutions++;
						ijkArray.clear();
					}
				}
			}
		}
		if (numSolutions != 0){
			numSolutions /= 2;
			pythagoreanTriple.clear();
			if (maxSolutions < numSolutions){
				maxSolutions = numSolutions;
				maxPerimeterValue = perimeter;
				std::cout << "Solutions: " << maxSolutions << " " << "Perimeter Value: " << perimeter << std::endl;
			}
		}
	}

	std::cout << "The answer is perimeter value of " << maxPerimeterValue << " with " << maxSolutions << std::endl;
	system("Pause");
	return 0;
}