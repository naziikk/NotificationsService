#ifndef NOTIFICATIONSSERVICE_AUXILIARYFUNCTIONS_H
#define NOTIFICATIONSSERVICE_AUXILIARYFUNCTIONS_H
#include "iostream"
#include <regex>
#include "../multithread_notification_scheduler/Time_scheduler.h"
#include "../email_sender/Email_sender.h"
#include <jwt-cpp/jwt.h>
#include <chrono>

class AuxiliaryFunctions {
public:
    Time_scheduler scheduler;
    Email_sender sender;

    bool validateToken(const std::string& token);

    bool isValidEmail(const std::string& email);

    std::string createJWT(const std::string& name, const std::string& last_name);
};


#endif //NOTIFICATIONSSERVICE_AUXILIARYFUNCTIONS_H
