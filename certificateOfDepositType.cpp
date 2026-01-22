#include "certificateOfDepositType.h"
#include <iostream>

certificateOfDepositType::certificateOfDepositType(const std::string& name,int accountNumber,double balance,double interestRate,int maturityMonths)
    : bankAccountType(name, accountNumber, balance),
      interestRate_(interestRate),
      monthsLeft_(maturityMonths)
{
}

void certificateOfDepositType::createMonthlyStatement()
{
    balance += balance * interestRate;
    if (monthsLeft > 0) monthsLeft--;
}

void certificateOfDepositType::withdraw(double amount)
{
    if (amount <= 0.0) return;

    if (monthsLeft == 0)
    {
        bankAccountType::withdraw(amount);
    }
}

void certificateOfDepositType::print() const
{
    std::cout << "[certificateOfDepositType]\n";
    bankAccountType::print();
    std::cout << "Interest rate: " << (interestRate * 100) << "%\n";
    std::cout << "Months left: " << monthsLeft << "\n";
}
