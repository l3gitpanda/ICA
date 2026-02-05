#ifndef ACCOUNTS_DATABASE_H
#define ACCOUNTS_DATABASE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

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

enum class LoginStatus
{
    kSuccess,
    kAccountNotFound,
    kIncorrectPassword
};

class AccountsDatabase
{
public:
    AccountsDatabase();

    AccountStatus addAccount(const std::string& email, const std::string& password);
    LoginStatus login(const std::string& email, const std::string& password) const;
    const AccountRecord* findByEmail(const std::string& email) const;

    static std::string statusMessage(AccountStatus status);
    static std::string statusMessage(LoginStatus status);

private:
    bool isValidEmail(const std::string& email) const;
    bool isStrongPassword(const std::string& password) const;
    std::string hashPassword(const std::string& password) const;
    int allocateUserId();

    int nextUserId_;
    std::unordered_map<std::string, AccountRecord> accountsByEmail_;
    std::unordered_set<int> assignedUserIds_;
};

#endif // ACCOUNTS_DATABASE_H
