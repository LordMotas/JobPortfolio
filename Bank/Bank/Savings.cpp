#include "Savings.hpp"
#include <iostream>

Savings::Savings()
{
	//empty
}

//Constructor
Savings::Savings(int number, string name, double balance, double interestRate, string type)
{
	accountNumber = number;
	accountName = name;
	accountBalance = balance;
	accountInterestRate = interestRate;
	accountType = type;
	counter = 0;
	isTransaction = false;
	isUpdate = false;
	rejection = false;
}

void Savings::updateAccount()
{
	interestGained = accountBalance*accountInterestRate;
	accountBalance += interestGained;
}

void Savings::makeTransaction(double transaction)
{
	transactionValue = transaction;
	if(-1*(transaction) > accountBalance)
	{
		rejection = true;		//Rejects the transaction if it exceeds the balance
	}
	else
	{
		accountBalance += transaction;
	}
}