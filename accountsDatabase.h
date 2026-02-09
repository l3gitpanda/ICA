#ifndef ACCOUNTS_DATABASE_H
#define ACCOUNTS_DATABASE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "checkingAccountType.h"
#include "savingsAccountType.h"

struct AccountRecord
{
    std::string email;
    std::string passwordHash;
    int userId;
};

enum class AccountStatus
{
    kSuccess,
    kInvalidEmail,
    kWeakPassword,
    kDuplicateEmail,
    kDuplicateUserId
};

class AccountsDatabase
{
public:
    AccountsDatabase();

    AccountStatus addAccount(const std::string& email, const std::string& password);
    const AccountRecord* findByEmail(const std::string& email) const;

    int createUser(const std::string& email, const std::string& password);
    int authenticate(const std::string& email, const std::string& password) const;

    bool hasChecking(int userId) const;
    bool hasSavings(int userId) const;

    void createChecking(int userId);
    void createSavings(int userId);

    double getCheckingBalance(int userId) const;
    double getSavingsBalance(int userId) const;

    bool depositChecking(int userId, double amount);
    bool depositSavings(int userId, double amount);

    bool withdrawChecking(int userId, double amount);
    bool withdrawSavings(int userId, double amount);

    static std::string statusMessage(AccountStatus status);

private:
    bool isValidEmail(const std::string& email) const;
    bool isStrongPassword(const std::string& password) const;
    std::string hashPassword(const std::string& password) const;
    int allocateUserId();
    int allocateAccountNumber();

    int nextUserId_;
    int nextAccountNumber_;
    std::unordered_map<std::string, AccountRecord> accountsByEmail_;
    std::unordered_set<int> assignedUserIds_;
    std::unordered_map<int, std::unique_ptr<checkingAccountType>> checkingByUserId_;
    std::unordered_map<int, std::unique_ptr<savingsAccountType>> savingsByUserId_;
};

#endif // ACCOUNTS_DATABASE_H
