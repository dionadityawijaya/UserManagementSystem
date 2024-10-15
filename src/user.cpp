#include "user.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>


std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_192_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0');
    }
    return ss.str();

}

User::User(const std::string& username, const std::string& password) : username(username) {
    passwordHash = hashPassword(password);
}
std::string User::getUsername() const {
    return username;
}
std::string User::getPasswordHash() const {
    return passwordHash;
}
