#include "RequestHandler.h"
using json = nlohmann::json;

bool RequestHandler::isValidEmail(const std::string& email) {
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

bool RequestHandler::validateToken(const std::string& token) {
    return scheduler.users.find(token) != scheduler.users.end();
}

std::string RequestHandler::generateAuthToken() {
    std::string s = "1234567890abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string token;
    for (int i = 0; i < 16; i++) {
        token += s[rand() % s.length()];
    }
    return token;
}

void RequestHandler::HttpPostToken(const httplib::Request& request, httplib::Response &res) {
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
    std::string message = "Привет! \n\nВот твой токен авторизации! \nЗапомни и не теряй его пожалуйста!\n" +
                          scheduler.db[{name, last_name}];
    std::string theme = "Получение токена авторизации";
    Email_sender sender;
    std::string path = "/Users/nazarzakrevskij/CLionProjects/NotificationsService/config.ini";
    std::string key = sender.getDataFromFile(path, "USERNAME");
    std::string application_password = sender.getDataFromFile(path, "APP_PASSWORD");
    std::string from = sender.getDataFromFile(path, "USERNAME");
    sender.sendEmailYandexApi(key, application_password, from,
                              email, theme, message);
}

void RequestHandler::HttpNotificationDelete(const httplib::Request& request, httplib::Response &res) {
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

void RequestHandler::HttpNotificationPutById(const httplib::Request& request, httplib::Response &res) {
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

void RequestHandler::HttpNotificationPost(const httplib::Request& request, httplib::Response &res, int id) {
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
}

void RequestHandler::HttpRegisterPost(const httplib::Request& request, httplib::Response &res) {
    auto parsed = json::parse(request.body);
    std::string name = parsed["name"];
    std::string last_name = parsed["last_name"];
    std::string token = generateAuthToken();
    scheduler.db[{name, last_name}] = token;
    scheduler.users[token] = std::vector<Time_scheduler::Notification>();
    json response = {
            {"auth_token", token}
    };
    res.set_content(response.dump(), "application/json");
}

void RequestHandler::HtttpNotificationsGet(const httplib::Request &request, httplib::Response &res) {
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