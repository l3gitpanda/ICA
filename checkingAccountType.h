#ifndef CHECKING_ACCOUNT_TYPE_H
#define CHECKING_ACCOUNT_TYPE_H

#include "bankAccountType.h"
#include <string>
using namespace std;

class checkingAccountType
{
    string name_;
    int accountNumber_;
    float balance_ = 0;
    int foreignKey_;
    public:
        checkingAccountType(const std::string& name, int accountNumber, double accountBalance, int foreignKey);
};

#endif // CHECKING_ACCOUNT_TYPE_H  