#include "Time_scheduler.h"

void Time_scheduler::sendEmail(const Notification& notification) {
    std::cout << "Отправка email на " << notification.email
              << " с темой '" << notification.theme
              << "' и сообщением '" << notification.message << "'\n";
    Email_sender sender;
    std::string path = "/Users/nazarzakrevskij/CLionProjects/Notification-Service/config.ini";
    std::string email = sender.getDataFromFile(path, "USERNAME");
    std::string application_password = sender.getDataFromFile(path, "APP_PASSWORD");
    std::string from = sender.getDataFromFile(path, "USERNAME");
    sender.sendEmailYandexApi(email, application_password, from,
                              notification.email, notification.theme, notification.message);
}
void Time_scheduler::workerThread() {
    while (true){
        Notification notification;
        {
            std::unique_lock<std::mutex> lock(m);
            cv.wait(lock, [this] { return !dq.empty(); });
            notification = dq.front();
            dq.pop_front();
        }
        auto now = std::chrono::system_clock::now();
        if (now < notification.sending_time) {
            std::this_thread::sleep_until(notification.sending_time);
        }
        {
            std::lock_guard<std::mutex> lock(m);
            if (deleted.find(notification.id) == deleted.end()) {
                if (updated.find(notification.id) != updated.end()) {
                    notification = updated[notification.id];
                    updated.erase(notification.id);
                }
                sendEmail(notification);
                all.erase(notification.id);
            } else {
                std::cout << "notification with id: " + std::to_string(notification.id) + " has been deleted.\n";
                deleted.erase(notification.id);
            }
        }
    }
}

void Time_scheduler::scheduleNotification(int id, const std::string& email, const std::string& theme,
                                          const std::string& message, const std::tm& send_time_tm,
                                          const std::string user_id) {
    auto send_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&send_time_tm)));
    Notification notification{id, theme, message, email, send_time, user_id};
    {
        std::lock_guard<std::mutex> lock(m);
        dq.push_back(notification);
        all.insert(id);
    }
    cv.notify_one();
}

bool Time_scheduler::updateNotificationDetails(int id, const std::string& email, const std::string& theme,
                                               const std::string& message, const std::tm& send_time_tm,
                                               const std::string user_id) {
    std::lock_guard<std::mutex> lock(m);
    auto find = all.find(id);
    if (find != all.end()) {
        auto send_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&send_time_tm)));
        Notification notification{id, theme, message, email, send_time, user_id};
        updated[id] = notification;
        return true;
    }
    return false;
}

bool Time_scheduler::deleteNotification(int id, const std::string user_id) {
    std::lock_guard<std::mutex> lock(m);
    if (all.find(id) != all.end()) {
        all.erase(id);
        deleted.insert(id);
        return true;
    }
    return false;
}

