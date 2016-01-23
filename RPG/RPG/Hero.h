#pragma once

/*
The Hero is the most complicated class in this lab. The Hero is identified by his/her name and has three
attributes (discussed shortly), bonuses based on the attributes, base and current Health Points (HP), and base and
current Magic Points (MP). In general it is better to have higher values in each of these stats
The attributes are Strength, Dexterity, and Intelligence. Strength affects how much HP you have and the damage
you deal in combat, Dexterity indicates your ability to successfully land attacks as well as dodge those of your enemies,
and Intelligence determines your Magic Points and Spell Strength.

? For each attribute Roll 3d6 (that’s three six-sided dice) for a possible value range of 3-18.
o If your total is 16 or higher, roll an additional 1d6
? If that bonus die results in a 6, roll another bonus die. Regardless of the result, stop rolling
? This means that the max value a starting attribute may have is 30

? Base HP is initially equal to Strength x 10. When the character is first created, the Current HP is equal to the Base HP
? A Damage Bonus will apply to high Strength characters. The Damage Bonus is equal to every point of Strength
over 15. For example, if a character has a Strength attribute of 19, the Damage Bonus would be 4.
? A negative Damage Bonus applies for every point below 10.

? A Strike Bonus is awarded for high Dexterity characters. The Strike Bonus gains +1 for every TWO points above
14. A character with a Dexterity attribute of 15 has a Strike Bonus of +0, but a character of Dexterity 16 gains a
Strike Bonus of +1. A character of Dexterity 20 would have a Strike Bonus of +3
? A negative Strike Bonus applies for every TWO points below 10, giving a character with a Dexterity of 6 a Strike Bonus of -2.
? A Dodge Bonus is awarded to high Dexterity characters as well. For every TWO points over 15, the character
gains a +1 to his/her Dodge Bonus. This means characters with a Dexterity of 17 or 18 gain a Dodge Bonus of +1.
? A negative Dodge Bonus applies for every TWO points below 11. Characters with a Dexterity of 7 or 6 both have a Dodge Bonus of -2.

? A character‘s Base MP is determined by multiplying his/her intelligence by 5. When a character is first created,
the Current MP is always set equal to the Base MP.
? A character with a high Intelligence attribute also gains a spell strength bonus. For every point over 15, his/her
Spell Strength gains +2.
? Likewise, a negative penalty is applied to Spell Strength when the character has a low Intelligence. Spell Strength
receives a -2 for every point below 10.

Finally, the Hero class needs to implement an override of the toString() method. This method will create a string
containing all of the Hero’s information formatted in a useful way. Think “label & value” for each point of data in the
Hero. The format is up to you, but you will be assessed on readability, clarity, and thoroughness.
*/

class Hero {
private:
	std::string name;
public:
	int currentHP;
	int baseHealthPoints;
	int currentMP;
	int baseMagicPoints;
	int strength;
	int strengthMod;
	int dexterity;
	int dexMod;
	int intelligence;
	int intMod;
	void calculateStrengthMod() {
		if (this->strength > 15)
			this->strengthMod = (this->strength - 15);
		else if (this->strength < 10)
			this->strengthMod = (10 - this->strength);
	}
	void calculateIntelligenceMod() {
		if (this->intelligence > 15)
			this->intMod = (this->intelligence - 15) * 2;
		else if (this->intelligence < 10)
			this->intMod = (10 - this->intelligence) * 2;
	}
	void calculateDexterityMod() {
		if (this->dexterity > 14 && this->dexterity % 2 == 0) //Even number above 14
			this->dexMod = (this->dexterity - 14)/2;
		else if (this->dexterity > 14 && this->dexterity % 2 != 0) //Odd number above 14
			this->dexMod = (int)floor((this->dexterity - 14)/2);
		else if (this->dexterity < 10 && this->dexterity % 2 == 0) //Even number below 10
			this->dexMod = (10 - this->dexterity)/2;
		else if (this->dexterity < 10 && this->dexterity % 2 != 0) //Odd number below 10
			this->dexMod = (int)floor((10 - this->dexterity)/2);
	}
};