#include "AuxiliaryFunctions.h"

bool AuxiliaryFunctions::isValidEmail(const std::string& email) {
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

bool AuxiliaryFunctions::validateToken(const std::string& token) {
    return scheduler.users.find(token) != scheduler.users.end();
}

std::string AuxiliaryFunctions::generateAuthToken() {
    std::string s = "1234567890abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string token;
    for (int i = 0; i < 16; i++) {
        token += s[rand() % s.length()];
    }
    return token;
}