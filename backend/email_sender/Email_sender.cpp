#include "Email_sender.h"

std::string Email_sender::getDataFromFile(const std::string& filename, const std::string& target) {
    std::ifstream file(filename);
    std::string line;
    std::string s;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(target) != std::string::npos) {
                int i = line.find('=');
                if (i != std::string::npos) {
                    s = line.substr(i + 1);
                    break;
                }
            }
        }
        file.close();
    } else {
        std::cout << "Невозможно прочесть данные из файла." << std::endl;
    }
    return s;
}

// some shit i don't understand what is going on
size_t read_data(void* ptr, size_t size, size_t nmemb, void* userp) {
    std::string* data = static_cast<std::string*>(userp);
    if (data->empty()) return 0;
    size_t bufferSize = size * nmemb;
    size_t sendSize = data->size() < bufferSize ? data->size() : bufferSize;
    memcpy(ptr, data->c_str(), sendSize);
    data->erase(0, sendSize);
    return sendSize;
}

bool Email_sender::sendEmailYandexApi(const std::string& email, const std::string& application_password,
                                      const std::string& from, const std::string& to,
                                      const std::string& theme, const std::string& message) {
    CURL* curl;
    CURLcode res = CURLE_OK;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string from_header = "From: " + from;
        std::string to_header = "To: " + to;
        std::string subj = "Subject: " + theme;
        std::string email_data = from_header + "\r\n" + to_header + "\r\n" + subj + "\r\n\r\n" + message + "\r\n";
        std::string url = "smtps://smtp.yandex.ru:465";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_USERNAME, email.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, application_password.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());
        struct curl_slist* recipients = nullptr;
        recipients = curl_slist_append(recipients, to.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data);
        curl_easy_setopt(curl, CURLOPT_READDATA, &email_data);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // optional for debugging
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Ошибка при отправке email: " << curl_easy_strerror(res) << '\n';
        }
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return res == CURLE_OK;
}