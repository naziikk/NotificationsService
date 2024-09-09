#ifndef NOTIFICATIONSSERVICE_AUXILIARYFUNCTIONS_H
#define NOTIFICATIONSSERVICE_AUXILIARYFUNCTIONS_H
#include "iostream"
#include <regex>
#include "../multithread_notification_scheduler/Time_scheduler.h"

class AuxiliaryFunctions {
public:
    Time_scheduler scheduler;

    bool validateToken(const std::string& token);

    bool isValidEmail(const std::string& email);

    std::string generateAuthToken();
};


#endif //NOTIFICATIONSSERVICE_AUXILIARYFUNCTIONS_H
