#include "bankAccountType.h"

#include <iostream>
#include <iomanip>

bankAccountType::bankAccountType()
    : name_{}, accountNumber_{0}, balance_{0.0}
{
}

bankAccountType::bankAccountType(const std::string& name, int accountNumber, double balance)
    : name_{name}, accountNumber_{accountNumber}, balance_{balance}
{
}

void bankAccountType::setName(const std::string& name)
{
    name_ = name;
}

std::string bankAccountType::getName() const
{
    return name_;
}

void bankAccountType::setAccountNumber(int accountNumber)
{
    accountNumber_ = accountNumber;
}

int bankAccountType::getAccountNumber() const
{
    return accountNumber_;
}

void bankAccountType::setBalance(double balance)
{
    balance_ = balance;
}

double bankAccountType::getBalance() const
{
    return balance_;
}

void bankAccountType::deposit(double amount)
{
    if (amount > 0.0)
        balance_ += amount;
}

// ====== Assigned stubs: withdraw & print ======

void bankAccountType::withdraw(double amount)
{
    // Sprint 0 behavior: keep it safe and non-crashing.
    // Later sprints can add overdraft rules, fees, etc.
    if (amount <= 0.0)
        return;

    if (amount <= balance_)
        balance_ -= amount;
    // else: ignore (no overdraft in stub)
}

void bankAccountType::print() const
{
    // Sprint 0 behavior: minimal readable output.
    std::cout << "Account Holder: " << name_ << '\n'
              << "Account Number: " << accountNumber_ << '\n'
              << "Balance: $" << std::fixed << std::setprecision(2) << balance_ << '\n';
}

void bankAccountType::createMonthlyStatement()
{
    // Stub: derived classes can override later
}
