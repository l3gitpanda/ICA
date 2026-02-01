#include <iostream>
#include "savingsAccountType.h"

savingsAccountType::savingsAccountType(const std::string& name, int accountNumber, double accountBalance)
    : bankAccountType(name, accountNumber, accountBalance)
{
    std::cout << "savingsAccountType constructor" << std::endl;
}