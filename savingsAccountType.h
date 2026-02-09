#ifndef SAVINGS_ACCOUNT_TYPE_H
#define SAVINGS_ACCOUNT_TYPE_H

#include <string>
#include "bankAccountType.h"

using namespace std;

class savingsAccountType
{
public:
    savingsAccountType(const std::string& name, int accountNumber, double accountBalance, int foreignKey);
private:
    int foreignKey_;
    double balance_;
    int accountNumber_;
    string name_;
};

#endif
