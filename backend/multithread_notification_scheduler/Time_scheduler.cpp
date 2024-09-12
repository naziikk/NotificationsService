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
                              notification.email, notification.theme, notification.message, false);
}
void Time_scheduler::workerThread() {
    while (true) {
        Notification notification;
        {
            std::unique_lock<std::mutex> lock(m);
            cv.wait(lock, [this] { return !dq.empty(); }); // ждем новое уведомлние

            while (true) {
                auto now = std::chrono::system_clock::now();
                auto next_send_time = dq.front().sending_time;
                if (now >= next_send_time) {
                    break;
                }
                // Ожидаем до наступления времени отправки следующего уведомления или появления нового уведомления
                cv.wait_until(lock, next_send_time, [this, next_send_time] {
                    auto now = std::chrono::system_clock::now();
                    return !dq.empty() && dq.front().sending_time <= now;
                });
            }
            notification = dq.front();
            dq.pop_front();
        }
        {
            std::lock_guard<std::mutex> lock(m);
            auto& notifications = users[notification.token];
            auto it = std::find_if(notifications.begin(), notifications.end(),
                                   [notification](const Notification& notif) {
                                       return notif.id == notification.id;
                                   });
            if (it != notifications.end()) {
                sendEmail(*it);
                notifications.erase(it);
                std::cout << "Notification with id: " << notification.id
                          << " and token: " << notification.token << " sent and deleted.\n";
            } else {
                std::cout << "Notification with id: " << notification.id
                          << " and token: " << notification.token << " has been deleted or not found.\n";
            }
        }
    }
}

static bool compare(Time_scheduler::Notification& f, Time_scheduler::Notification& s) {
    return f.sending_time < s.sending_time;
}

void Time_scheduler::scheduleNotification(int id, const std::string& email, const std::string& theme,
                                          const std::string& message, const std::tm& send_time_tm,
                                          const std::string& token) {
    auto send_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&send_time_tm)));
    Notification notification{id, theme, message, email, send_time, token};
    {
        std::lock_guard<std::mutex> lock(m);
        users[token].push_back(notification);
        dq.push_back(notification);
        std::sort(dq.begin(), dq.end(), compare);
    }
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
    std::lock_guard<std::mutex> lock(m);
    return users[token];
}

