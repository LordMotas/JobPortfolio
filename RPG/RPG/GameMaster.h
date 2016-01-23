#pragma once

/*
The GM has a DiceBag that he/she uses to do just about everything, including create the Hero character. The
GM is responsible for keeping track of the Hero character. The GM is also the brains of the operation and will use an
instance of the ConsoleUI class to communicate with the user.
*/

class GameMaster {
private:
	Hero hero;
	DiceBag diceBag;
	ConsoleUI consolueUI;
public:
	void generate(char choice = 'H') {
		switch (choice) {
			case 'H':
				this->hero.dexterity = this->diceBag.getDice(3, 6);
				if (this->hero.dexterity >= 16) {
					auto previousDexterity = this->hero.dexterity;
					this->hero.dexterity += this->diceBag.getDice(1, 6);
					if (previousDexterity - this->hero.dexterity == 6) {
						this->hero.dexterity += this->diceBag.getDice(1, 6);
					}
				}
				this->hero.intelligence = this->diceBag.getDice(3, 6);
				if (this->hero.intelligence >= 16) {
					auto previousIntelligence = this->hero.intelligence;
					this->hero.intelligence += this->diceBag.getDice(1, 6);
					if (previousIntelligence - this->hero.intelligence == 6) {
						this->hero.intelligence += this->diceBag.getDice(1, 6);
					}
				}
				this->hero.strength = this->diceBag.getDice(3, 6);
				if (this->hero.strength >= 16) {
					auto previousStrength = this->hero.strength;
					this->hero.strength += this->diceBag.getDice(1, 6);
					if (previousStrength - this->hero.strength == 6) {
						this->hero.strength += this->diceBag.getDice(1, 6);
					}
				}
				this->hero.baseHealthPoints = this->hero.strength * 10;
				this->hero.currentHP = this->hero.baseHealthPoints;
				this->hero.baseMagicPoints = this->hero.intelligence * 5;
				this->hero.currentMP = this->hero.baseMagicPoints;

			break;
		}
		
	};
};