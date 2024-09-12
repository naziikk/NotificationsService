#ifndef NOTIFICATIONSSERVICE_POSTGRESPROCESSIN_H
#define NOTIFICATIONSSERVICE_POSTGRESPROCESSIN_H
#include "pqxx/pqxx"
#include <iostream>

class Database {
pqxx::connection conn_;

public:
    Database() {};

    Database(const std::string& con);

    void executeQuery(const std::string& query);
};


#endif //NOTIFICATIONSSERVICE_POSTGRESPROCESSIN_H
