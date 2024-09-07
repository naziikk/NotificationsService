#ifndef NOTIFICATION_SERVICE_EMAIL_SENDER_H
#define NOTIFICATION_SERVICE_EMAIL_SENDER_H
#include <iostream>
#include <curl/curl.h>
#include <fstream>

class Email_sender {
public:
    Email_sender() {};

    ~Email_sender() {};

    bool sendEmailYandexApi(const std::string& email, const std::string& application_password,
                            const std::string& from, const std::string& to,
                            const std::string& theme, const std::string& message);

    std::string getDataFromFile(const std::string& filename, const std::string& target);

};

#endif //NOTIFICATION_SERVICE_EMAIL_SENDER_H
