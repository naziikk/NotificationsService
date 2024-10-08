#ifndef NOTIFICATION_SERVICE_TIME_SCHEDULER_H
#define NOTIFICATION_SERVICE_TIME_SCHEDULER_H
#include "iostream"
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include "../email_sender/Email_sender.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include "/Users/nazarzakrevskij/CLionProjects/NotificationsService/postgres/PostgresProcessing.h"
class Time_scheduler {
public:
struct Notification {
    int id;
    std::string theme;
    std::string message;
    std::string email;
    std::chrono::system_clock::time_point sending_time;
    std::string token;
};
private:
std::deque<Notification> dq;
std::condition_variable cv;
std::mutex m;
public:
    void sendEmail(const Notification& notification);

    void workerThread();

    void scheduleNotification(int id, const std::string& email, const std::string& theme,
                              const std::string& message, const std::tm& time, const std::string& token, Database& db);

    bool updateNotificationDetails(int id, const std::string& email, const std::string& theme,
                                   const std::string& message, const std::tm& time, const std::string& token, Database& db);

    bool deleteNotification(int id, const std::string& token, Database& db);

    std::vector<Time_scheduler::Notification> getNotifications(std::string token, Database& db);
    Database* db;
    std::unordered_map<std::string, std::vector<Time_scheduler::Notification>> users;
};

#endif //NOTIFICATION_SERVICE_TIME_SCHEDULER_H

