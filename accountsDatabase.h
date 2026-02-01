#ifndef ACCOUNTS_DATABASE_H
#define ACCOUNTS_DATABASE_H

#include <string>
#include <unordered_map>

struct userAccountRecord
{
    std::string userId;
    std::string email;
    std::string password;
};

class accountDatabaseBase
{
public:
    virtual ~accountDatabaseBase() = default;

    virtual std::string createUser(const std::string& email, const std::string& password) = 0;
    virtual bool authenticate(const std::string& email, const std::string& password) const = 0;
    virtual bool hasUserId(const std::string& userId) const = 0;
    virtual std::string getUserIdForEmail(const std::string& email) const = 0;
};

class inMemoryAccountDatabase final : public accountDatabaseBase
{
public:
    std::string createUser(const std::string& email, const std::string& password) override;
    bool authenticate(const std::string& email, const std::string& password) const override;
    bool hasUserId(const std::string& userId) const override;
    std::string getUserIdForEmail(const std::string& email) const override;

private:
    std::string generateUserId();

    std::unordered_map<std::string, userAccountRecord> usersById_;
    std::unordered_map<std::string, std::string> idByEmail_;
    int nextId_ = 1000;
};

#endif
