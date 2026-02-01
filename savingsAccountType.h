#ifndef SAVINGS_ACCOUNT_TYPE_H
#define SAVINGS_ACCOUNT_TYPE_H

#include <string>
#include "bankAccountType.h"

class savingsAccountType : public bankAccountType
{
public:
    savingsAccountType(const std::string& name, int accountNumber, double accountBalance);
};

#endif
