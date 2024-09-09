#include <iostream>
#include <thread>
#include <unordered_map>
#include <fstream>
#include <regex>
#include "libraries/httplib.h"
#include "libraries/nlohmann/json.hpp"
#include "backend/multithread_notification_scheduler/Time_scheduler.h"

using json = nlohmann::json;

Time_scheduler scheduler;
int id = 1;

bool isValidEmail(const std::string& email) {
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

bool validateToken(const std::string& token) {
    return scheduler.users.find(token) != scheduler.users.end();
}

std::string generateAuthToken() {
    std::string s = "1234567890abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string token;
    for (int i = 0; i < 16; i++) {
        token += s[rand() % s.length()];
    }
    return token;
}

void HttpPostToken(const httplib::Request& request, httplib::Response &res) {
    auto parsed = json::parse(request.body);
    std::string name = parsed["name"];
    std::string last_name = parsed["last_name"];
    std::string email = parsed["email"];

    if (!isValidEmail(email)) {
        res.status = 400;
        res.set_content(R"({"status": "bad request"})", "application/json");
        return;
    }

    if (scheduler.db.find({name, last_name}) == scheduler.db.end()) {
        res.status = 401;
        res.set_content(R"({"status": "Unauthorized"})", "application/json");
        return;
    }

    std::string token = scheduler.db[{name, last_name}];
    std::string message = R"(
        <html>
            <body>
                <p>Добро пожаловать!</p>
                <p>Ваш токен авторизации готов. Пожалуйста, храните его в безопасности и не передавайте третьим лицам!</p>
                <details>
                    <summary>Нажмите, чтобы увидеть токен</summary>
                    <p>)" + token + R"(</p>
                </details>
            </body>
        </html>
    )";

    std::string theme = "Получение токена авторизации";
    Email_sender sender;
    std::string path = "/Users/nazarzakrevskij/CLionProjects/NotificationsService/config.ini";
    std::string key = sender.getDataFromFile(path, "USERNAME");
    std::string application_password = sender.getDataFromFile(path, "APP_PASSWORD");
    std::string from = sender.getDataFromFile(path, "USERNAME");

    sender.sendEmailYandexApi(key, application_password, from, email, theme, message, true);
}

void HttpNotificationDelete(const httplib::Request& request, httplib::Response &res) {
    int id_1 = std::stoi(request.matches[1]);
    auto parsed = json::parse(request.body);
    std::string token = parsed["auth_token"];
    if (!validateToken(token)) {
        res.status = 403;
        res.set_content(R"({"status": "access denied"})", "application/json");
        return;
    }
    bool flag = scheduler.deleteNotification(id_1, token);
    if (flag) {
        res.set_content(R"({"status": "deleted", "id": ")" + std::to_string(id_1) + R"("})", "application/json");
    } else {
        res.status = 404;
        res.set_content(R"({"status": "not found"})", "application/json");
    }
}

void HttpNotificationPutById(const httplib::Request& request, httplib::Response &res) {
    int id_1 = std::stoi(request.matches[1]);
    auto parsed = json::parse(request.body);
    std::string token = parsed["auth_token"];
    if (!validateToken(token)) {
        res.status = 403;
        res.set_content(R"({"status": "access denied"})", "application/json");
        return;
    }
    std::string theme = parsed["type"];
    std::string recipient = parsed["recipient"];
    std::string message = parsed["message"];
    std::string scheduled_time_str = parsed["scheduled_time"];
    std::tm scheduled_time_tm = {};
    std::istringstream ss(scheduled_time_str);
    ss >> std::get_time(&scheduled_time_tm, "%Y-%m-%dT%H:%M:%S");
    if (!isValidEmail(recipient)) {
        res.status = 400;
        res.set_content(R"({"status": "bad request"})", "application/json");
        return;
    }
    bool flag = scheduler.updateNotificationDetails(id_1, recipient, theme, message, scheduled_time_tm, token);
    if (flag) {
        res.set_content(R"({"status": "updated", "id": ")" + std::to_string(id_1) + R"("})", "application/json");
    } else {
        res.status = 404;
        res.set_content(R"({"status": "not found"})", "application/json");
    }
}

void HttpNotificationPost(const httplib::Request& request, httplib::Response &res, int id) {
    auto parsed = json::parse(request.body);
    std::string token = parsed["auth_token"];
    if (!validateToken(token)) {
        res.status = 403;
        res.set_content(R"({"status": "access denied"})", "application/json");
        return;
    }

    std::string theme = parsed["type"];
    std::string recipient = parsed["recipient"];
    std::string message = parsed["message"];
    std::string scheduled_time_str = parsed["scheduled_time"];
    std::tm scheduled_time_tm = {};
    std::istringstream ss(scheduled_time_str);
    ss >> std::get_time(&scheduled_time_tm, "%Y-%m-%dT%H:%M:%S");

    if (!isValidEmail(recipient)) {
        res.status = 400;
        res.set_content(R"({"status": "bad request"})", "application/json");
        return;
    }

    scheduler.scheduleNotification(id, recipient, theme, message, scheduled_time_tm, token);
    id++;

    json response = {
            {"status", "queued"},
            {"id", std::to_string(id - 1)},
            {"scheduled_time", scheduled_time_str}
    };
    res.set_content(response.dump(), "application/json");

    return;
}

void HttpRegisterPost(const httplib::Request& request, httplib::Response &res) {
    auto parsed = json::parse(request.body);
    std::string name = parsed["name"];
    std::string last_name = parsed["last_name"];
    if (scheduler.db.find({name, last_name}) != scheduler.db.end()) {
        std::string token = scheduler.db[{name, last_name}];
        json response = {
                {"message", "You already have a token!"},
                {"auth_token", token}
        };
        res.set_content(response.dump(), "application/json");
        return;
    }
    std::string token = generateAuthToken();
    scheduler.db[{name, last_name}] = token;
    scheduler.users[token] = std::vector<Time_scheduler::Notification>();
    json response = {
            {"auth_token", token}
    };
    res.set_content(response.dump(), "application/json");
}

void HttpNotificationsGet(const httplib::Request &request, httplib::Response &res) {
    std::string token = request.matches[1];
    if (!validateToken(token)) {
        res.status = 403;
        res.set_content(R"({"status": "access denied"})", "application/json");
        return;
    }
    std::vector<Time_scheduler::Notification> arr = scheduler.getNotifications(token);
    nlohmann::json jsonResponse;
    for (const auto& el : arr) {
        jsonResponse.push_back({
               {"id", el.id},
               {"email", el.email},
               {"theme", el.theme},
               {"message", el.message},
               {"sending_time", std::chrono::system_clock::to_time_t(el.sending_time)}
       });
    }
    res.set_content(jsonResponse.dump(), "application/json");
}

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

int main() {
    std::thread worker(&Time_scheduler::workerThread, &scheduler);
    httplib::Server server;

    server.Get("/", [](const httplib::Request& request, httplib::Response& res) {
        std::string content = read_file("/Users/nazarzakrevskij/CLionProjects/NotificationsService/interface/index.html");
        res.set_content(content, "text/html");
    });

    server.Post("/register", [](const httplib::Request& request, httplib::Response &res) {
        HttpRegisterPost(request, res);
    });

    server.Post("/notifications", [](const httplib::Request& request, httplib::Response& res) {
        HttpNotificationPost(request, res, id);
    });

    server.Put("/notifications/(.*)", [](const httplib::Request& request, httplib::Response &res) {
        HttpNotificationPutById(request, res);
    });

    server.Delete("/notifications/(.*)", [](const httplib::Request& request, httplib::Response &res) {
        HttpNotificationDelete(request, res);
    });

    server.Post("/token", [](const httplib::Request& request, httplib::Response &res) {
        HttpPostToken(request, res);
    });

    server.Get("/notifications/(.*)", [](const httplib::Request& request, httplib::Response &res) {
        HttpNotificationsGet(request, res);
    });

    std::cout << "Server is listening http://localhost:8080" << '\n';
    server.listen("0.0.0.0", 8080);
    worker.join();
    return 0;
}