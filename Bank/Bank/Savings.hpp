//Derived Savings class

#ifndef SAVINGS_H_
#define SAVINGS_H_
#include "Account.hpp"


class Savings : public Account
{
public:
	Savings();
	Savings(int, string, double, double, string);
	void updateAccount();
	void makeTransaction(double);

private:
	double accountInterestRate;
};

#endif SAVINGS_H_