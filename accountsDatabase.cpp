#include "accountsDatabase.h"

#include <cctype>
#include <functional>
#include <sstream>

AccountsDatabase::AccountsDatabase()
    : nextUserId_{100000}, nextAccountNumber_{200000}
{
    const std::string testEmail = "test@account.com";
    const std::string testPassword = "password";

    const int userId = allocateUserId();
    if (userId > 0)
    {
        AccountRecord record;
        record.email = testEmail;
        record.passwordHash = hashPassword(testPassword);
        record.userId = userId;

        accountsByEmail_.emplace(testEmail, record);
        assignedUserIds_.insert(userId);
    }
}

AccountStatus AccountsDatabase::addAccount(const std::string& email, const std::string& password)
{
    if (!isValidEmail(email))
        return AccountStatus::kInvalidEmail;

    if (!isStrongPassword(password))
        return AccountStatus::kWeakPassword;

    if (accountsByEmail_.find(email) != accountsByEmail_.end())
        return AccountStatus::kDuplicateEmail;

    const int userId = allocateUserId();
    if (userId <= 0)
        return AccountStatus::kDuplicateUserId;

    AccountRecord record;
    record.email = email;
    record.passwordHash = hashPassword(password);
    record.userId = userId;

    accountsByEmail_.emplace(email, record);
    assignedUserIds_.insert(userId);
    return AccountStatus::kSuccess;
}

const AccountRecord* AccountsDatabase::findByEmail(const std::string& email) const
{
    const auto it = accountsByEmail_.find(email);
    if (it == accountsByEmail_.end())
        return nullptr;
    return &it->second;
}

int AccountsDatabase::createUser(const std::string& email, const std::string& password)
{
    const AccountStatus status = addAccount(email, password);
    if (status != AccountStatus::kSuccess)
        return -1;

    const AccountRecord* record = findByEmail(email);
    return record ? record->userId : -1;
}

int AccountsDatabase::authenticate(const std::string& email, const std::string& password) const
{
    const AccountRecord* record = findByEmail(email);
    if (record == nullptr)
        return -1;

    const std::string hashedPassword = hashPassword(password);
    if (hashedPassword != record->passwordHash)
        return -1;

    return record->userId;
}

bool AccountsDatabase::hasChecking(int userId) const
{
    return checkingByUserId_.find(userId) != checkingByUserId_.end();
}

bool AccountsDatabase::hasSavings(int userId) const
{
    return savingsByUserId_.find(userId) != savingsByUserId_.end();
}

void AccountsDatabase::createChecking(int userId)
{
    if (assignedUserIds_.find(userId) == assignedUserIds_.end())
        return;
    if (hasChecking(userId))
        return;

    const int accountNumber = allocateAccountNumber();
    checkingByUserId_[userId] = std::make_unique<checkingAccountType>(
        "User " + std::to_string(userId), accountNumber, 0.0, userId);
}

void AccountsDatabase::createSavings(int userId)
{
    if (assignedUserIds_.find(userId) == assignedUserIds_.end())
        return;
    if (hasSavings(userId))
        return;

    const int accountNumber = allocateAccountNumber();
    savingsByUserId_[userId] = std::make_unique<savingsAccountType>(
        "User " + std::to_string(userId), accountNumber, 0.0, userId);
}

double AccountsDatabase::getCheckingBalance(int userId) const
{
    const auto it = checkingByUserId_.find(userId);
    if (it == checkingByUserId_.end())
        return 0.0;
    return it->second->getBalance();
}

double AccountsDatabase::getSavingsBalance(int userId) const
{
    const auto it = savingsByUserId_.find(userId);
    if (it == savingsByUserId_.end())
        return 0.0;
    return it->second->getBalance();
}

bool AccountsDatabase::depositChecking(int userId, double amount)
{
    if (amount <= 0.0)
        return false;
    const auto it = checkingByUserId_.find(userId);
    if (it == checkingByUserId_.end())
        return false;
    it->second->deposit(amount);
    return true;
}

bool AccountsDatabase::depositSavings(int userId, double amount)
{
    if (amount <= 0.0)
        return false;
    const auto it = savingsByUserId_.find(userId);
    if (it == savingsByUserId_.end())
        return false;
    it->second->deposit(amount);
    return true;
}

bool AccountsDatabase::withdrawChecking(int userId, double amount)
{
    if (amount <= 0.0)
        return false;
    const auto it = checkingByUserId_.find(userId);
    if (it == checkingByUserId_.end())
        return false;
    const bool success = it->second->withdraw(amount);
    return success;
}

bool AccountsDatabase::withdrawSavings(int userId, double amount)
{
    if (amount <= 0.0)
        return false;
    const auto it = savingsByUserId_.find(userId);
    if (it == savingsByUserId_.end())
        return false;
    const bool success = it->second->withdraw(amount);
    return success;
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

// Need to replace hashing algo to a better one with salting in future
std::string AccountsDatabase::hashPassword(const std::string& password) const
{
    const std::size_t hashed = std::hash<std::string>{}(password);
    std::ostringstream out;
    out << std::hex << hashed;
    return out.str();
}

int AccountsDatabase::allocateUserId()
{
    int candidate = nextUserId_;
    while (candidate > 0 && assignedUserIds_.find(candidate) != assignedUserIds_.end())
    {
        ++candidate;
    }

    if (candidate <= 0)
        return -1;

    nextUserId_ = candidate + 1;
    return candidate;
}

int AccountsDatabase::allocateAccountNumber()
{
    if (nextAccountNumber_ <= 0)
        return -1;
    return nextAccountNumber_++;
}
