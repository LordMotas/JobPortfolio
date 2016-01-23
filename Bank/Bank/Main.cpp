//This program demonstrates the usage of Polymorphism in C++ programming
//It simulates a Bank that manages 3 different types of accounts: Checking, Loan, and Savings
//Created by Tanner Olsen (10/31/2013) 
//Updated: (5/25/2014)

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Account.hpp"
#include "Savings.hpp"
#include "Checking.hpp"
#include "Loan.hpp"

using namespace std;

//Overloaded << operator
std::ostream& operator<<(std::ostream& out, Account* outAccount)
{
	if(outAccount->getTransaction() == true && outAccount->getAccountType() != "checking")
	{
		if(outAccount->getRejection() == true)
		{
			out << outAccount->getAccountName() << " (savings) : $" << outAccount->getTransactionValue() << " rejected (insufficient funds)" << endl;
			outAccount->setRejection(false);
		}
		out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << ") : $" << outAccount->getTransactionValue() << " applied to account" << endl;
		out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << ") : balance is $" << outAccount->getAccountBalance() << endl << endl;
		outAccount->setTransaction(false);
	}
	else
		if(outAccount->getTransaction() == true && outAccount->getAccountType() == "checking")
			{
				if(outAccount->getRejection() == true)
				{
					out << outAccount->getAccountName() << " (checking) : $" << outAccount->getTransactionValue() << " rejected (insufficient funds)" << endl;
					out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << ") : $" << outAccount->getPenalty() << " applied to account" << endl;
					outAccount->setRejection(false);
				}
				else
					out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << ") : $" << outAccount->getTransactionValue() << " applied to account" << endl;
				out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << ") : balance is $" <<  outAccount->getAccountBalance() << endl << endl;
				outAccount->setTransaction(false);
			}
		if(outAccount->getUpdate() == true)
		{
			out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << ") : $" << outAccount->getInterestGained() << " applied to account" << endl;
			out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << ") : balance is $" <<  outAccount->getAccountBalance() << endl << endl;
			outAccount->setUpdate(false);
		}
		else
			if(outAccount->getCounter() == 0)
			{
				out << "new account..." << endl;
				out << outAccount->getAccountName() << " (" << outAccount->getAccountType() << "): balance is $" << outAccount->getAccountBalance() << endl << endl;
				outAccount->addCounter();
			}
	return out;
} 

int main(void)
{
	char decide;
	int number;
	double balance, interestRate, feeRate, transaction;
	string name;
	Account* accounts[100];
	std::cout << std::setprecision(2) << std::fixed;
	ifstream transactionFile;
	transactionFile.open("Bank.txt");		//Opens the text file with all the information
	transactionFile >> decide;
	for(int i = 0; i < 100; i++)			//Simple loop for the whole program
	{
		if(transactionFile.eof() == true) //exits when the end of the file is reached
		{
			cin.get();			//Allows the system to pause so I can see the results to make sure they are accurate
			return 0;
		}
		switch(decide) //switches based on the first letter
		{
		case's':		//Savings account
			{
				transactionFile >> number >> name >> balance >> interestRate;
				accounts[i] = new Savings(number, name, balance, interestRate, "savings");
				cout << accounts[i];
				transactionFile >> decide;
				break;
			}
		case'c':		//Checking account
			{
				transactionFile >> number >> name >> balance >> feeRate;
				accounts[i] = new Checking(number, name, balance, feeRate, "checking");
				cout << accounts[i];
				transactionFile >> decide;
				break;
			}
		case'l':		//Loan account
			{
				transactionFile >> number >> name >> balance >> interestRate;
				accounts[i] = new Loan(number, name, balance, interestRate, "loan");
				cout << accounts[i];
				transactionFile >> decide;
				break;
			}
		case't':		//Transaction
			{
				cout << "transaction..." << endl;
				transactionFile >> number >> transaction;
				accounts[number]->makeTransaction(transaction);
				accounts[number]->setTransaction(true);
				cout << accounts[number];
				transactionFile >> decide;
				break;
			}
		case'u':		//Update
			{
				cout << "update..." << endl;
				transactionFile >> number;
				accounts[number]->updateAccount();
				accounts[number]->setUpdate(true);
				cout << accounts[number];
				transactionFile >> decide;
				break;
			}
		}
	}
	cin.get();
	return 0;
}