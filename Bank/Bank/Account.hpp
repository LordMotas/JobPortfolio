//The base Account class

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
using namespace std;

class Account
{
public:
	Account();
	Account(int, string, double, string);
	virtual void makeTransaction(double);
	virtual void updateAccount();

	string getAccountName();
	double getAccountBalance();
	string getAccountType();
	int getCounter();
	void addCounter();
	bool getTransaction();
	void setTransaction(bool);
	bool getUpdate();
	void setUpdate(bool);
	void setRejection(bool);
	bool getRejection();
	double getTransactionValue();
	void setInterestGained(double);
	double getInterestGained();
	double getPenalty();

protected:
	string accountName;
	int accountNumber;
	double accountBalance;
	string accountType;
	int counter;
	bool isTransaction;
	bool isUpdate;
	double transactionValue;
	bool rejection;
	double interestGained;
	double penalty;
};
#endif