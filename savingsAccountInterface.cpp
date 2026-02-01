#include "savingsAccountInterface.h"

#include <stdexcept>

savingsAccountInterface::savingsAccountInterface(accountDatabaseBase& database)
    : database_(database)
{
}

savingsAccountType savingsAccountInterface::openSavingsAccount(const std::string& userId,
                                                               const std::string& name,
                                                               int accountNumber,
                                                               double balance) const
{
    if (!database_.hasUserId(userId))
        throw std::runtime_error("Savings account requires a valid user id.");

    return savingsAccountType(name, accountNumber, balance, userId);
}
