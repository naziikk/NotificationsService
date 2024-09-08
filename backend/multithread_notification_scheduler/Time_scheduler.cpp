#include "Time_scheduler.h"

void Time_scheduler::sendEmail(const Notification& notification) {
    std::cout << "Отправка email на " << notification.email
              << " с темой '" << notification.theme
              << "' и сообщением '" << notification.message << "'\n";
    Email_sender sender;
    std::string path = "/Users/nazarzakrevskij/CLionProjects/NotificationsService/config.ini";
    std::string email = sender.getDataFromFile(path, "USERNAME");
    std::string application_password = sender.getDataFromFile(path, "APP_PASSWORD");
    std::string from = sender.getDataFromFile(path, "USERNAME");
    sender.sendEmailYandexApi(email, application_password, from,
                              notification.email, notification.theme, notification.message);
}
void Time_scheduler::workerThread() {
    std::cout << "Worker thread started\n";
    while (true) {
        Notification notification;
        {
            std::unique_lock<std::mutex> lock(m);
            cv.wait(lock, [this] {
                std::cout << "Waiting... dq size: " << dq.size() << '\n';
                return !dq.empty();
            });
            notification = dq.front();
            dq.pop_front();
            std::cout << "Notification dequeued: " << notification.token << '\n';
        }

        auto now = std::chrono::system_clock::now();
        if (now < notification.sending_time) {
            std::cout << "Sleeping until: " << std::chrono::system_clock::to_time_t(notification.sending_time) << '\n';
            std::this_thread::sleep_until(notification.sending_time);
        }

        std::cout << "Processing notification: " << notification.token << '\n';
        {
            std::lock_guard<std::mutex> lock(m);
            auto it = std::find_if(users[notification.token].begin(), users[notification.token].end(),
                                   [notification](const Notification& notif) {
                                       return notif.id == notification.id;
                                   });
            if (it != users[notification.token].end()) {
                sendEmail(*it);
                users[notification.token].erase(it);
                std::cout << "Notification with id: " << notification.id
                          << " and token: " << notification.token << " sent and deleted.\n";
            } else {
                std::cout << "Notification with id: " << notification.id
                          << " and token: " << notification.token << " has been deleted.\n";
            }
        }
    }
}

void Time_scheduler::scheduleNotification(int id, const std::string& email, const std::string& theme,
                                          const std::string& message, const std::tm& send_time_tm,
                                          const std::string& token) {
    auto send_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&send_time_tm)));
    Notification notification{id, theme, message, email, send_time, token};
    {
        std::lock_guard<std::mutex> lock(m);
        dq.push_back(notification);
        users[token].push_back(notification);
        std::cout << token << '\n';
        std::cout << dq.size() << '\n';
    }
    std::cout << dq.size() << '\n';
    cv.notify_one();
}

// обновляем уведомление в случае нахождения в списке
bool Time_scheduler::updateNotificationDetails(int id, const std::string& email, const std::string& theme,
                                               const std::string& message, const std::tm& send_time_tm,
                                               const std::string& token) {
    std::lock_guard<std::mutex> lock(m);
    auto it = std::find_if(users[token].begin(), users[token].end(),
                           [id](const Notification& notif) { return notif.id == id; });
    if (it != users[token].end()) {
        auto send_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&send_time_tm)));
        Notification notification{id, theme, message, email, send_time, token};
        *it = notification;
        return true;
    }
    return false;
}

// удаляем уведомление в случае его нахождения в списке
bool Time_scheduler::deleteNotification(int id, const std::string& token) {
    std::lock_guard<std::mutex> lock(m);
    auto it = std::find_if(users[token].begin(), users[token].end(),
                           [id](const Notification& notif) { return notif.id == id; });
    if (it != users[token].end()) {
        users[token].erase(it);
        return true;
    }
    return false;
}

std::vector<Time_scheduler::Notification> Time_scheduler::getNotifications(std::string token) {
    return users[token];
}

