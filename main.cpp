#include "crow.h"
#include "auth.h"
#include <nlohmann/json.hpp>
#include "user.h"
#include <vector>

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<User> users;

int main(int argc, char const *argv[])
{
    crow::SimpleApp app;

   CROW_ROUTE(app, "/register").methods(crow::HTTPMethod::GET)([]() {
        std::string content = readFile("templates/register.html");
        return crow::response(content);
    });

    CROW_ROUTE(app, "/register").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = nlohmann::json::parse(req.body);
        std::string username = body["username"];
        std::string password = body["password"];

        std::string hashedPassword = Auth::hashPassword(password);
        std::cout << "Register - Password: " << password << ", Hashed: " << hashedPassword << std::endl;

        User newUser(username, hashedPassword);
        users.push_back(newUser);

        crow::json::wvalue response;
        response["success"] = true;
        response["message"] = "User registrered successfully";
        return crow::response(200, response);
    });

    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::GET)([]() {
        std::string content = readFile("templates/login.html");
        return crow::response(content);
    });

    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = nlohmann::json::parse(req.body);
        std::string username = body["username"];
        std::string password = body["password"];

        for (const auto& user : users) {
            if (user.getUsername() == username) {
                std::string hashedInputPassword = Auth::hashPassword(password);
         std::cout << "Login - Password: " << password << ", Hashed: " << hashedInputPassword << std::endl;

                if (user.getPasswordHash() == hashedInputPassword) {
                    std::string token = Auth::createToken(user);
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["token"] = token;
                    return crow::response(200, response);
                } else {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["message"] = "Invalid password";
                    return crow::response(400, response);
                }
            }
        }

        crow::json::wvalue response;
        response["success"] = false;
        response["message"] = "User not found";
        return crow::response(404, response);
    });

    app.port(18080).multithreaded().run();
}
        