#include "accountsDatabase.h"

std::string inMemoryAccountDatabase::createUser(const std::string& email, const std::string& password)
{
    if (email.empty() || password.empty())
        return "";

    if (idByEmail_.find(email) != idByEmail_.end())
        return "";

    std::string userId = generateUserId();
    if (userId.empty())
        return "";

    userAccountRecord record{userId, email, password};
    usersById_.emplace(userId, record);
    idByEmail_.emplace(email, userId);
    return userId;
}

bool inMemoryAccountDatabase::authenticate(const std::string& email, const std::string& password) const
{
    auto idIter = idByEmail_.find(email);
    if (idIter == idByEmail_.end())
        return false;

    auto userIter = usersById_.find(idIter->second);
    if (userIter == usersById_.end())
        return false;

    return userIter->second.password == password;
}

bool inMemoryAccountDatabase::hasUserId(const std::string& userId) const
{
    return usersById_.find(userId) != usersById_.end();
}

std::string inMemoryAccountDatabase::getUserIdForEmail(const std::string& email) const
{
    auto iter = idByEmail_.find(email);
    if (iter == idByEmail_.end())
        return "";

    return iter->second;
}

std::string inMemoryAccountDatabase::generateUserId()
{
    while (true)
    {
        std::string candidate = "U" + std::to_string(nextId_++);
        if (usersById_.find(candidate) == usersById_.end())
            return candidate;
    }
}
