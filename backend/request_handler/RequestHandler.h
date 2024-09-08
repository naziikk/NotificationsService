#include <iostream>
#include "../../libraries/httplib.h"
#include <thread>
#include "../multithread_notification_scheduler/Time_scheduler.h"
#include "../../libraries/nlohmann/json.hpp"
#include <unordered_map>
#include <fstream>
#include <regex>


class RequestHandler {
public:
    Time_scheduler scheduler;

    void HttpPostToken(const httplib::Request& request, httplib::Response &res);

    void HttpNotificationDelete(const httplib::Request& request, httplib::Response &res);

    void HttpNotificationPutById(const httplib::Request& request, httplib::Response &res);

    void HttpNotificationPost(const httplib::Request& request, httplib::Response &res, int id);

    void HttpRegisterPost(const httplib::Request& request, httplib::Response &res);

    void HtttpNotificationsGet(const httplib::Request& request, httplib::Response &res);

    bool isValidEmail(const std::string& email);

    bool validateToken(const std::string& token);

    std::string generateAuthToken();
};

