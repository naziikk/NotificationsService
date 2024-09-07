#include <iostream>
#include "libraries/httplib.h"
#include <thread>
#include "backend/multithread_notification_scheduler/Time_scheduler.h"
#include "libraries/nlohmann/json.hpp"
#include <unordered_map>
#include <fstream>
#include <regex>

Time_scheduler scheduler;
std::unordered_map<int, Time_scheduler::Notification> mp;
int id = 1;
using json = nlohmann::json;
std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

bool isValidEmail(const std::string& email) {
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

std::string generateAuthToken() {
    std::string s = "1234567890abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string token;
    for (int i = 0; i < 16; i++) {
        token += s[rand() % s.length()];
    }
    return token;
}

std::string user_token;
int main() {
    std::thread worker(&Time_scheduler::workerThread, &scheduler);
    httplib::Server server;
    server.Get("/", [](const httplib::Request& request, httplib::Response& res) {
        std::string content = read_file("/Users/nazarzakrevskij/CLionProjects/Notification-Service/interface/index.html");
        res.set_content(content, "text/html");
    });
    server.Post("/register", [](const httplib::Request& request, httplib::Response &res) {
        auto parsed = json::parse(request.body);
        std::string name = parsed["name"];
        std::string token = generateAuthToken();
        json response = {
                {"status", "done"},
                {"auth_token", token}
        };
        res.set_content(response.dump(), "application/json");
    });
    server.Post("/login", [](const httplib::Request& request, httplib::Response &res) {
        auto parsed = json::parse(request.body);
        std::string name = parsed["name"];
        std::string last_name = parsed["last_name"];
        std::string token = parsed["token"];
        if (1) {
            json response = {
                    {"status", "success"},
            };
            user_token = token;
            res.set_content(response.dump(), "application/json");
        }
        else {
            res.status = 401;
            res.set_content(R"({"status": "Unauthorized"})", "application/json");
        }
    });
    server.Post("/notifications", [](const httplib::Request& request, httplib::Response &res) {
        auto parsed = json::parse(request.body);
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
        }
        scheduler.scheduleNotification(id, recipient, theme, message, scheduled_time_tm, user_token);
        id++;
        json response = {
                {"status", "queued"},
                {"id", std::to_string(id - 1)},
                {"scheduled_time", scheduled_time_str}
        };
        res.set_content(response.dump(), "application/json");
    });
    server.Put("/notifications/(.*)", [](const httplib::Request& request, httplib::Response &res) {
        int id_1 = std::stoi(request.matches[1]);
        auto parsed = json::parse(request.body);
        std::string theme = parsed["type"];
        std::string recipient = parsed["recipient"];
        std::string message = parsed["message"];
        std::string scheduled_time_str = parsed["scheduled_time"];
        std::tm scheduled_time_tm = {};
        std::istringstream ss(scheduled_time_str);
        ss >> std::get_time(&scheduled_time_tm, "%Y-%m-%dT%H:%M:%S");
        bool flag = scheduler.updateNotificationDetails(id_1, recipient, theme, message, scheduled_time_tm, user_token);
        if (!isValidEmail(recipient)) {
            res.status = 400;
            res.set_content(R"({"status": "bad request"})", "application/json");
        }
        if (flag) {
            res.set_content(R"({"status": "updated", "id": ")" + std::to_string(id_1) + R"("})", "application/json");
        }
        else {
            res.status = 404;
            res.set_content(R"({"status": "not found"})", "application/json");
        }
    });
    server.Delete("/notifications/(.*)", [](const httplib::Request& request, httplib::Response &res) {
        int id_1 = std::stoi(request.matches[1]);
        bool flag = scheduler.deleteNotification(id_1, user_token);
        if (flag) {
            res.set_content(R"({"status": "deleted", "id": ")" + std::to_string(id_1) + R"("})", "application/json");
        }
        else {
            res.status = 404;
            res.set_content(R"({"status": "not found"})", "application/json");
        }
    });
    std::cout << "Server is listening http://localhost:8080" << '\n';
    server.listen("0.0.0.0", 8080);
    worker.join();
    return 0;
}