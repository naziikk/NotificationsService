#include "AuxiliaryFunctions.h"

bool AuxiliaryFunctions::isValidEmail(const std::string& email) {
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

std::string AuxiliaryFunctions::createJWT(const std::string& name, const std::string& last_name) {
    std::string path = "/Users/nazarzakrevskij/CLionProjects/NotificationsService/config.ini";
    std::string private_key = sender.getDataFromFile(path, "SECRET_KEY");
    std::string token = jwt::create().
            set_issuer("NotificationsService").
            set_subject(name + " " + last_name)
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{864000})
            .sign(jwt::algorithm::hs256{private_key});
    return token;
}

std::pair<std::string, std::string> AuxiliaryFunctions::extractNamefromJWT(const std::string &token) {
    try {
        std::string path = "/Users/nazarzakrevskij/CLionProjects/NotificationsService/config.ini";
        auto decoded = jwt::decode(token);
        std::string private_key = sender.getDataFromFile(path, "SECRET_KEY");

        auto verifier = jwt::verify().
                allow_algorithm(jwt::algorithm::hs256{private_key})
                .with_issuer("NotificationsService");
        verifier.verify(decoded);
        std::string subject = decoded.get_subject();
        int pos = subject.find(' ');
        if (pos == std::string::npos) {
            throw std::runtime_error("Invalid token format: subject does not contain a space separator");
        }
        std::string name = subject.substr(0, pos);
        std::string last_name = subject.substr(pos + 1);
        return {name, last_name};
    } catch (...) {
        std::cerr << "Failed to decode token: " << '\n';
        return {"", ""};
    }
}