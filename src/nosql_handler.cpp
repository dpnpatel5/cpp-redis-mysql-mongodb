#include "nosql_handler.h"
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

NoSQLHandler::NoSQLHandler(const std::string& uri) : client(mongocxx::uri{uri}) {}

void NoSQLHandler::insertDocument(const std::string& dbName, const std::string& collectionName, const std::string& jsonDocument) {
    auto db = client[dbName];
    auto collection = db[collectionName];
    auto document = bsoncxx::from_json(jsonDocument);
    collection.insert_one(document.view());
}

void NoSQLHandler::deleteDocument(const std::string& dbName, const std::string& collectionName, const std::string& filterJson) {
    auto db = client[dbName];
    auto collection = db[collectionName];
    auto filter = bsoncxx::from_json(filterJson);
    collection.delete_one(filter.view());
}

void NoSQLHandler::updateDocument(const std::string& dbName, const std::string& collectionName, const std::string& filterJson, const std::string& updateJson) {
    auto db = client[dbName];
    auto collection = db[collectionName];
    auto filter = bsoncxx::from_json(filterJson);
    auto update = bsoncxx::from_json(updateJson);
    collection.update_one(filter.view(), update.view());
}

