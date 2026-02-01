#include <iostream>
#include "savingsAccountType.h"

savingsAccountType::savingsAccountType(const std::string& name,
                                       int accountNumber,
                                       double accountBalance,
                                       const std::string& userId)
    : bankAccountType(name, accountNumber, accountBalance),
      userId_(userId)
{
}

std::string savingsAccountType::getUserId() const
{
    return userId_;
}

void savingsAccountType::print() const
{
    std::cout << "[savingsAccountType]\n";
    bankAccountType::print();
    std::cout << "User ID: " << userId_ << "\n";
}
