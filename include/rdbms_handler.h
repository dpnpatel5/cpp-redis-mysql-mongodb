#ifndef RDBMS_HANDLER_H
#define RDBMS_HANDLER_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h> 
#include <string>
#include <memory>

class RDBMSHandler {
public:
    RDBMSHandler(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname);
    ~RDBMSHandler();

    void executeQuery(const std::string& query);
    std::string escapeString(const std::string& str);

private:
    std::unique_ptr<sql::mysql::MySQL_Driver> driver;
    std::unique_ptr<sql::Connection> connection;
};

#endif // RDBMS_HANDLER_H

