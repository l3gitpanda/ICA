#ifndef BANK_ACCOUNT_TYPE_H
#define BANK_ACCOUNT_TYPE_H

#include <string>

// Baseline stub: enough to build/run with the provided main.cpp.
// Extend/replace these implementations in later sprints.
class bankAccountType
{
public:
    bankAccountType();
    bankAccountType(const std::string& name, int accountNumber, double balance);
    virtual ~bankAccountType() = default;

    // Accessors / mutators
    void setName(const std::string& name);
    std::string getName() const;

    void setAccountNumber(int accountNumber);
    int getAccountNumber() const;

    void setBalance(double balance);
    double getBalance() const;

    // Core banking operations
    virtual void deposit(double amount);
    virtual void withdraw(double amount);  // stub OK for Sprint 0
    virtual void print() const;            // stub OK for Sprint 0
    virtual void createMonthlyStatement(); // stub OK for Sprint 0

protected:
    std::string name_;
    int accountNumber_;
    double balance_;
};

#endif // BANK_ACCOUNT_TYPE_H
