#include "PostgresProcessing.h"

Database::Database(const std::string& con) : conn_(con) { }

void Database::executeQuery(const std::string &query) {
    try {
        pqxx::work txn(conn_);
        pqxx::result res = txn.exec(query);
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "Errror: " << e.what() << '\n';
    }
}
