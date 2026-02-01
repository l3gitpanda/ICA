

#include <iostream>
#include <iomanip>
#include <vector>
#include "accountsDatabase.h"
#include "savingsAccountInterface.h"
#include "bankAccountType.h"
#include "savingsAccountType.h"
#include "highInterestSavingsType.h"
#include "noServiceChargeCheckingType.h"
#include "serviceChargeCheckingType.h"
#include "highInterestCheckingType.h"
#include "certificateOfDepositType.h"
#include "checkingAccountType.h"

using namespace std;

int main()
{
	inMemoryAccountDatabase database;
	accountDatabaseBase* databaseBase = &database;

	string billUserId = databaseBase->createUser("bill@example.com", "BillPassword1");
	string susanUserId = databaseBase->createUser("susan@example.com", "SusanPassword2");

	savingsAccountInterface savingsInterface(*databaseBase);

	vector<bankAccountType *> accountsList;

	accountsList.push_back(new savingsAccountType(
        savingsInterface.openSavingsAccount(billUserId, "Bill", 10200, 2500)));
	accountsList.push_back(new savingsAccountType(
        savingsInterface.openSavingsAccount(susanUserId, "Susan", 10210, 2000)));
	accountsList.push_back(new highInterestSavingsType("Priya", 10220, 2200));
	accountsList.push_back(new noServiceChargeCheckingType("John", 20100, 3500));
	accountsList.push_back(new serviceChargeCheckingType("Ravi", 30100, 1800));
	accountsList.push_back(new highInterestCheckingType("Sheila", 20200, 6000));
	accountsList.push_back(new certificateOfDepositType("Hamid", 51001, 18000, 0.075, 18));

	cout << "January:\n-------------" << endl;
	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->createMonthlyStatement();
		accountsList[i]->print();
		cout << endl;
    }

	cout << "\nFebruary:\n-------------" << endl;
	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->createMonthlyStatement();
		accountsList[i]->print();
		cout << endl;
	}

	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->withdraw(500);
	}

	cout << "\nMarch:\n-------------" << endl;
	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->createMonthlyStatement();
		accountsList[i]->print();
		cout << endl;
	}

	return 0;
}
