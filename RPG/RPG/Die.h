#pragma once

/*
Every die has a set number of sides, can be rolled (select a random value in the appropriate range), and keeps
track of the value of the last roll it made.
*/

class Die {
private:
	int numSides;
	int value;
public:
	int rollDie() {
		//Roll a random number between 1 and the number of sides
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> random(1, this->numSides);
		this->value = random(mt);
		return this->value;
	};

	Die(int numberOfSides) {
		this->numSides = numberOfSides;
	};
};