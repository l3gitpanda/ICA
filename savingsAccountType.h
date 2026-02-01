#ifndef SAVINGS_ACCOUNT_TYPE_H
#define SAVINGS_ACCOUNT_TYPE_H

#include <string>
#include "bankAccountType.h"

class savingsAccountType : public bankAccountType
{
public:
    savingsAccountType(const std::string& name,
                       int accountNumber,
                       double accountBalance,
                       const std::string& userId);

    std::string getUserId() const;
    void print() const override;

private:
    std::string userId_;
};

#endif
