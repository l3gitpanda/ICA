

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

using namespace std;

int main()
{
    AccountsDatabase accountsDatabase;

    const std::string email = "bill@example.com";
    const std::string password = "Secur3!Pass";
    const AccountStatus status = accountsDatabase.addAccount(email, password);
    std::cout << "Account setup: " << AccountsDatabase::statusMessage(status) << '\n';

    const AccountRecord* record = accountsDatabase.findByEmail(email);
    if (record != nullptr)
    {
        std::cout << "Stored account: " << record->email
                  << " (user ID " << record->userId << ")\n";
    }

    // Login with correct password (plain text — hashed internally for comparison)
    LoginStatus loginResult = accountsDatabase.login(email, password);
    std::cout << "Login attempt: " << AccountsDatabase::statusMessage(loginResult) << '\n';

    // Login with wrong password
    loginResult = accountsDatabase.login(email, "WrongPass1!");
    std::cout << "Bad password:  " << AccountsDatabase::statusMessage(loginResult) << '\n';

    // Login with unknown email
    loginResult = accountsDatabase.login("nobody@example.com", password);
    std::cout << "Bad email:     " << AccountsDatabase::statusMessage(loginResult) << "\n\n";

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

	return 0;
}
