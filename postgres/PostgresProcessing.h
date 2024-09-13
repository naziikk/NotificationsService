#ifndef NOTIFICATIONSSERVICE_POSTGRESPROCESSIN_H
#define NOTIFICATIONSSERVICE_POSTGRESPROCESSIN_H
#include <pqxx/pqxx>
#include <iostream>
#include <fstream>

class Database {
pqxx::connection conn_;

public:
    Database() {};

    Database(const std::string& con);

    pqxx::result executeQuery(const std::string& query);

    void initDbFromFile(const std::string& filename);
};


#endif //NOTIFICATIONSSERVICE_POSTGRESPROCESSIN_H
