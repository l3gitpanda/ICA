#ifndef SAVINGS_ACCOUNT_INTERFACE_H
#define SAVINGS_ACCOUNT_INTERFACE_H

#include <string>
#include "accountsDatabase.h"
#include "savingsAccountType.h"

class savingsAccountInterface
{
public:
    explicit savingsAccountInterface(accountDatabaseBase& database);

    savingsAccountType openSavingsAccount(const std::string& userId,
                                          const std::string& name,
                                          int accountNumber,
                                          double balance) const;

private:
    accountDatabaseBase& database_;
};

#endif
