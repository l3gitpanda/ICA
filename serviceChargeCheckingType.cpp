#include "serviceChargeCheckingType.h"
#include <iostream>

serviceChargeCheckingType::serviceChargeCheckingType(const std::string& name, int accountNumber, double balance)
    : bankAccountType(name, accountNumber, balance)
{
}

void serviceChargeCheckingType::withdraw(double amount)
{
    if (amount <= 0.0) return;

    if (amount + serviceFee_ <= balance_)
    {
        balance_ -= (amount + serviceFee_);
    }
}

void serviceChargeCheckingType::print() const
{
    std::cout << "[serviceChargeCheckingType]\n";
    bankAccountType::print();
    std::cout << "Service fee per withdraw: $" << serviceFee_ << "\n";
}
