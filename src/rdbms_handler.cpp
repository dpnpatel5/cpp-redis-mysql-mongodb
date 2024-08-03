#include "rdbms_handler.h"
#include <iostream>
#include <stdexcept>

RDBMSHandler::RDBMSHandler(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname) {
    try {
        driver = std::unique_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());
        connection = std::unique_ptr<sql::Connection>(driver->connect(host, user, password));
        connection->setSchema(dbname);
    } catch (sql::SQLException &e) {
        std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
        throw;
    }
}

RDBMSHandler::~RDBMSHandler() {
    // No need to manually delete connection, smart pointers handle that
}

void RDBMSHandler::executeQuery(const std::string& query) {
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        stmt->execute(query);
    } catch (sql::SQLException &e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        throw;
    }
}

std::string RDBMSHandler::escapeString(const std::string& str) {
    std::string escaped;
    for (char c : str) {
        if (c == '\'') {
            escaped += "''"; // Escape single quotes
        } else {
            escaped += c;
        }
    }
    return escaped;
}

