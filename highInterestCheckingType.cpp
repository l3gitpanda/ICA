#include "highInterestCheckingType.h"
#include <iostream>

highInterestCheckingType::highInterestCheckingType(const std::string& name,int accountNumber,double balance)
    : bankAccountType(name, accountNumber, balance)
{
}

void highInterestCheckingType::createMonthlyStatement()
{
    balance += balance * monthlyInterestRate;
}

void highInterestCheckingType::print() const
{
    std::cout << "[highInterestCheckingType]\n";
    bankAccountType::print();
    std::cout << "Monthly interest rate: " << (monthlyInterestRate * 100) << "%\n";
}
