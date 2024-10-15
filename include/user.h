#pragma once
#include <string>

class User {
    public:
        User(const std::string& username, const std::string& password);

        std::string getUsername() const;
        std::string getPasswordHash() const;

    private:
        std::string username;
        std::string passwordHash;
};