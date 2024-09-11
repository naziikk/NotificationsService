#include "AuxiliaryFunctions.h"

bool AuxiliaryFunctions::isValidEmail(const std::string& email) {
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

bool AuxiliaryFunctions::validateToken(const std::string& token) {
    return scheduler.users.find(token) == scheduler.users.end();
}

std::string AuxiliaryFunctions::createJWT(const std::string& name, const std::string& last_name) {
    std::string path = "/Users/nazarzakrevskij/CLionProjects/NotificationsService/config.ini";
    std::string private_key = sender.getDataFromFile(path, "SECRET_KEY");
    std::string token = jwt::create()
        .set_subject(name + " " + last_name)
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{864000})
        .sign(jwt::algorithm::hs256{private_key});
    return token;
}