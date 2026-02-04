#include "savingsAccountList.h"
savingsAccountList::savingsAccountList()
{
}
savingsAccountList::~savingsAccountList()
{
    for (auto account : accounts_)
    {
        delete account;
    }
}
void savingsAccountList::addAccount(savingsAccountType* account)
{
    accounts_.push_back(account);
}
void savingsAccountList::removeAccount(int accountNumber)
{
    for (auto it = accounts_.begin(); it != accounts_.end(); ++it)
    {
        if ((*it)->getAccountNumber() == accountNumber)
        {
            delete *it;
            accounts_.erase(it);
            return;
        }
    }
}
savingsAccountType* savingsAccountList::getAccount(int accountNumber) const
{
    for (auto account : accounts_)
    {
        if (account->getAccountNumber() == accountNumber)
        {
            return account;
        }
    }
    return nullptr;
}
void savingsAccountList::printAllAccounts() const
{
    for (const auto& account : accounts_)
    {
        account->print();
        std::cout << "-----------------------\n";
    }
}
