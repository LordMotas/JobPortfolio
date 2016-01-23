//Derived Checking class

#ifndef CHECKING_H_
#define CHECKING_H_
#include "Account.hpp"


class Checking : public Account
{
public:
	Checking();
	Checking(int, string, double, double, string);
	void updateAccount();
	void makeTransaction(double);

private:
	double accountFeeRate;
	int numberOfChecks;
};

#endif CHECKING_H_