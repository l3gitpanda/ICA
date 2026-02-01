#include "accountsDatabase.h"

#include <cctype>
#include <functional>
#include <limits>
#include <sstream>

AccountsDatabase::AccountsDatabase()
    : nextUserId_{100000}
{
}

AccountStatus AccountsDatabase::addAccount(const std::string& email, const std::string& password)
{
    if (!isValidEmail(email))
        return AccountStatus::kInvalidEmail;

    if (!isStrongPassword(password))
        return AccountStatus::kWeakPassword;

    if (accountsByEmail_.find(email) != accountsByEmail_.end())
        return AccountStatus::kDuplicateEmail;

    int userId = 0;
    if (!generateUniqueUserId(userId))
        return AccountStatus::kDuplicateUserId;

    AccountRecord record;
    record.email = email;
    record.passwordHash = hashPassword(password);
    record.userId = userId;

    accountsByEmail_.emplace(email, record);
    userIds_.insert(userId);
    return AccountStatus::kSuccess;
}

const AccountRecord* AccountsDatabase::findByEmail(const std::string& email) const
{
    const auto it = accountsByEmail_.find(email);
    if (it == accountsByEmail_.end())
        return nullptr;
    return &it->second;
}

std::string AccountsDatabase::statusMessage(AccountStatus status)
{
    switch (status)
    {
    case AccountStatus::kSuccess:
        return "Account created.";
    case AccountStatus::kInvalidEmail:
        return "Invalid email format.";
    case AccountStatus::kWeakPassword:
        return "Password does not meet complexity requirements.";
    case AccountStatus::kDuplicateEmail:
        return "Email already exists.";
    case AccountStatus::kDuplicateUserId:
        return "User ID conflict.";
    default:
        return "Unknown status.";
    }
}

bool AccountsDatabase::generateUniqueUserId(int& userId)
{
    const int maxId = std::numeric_limits<int>::max();
    if (userIds_.size() >= static_cast<std::size_t>(maxId - 1))
        return false;

    if (nextUserId_ <= 0 || nextUserId_ == maxId)
        nextUserId_ = 1;

    const int startId = nextUserId_;

    while (true)
    {
        const int candidate = nextUserId_;

        if (nextUserId_ == maxId)
            nextUserId_ = 1;
        else
            ++nextUserId_;

        if (userIds_.find(candidate) == userIds_.end())
        {
            userId = candidate;
            return true;
        }

        if (nextUserId_ == startId)
            return false;
    }
}

bool AccountsDatabase::isValidEmail(const std::string& email) const
{
    const auto atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0)
        return false;

    const auto dotPos = email.find('.', atPos + 1);
    if (dotPos == std::string::npos || dotPos == atPos + 1)
        return false;

    return dotPos < email.size() - 1;
}

bool AccountsDatabase::isStrongPassword(const std::string& password) const
{
    if (password.size() < 8)
        return false;

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSymbol = false;

    for (char ch : password)
    {
        if (std::isupper(static_cast<unsigned char>(ch)))
            hasUpper = true;
        else if (std::islower(static_cast<unsigned char>(ch)))
            hasLower = true;
        else if (std::isdigit(static_cast<unsigned char>(ch)))
            hasDigit = true;
        else
            hasSymbol = true;
    }

    return hasUpper && hasLower && hasDigit && hasSymbol;
}

std::string AccountsDatabase::hashPassword(const std::string& password) const
{
    const std::size_t hashed = std::hash<std::string>{}(password);
    std::ostringstream out;
    out << std::hex << hashed;
    return out.str();
}
