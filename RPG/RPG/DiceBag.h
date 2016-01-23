#pragma once

/*
The DiceBag is able to produce any kind of die needed for any kind of roll. When the GM needs to roll dice, it
tells the DiceBag how many dice need to be rolled, how many sides each die has, and whether there is a modifier (+2, -7,
etc). While the modifier is optional, every die roll will have at least one die which will have at least two sides. The GM
may ask for any number of dice with any number of sides. This means that 12d34 (meaning 12 dice, each containing 34
sides) is a completely legit request. The DiceBag’s job is to take the request, create the appropriate die (or dice), roll
it/them the correct number of times, add the modifier (if any) to the total, and return the result.
*/

class DiceBag {
public:
	int getDice(int numDice, int numSides, int modifier = 0) {
		auto sum = 0;
		for (auto i = 0; i < numDice; i++) {
			Die die(numSides);
			sum += die.rollDie();
		}
		sum += modifier;
		return sum;
	}
};