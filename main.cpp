

#include <iostream>
#include <iomanip>
#include <vector>
#include "bankAccountType.h"
#include "savingsAccountType.h"
#include "highInterestSavingsType.h"
#include "noServiceChargeCheckingType.h"
#include "serviceChargeCheckingType.h"
#include "highInterestCheckingType.h"
#include "certificateOfDepositType.h"
#include "checkingAccountType.h"
#include "accountsDatabase.h"
#include "functionalUI.h"

using namespace std;

void runSampleTests()
{

	vector<bankAccountType *> accountsList;

	accountsList.push_back(new savingsAccountType("Bill", 10200, 2500));
	accountsList.push_back(new highInterestSavingsType("Susan", 10210, 2000));
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

	return;
}

int main()
{
    cout << "1) Run Functional UI" << endl;
    cout << "2) Run Sample Account Tests" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        AccountsDatabase db;
        FunctionalUI ui(db);
        ui.run();
    }
    else if (choice == 2)
    {
        runSampleTests();
    }

    return 0;
}
