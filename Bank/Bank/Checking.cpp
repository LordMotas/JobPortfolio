#include "Checking.hpp"
#include <iostream>

Checking::Checking()
{
	//empty
}

//Constructor
Checking::Checking(int number, string name, double balance, double feeRate, string type)
{
	numberOfChecks = 0;
	accountNumber = number;
	accountName = name;
	accountBalance = balance;
	accountFeeRate = feeRate;
	accountType = type;
	counter = 0;
	isTransaction = false;
	isUpdate = false;
}

void Checking::updateAccount()
{
	interestGained = (numberOfChecks*accountFeeRate)*-1;
	accountBalance += interestGained;
}

void Checking::makeTransaction(double transaction)
{
	transactionValue = transaction;
	if(-1*(transaction) > accountBalance)
	{
		rejection = true;		//Rejects if transaction exceeds the balance
		transaction = -25;		//Adds a penalty if the transaction is rejected
		penalty = -25;
	}
	accountBalance += transaction;
	if(transaction < 0 && transaction != -25)
	{
		numberOfChecks++;
	}
}