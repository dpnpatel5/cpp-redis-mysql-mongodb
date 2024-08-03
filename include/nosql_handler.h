#ifndef NOSQL_HANDLER_H
#define NOSQL_HANDLER_H

#include <bsoncxx/document/view.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/collection.hpp>
#include <mongocxx/database.hpp>
#include <string>
#include <memory>

class NoSQLHandler {
public:
    NoSQLHandler(const std::string& uri);
    void insertDocument(const std::string& dbName, const std::string& collectionName, const std::string& jsonDocument);
    void deleteDocument(const std::string& dbName, const std::string& collectionName, const std::string& filterJson);
    void updateDocument(const std::string& dbName, const std::string& collectionName, const std::string& filterJson, const std::string& updateJson);

private:
    mongocxx::client client;
};

#endif // NOSQL_HANDLER_H

