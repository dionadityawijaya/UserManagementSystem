#include "auth.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <jwt-cpp/jwt.h>

std::string Auth::hashPassword(const std::string& password) {
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
bool Auth::verifyPassword(const std::string& hash, const std::string& password) {
    return hash == Auth::hashPassword(password);
}
std::string Auth::createToken(const User& user) {
    auto token = jwt::create()
    .set_issuer("auth0")
    .set_type("JWS")
    .set_payload_claim("username", jwt::claim(user.getUsername()))
    .sign(jwt::algorithm::hs256{"secret"});

    return token;
}
bool Auth::verifyToken(const std::string& token) {
    try {
        auto decoded = jwt::decode(token);
        auto verifier = jwt::verify()
                .allow_algorithm
                (jwt::algorithm::hs256
                {"secret"})
                .with_issuer("auth0");
        verifier.verify(decoded);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}