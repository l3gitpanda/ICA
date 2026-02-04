#ifndef SAVINGS_ACCOUNT_LIST_H
#define SAVINGS_ACCOUNT_LIST_H
#include <vector>
#include "savingsAccountType.h"
class savingsAccountList
{
public:
    savingsAccountList();
    ~savingsAccountList();

    void addAccount(savingsAccountType* account);
    void removeAccount(int accountNumber);
    savingsAccountType* getAccount(int accountNumber) const;
    void printAllAccounts() const;
private:
    std::vector<savingsAccountType*> accounts_;
};
#endif // savings_ACCOUNT_LIST_H