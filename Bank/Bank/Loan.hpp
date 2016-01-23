//Derived Loan class

#ifndef LOAN_H_
#define LOAN_H_
#include "Account.hpp"


class Loan : public Account
{
public:
	Loan();
	Loan(int, string, double, double, string);
	void updateAccount();
	void makeTransaction(double);

private:
	double accountInterestRate;

};

#endif LOAN_H_