#include "Account.hpp"
#include <iostream>

Account::Account()
{
	//empty
}

//Constructor
Account::Account(int number, string name, double balance, string type)
{
	accountNumber = number;
	accountName = name;
	accountBalance = balance;
	accountType = type;
	counter = 0;
	isTransaction = false;
	isUpdate = false;
	rejection = false;
}

//Polymorphic Functions
void Account::makeTransaction(double transaction)
{
	//empty
}

void Account::updateAccount()
{
	//empty
}

//Other functions
string Account::getAccountName()
{
	return accountName;
}

double Account::getAccountBalance()
{
	return accountBalance;
}

string Account::getAccountType()
{
	return accountType;
}

int Account::getCounter()
{
	return counter;
}

void Account::addCounter()
{
	counter++;
}

bool Account::getTransaction()
{
	return isTransaction;
}

void Account::setTransaction(bool TorF)
{
	isTransaction = TorF;
	isUpdate = false;
}

bool Account::getUpdate()
{
	return isUpdate;
}

void Account::setUpdate(bool TorF)
{
	isUpdate = TorF;
	isTransaction = false;
}

bool Account::getRejection()
{
	return rejection;
}

void Account::setRejection(bool TorF)
{
	rejection = TorF;
}

double Account::getTransactionValue()
{
	return transactionValue;
}

double Account::getInterestGained()
{
	return interestGained;
}

void Account::setInterestGained(double gained)
{
	interestGained = gained;
}

double Account::getPenalty()
{
	return penalty;
}