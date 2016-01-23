#include "Loan.hpp"
#include <iostream>

Loan::Loan()
{
	//empty
}

//Constructor
Loan::Loan(int number, string name, double balance, double interestRate, string type)
{
	accountNumber = number;
	accountName = name;
	accountBalance = balance*-1;
	accountInterestRate = interestRate;
	accountType = type;
	counter = 0;
	isTransaction = false;
	isUpdate = false;
}

void Loan::updateAccount()
{
	interestGained = accountBalance*accountInterestRate;
	accountBalance += interestGained;
}

void Loan::makeTransaction(double transaction)
{
	transactionValue = transaction;
	accountBalance += transaction;
}