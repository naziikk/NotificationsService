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
            cv.wait(lock, [this] { return !dq.empty(); }); // ждем новое уведомление

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
            std::string jwt = notification.token;
            std::cout << jwt << ' ' << notification.id << '\n';
            std::string req = "SELECT id, theme, message, email, sending_time, jwt FROM notifications.users_notifications "
                              "WHERE id = " + std::to_string(notification.id) +
                              " AND jwt = '" + jwt + "';";

            pqxx::result res = db->executeQuery(req);

            if (res.empty()) {
                std::cout << "Notification with id: " << notification.id
                          << " and token: " << notification.token << " has been deleted or not found.\n";
                continue;
            } else {
                int notification_id = res[0][0].as<int>();
                std::string theme = res[0][1].as<std::string>();
                std::string message = res[0][2].as<std::string>();
                std::string email = res[0][3].as<std::string>();
                std::string sending_time_str = res[0][4].as<std::string>();
                std::tm sending_time_tm = {};
                std::istringstream ss(sending_time_str);
                ss >> std::get_time(&sending_time_tm, "%Y-%m-%d %H:%M:%S"); // Парсинг строки времени
                auto sending_time = std::chrono::system_clock::from_time_t(std::mktime(&sending_time_tm));
                std::string jwt_in_db = res[0][5].as<std::string>();
                auto now = std::chrono::system_clock::now();
                if (sending_time > now) {
                    {
                        std::lock_guard<std::mutex> lock(m);
                        // scheduleNotification(notification_id, theme, message, email, sending_time, jwt_in_db, db)
                    }
                    continue;
                }
                Notification notification1{notification_id, theme, message, email, sending_time, jwt_in_db};
                sendEmail(notification1);
                std::string req1 = "DELETE FROM notifications.users_notifications "
                                   "WHERE id = " + std::to_string(notification.id) +
                                   " AND jwt = '" + jwt + "';";
                db->executeQuery(req1);

                std::cout << "Notification with id: " << notification.id
                          << " and token: " << notification.token << " sent and deleted.\n";
            }
        }
    }
}

static bool compare(Time_scheduler::Notification& f, Time_scheduler::Notification& s) {
    return f.sending_time < s.sending_time;
}

void Time_scheduler::scheduleNotification(int id, const std::string& email, const std::string& theme,
                                          const std::string& message, const std::tm& send_time_tm,
                                          const std::string& token, Database& db) {
    auto send_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&send_time_tm)));
    Notification notification{id, theme, message, email, send_time, token};
    {
        std::lock_guard<std::mutex> lock(m);
        std::ostringstream oss;
        oss << "INSERT INTO notifications.users_notifications (id, theme, message, email, sending_time, jwt) "
            << "VALUES (" << id << ", '" << theme << "', '" << message << "', '" << email << "', '"
            << std::put_time(&send_time_tm, "%Y-%m-%d %H:%M:%S") << "', '" << token << "');";

        std::string req = oss.str();
        db.executeQuery(req);
        dq.push_back(notification);
        std::sort(dq.begin(), dq.end(), compare);
    }
    cv.notify_one();
}

// обновляем уведомление в случае нахождения в списке
bool Time_scheduler::updateNotificationDetails(int id, const std::string& email, const std::string& theme,
                                               const std::string& message, const std::tm& send_time_tm,
                                               const std::string& token, Database& db) {
    std::lock_guard<std::mutex> lock(m);
    std::string req = "SELECT id, theme, message, email, sending_time, jwt FROM notifications.users_notifications "
                      "WHERE id = " + std::to_string(id) +
                      " AND jwt = '" + token + "';";
    pqxx::result res = db.executeQuery(req);
    if (!res.empty()) {
        std::string req2 = "DELETE FROM notifications.users_notifications "
                           "WHERE id = " + std::to_string(id) +
                           " AND jwt = '" + token + "';";
        db.executeQuery(req2);

        std::ostringstream oss;
        oss << "INSERT INTO notifications.users_notifications (id, theme, message, email, sending_time, jwt) "
            << "VALUES (" << id << ", '" << theme << "', '" << message << "', '" << email << "', '"
            << std::put_time(&send_time_tm, "%Y-%m-%d %H:%M:%S") << "', '" << token << "');";

        std::string req3 = oss.str();
        db.executeQuery(req3);
        return true;
    }
    return false;
}

// удаляем уведомление в случае его нахождения в списке
bool Time_scheduler::deleteNotification(int id, const std::string& token, Database& db) {
    std::lock_guard<std::mutex> lock(m);
    std::string req = "SELECT * FROM notifications.users_notifications "
                      "WHERE id = " + std::to_string(id) +
                      " AND jwt = '" + token + "';";
    pqxx::result res = db.executeQuery(req);
    if (!res.empty()) {
        std::string req2 = "DELETE FROM notifications.users_notifications "
                           "WHERE id = " + std::to_string(id) +
                           " AND jwt = '" + token + "';";
        db.executeQuery(req2);
        return true;
    }
    return false;
}

std::vector<Time_scheduler::Notification> Time_scheduler::getNotifications(std::string token) {
    std::lock_guard<std::mutex> lock(m);
    return users[token];
}

