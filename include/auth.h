#pragma once
#include "user.h"
#include <jwt-cpp/jwt.h>

class Auth {
    public:
        static std::string hashPassword(const std::string& password);
        static bool verifyPassword(const std::string& hash, const std::string& password);
        static std::string createToken(const User& user);
        static bool verifyToken(const std::string& token);
};