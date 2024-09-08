#include <iostream>
#include "libraries/httplib.h"
#include <thread>
#include "backend/multithread_notification_scheduler/Time_scheduler.h"
#include <fstream>
#include "backend/request_handler/RequestHandler.h"

RequestHandler handler;
Time_scheduler scheduler;
int id = 1;

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
        handler.HttpRegisterPost(request, res);
    });

    server.Post("/notifications", [](const httplib::Request& request, httplib::Response &res) {
        handler.HttpNotificationPost(request, res, id);
    });

    server.Put("/notifications/(.*)", [](const httplib::Request& request, httplib::Response &res) {
        handler.HttpNotificationPutById(request, res);
    });

    server.Delete("/notifications/(.*)", [](const httplib::Request& request, httplib::Response &res) {
        handler.HttpNotificationDelete(request, res);
    });

    server.Post("/token", [](const httplib::Request& request, httplib::Response &res) {
        handler.HttpPostToken(request, res);
    });
    std::cout << "Server is listening http://localhost:8080" << '\n';
    server.listen("0.0.0.0", 8080);
    worker.join();
    return 0;
}