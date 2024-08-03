#include "user_management.h"
#include <iostream>
#include <stdexcept>

#ifdef USE_MYSQL
UserManagement::UserManagement(RDBMSHandler& rdbms, RedisHandler& redis)
    : rdbmsHandler(rdbms), redisHandler(redis) {}
#elif defined(USE_NOSQL)
UserManagement::UserManagement(NoSQLHandler& nosql, RedisHandler& redis)
    : nosqlHandler(nosql), redisHandler(redis) {}
#endif

void UserManagement::createUser(const User& user) {
    #ifdef USE_MYSQL
    createUserInRDBMS(user);
    #elif defined(USE_NOSQL)
    createUserInNoSQL(user);
    #endif
    cacheUser(std::to_string(user.id), user.name);
}

void UserManagement::deleteUser(int userId) {
    #ifdef USE_MYSQL
    deleteUserInRDBMS(userId);
    #elif defined(USE_NOSQL)
    deleteUserInNoSQL(userId);
    #endif
    redisHandler.set(std::to_string(userId), "");
}

void UserManagement::updateUser(const User& user) {
    #ifdef USE_MYSQL
    updateUserInRDBMS(user);
    #elif defined(USE_NOSQL)
    updateUserInNoSQL(user);
    #endif
    cacheUser(std::to_string(user.id), user.name);
}

#ifdef USE_MYSQL
void UserManagement::createUserInRDBMS(const User& user) {
    try {
        // Example SQL code for creating a user in MySQL
        rdbmsHandler.executeQuery(
            "CREATE TABLE IF NOT EXISTS users ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "name VARCHAR(255) NOT NULL, "
            "age INT NOT NULL, "
            "gender VARCHAR(10) NOT NULL)"
        );
        rdbmsHandler.executeQuery("INSERT INTO users (name, age, gender) VALUES ('" +
            rdbmsHandler.escapeString(user.name) + "', " +
            std::to_string(user.age) + ", '" +
            rdbmsHandler.escapeString(user.gender) + "')"
        );
    } catch (const std::exception& e) {
        throw std::runtime_error("Error creating user in RDBMS: " + std::string(e.what()));
    }
}

void UserManagement::deleteUserInRDBMS(int userId) {
    try {
        if (userId <= 0) {
            throw std::invalid_argument("Invalid user ID");
        }
        rdbmsHandler.executeQuery("DELETE FROM users WHERE id = " + std::to_string(userId));
    } catch (const std::exception& e) {
        throw std::runtime_error("Error deleting user from RDBMS: " + std::string(e.what()));
    }
}

void UserManagement::updateUserInRDBMS(const User& user) {
    try {
        if (user.id <= 0) {
            throw std::invalid_argument("Invalid user ID");
        }
        if (user.name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        rdbmsHandler.executeQuery("UPDATE users SET name = '" + 
            rdbmsHandler.escapeString(user.name) + "', age = " +
            std::to_string(user.age) + ", gender = '" +
            rdbmsHandler.escapeString(user.gender) + "' WHERE id = " + 
            std::to_string(user.id)
        );
    } catch (const std::exception& e) {
        throw std::runtime_error("Error updating user in RDBMS: " + std::string(e.what()));
    }
}
#elif defined(USE_NOSQL)
void UserManagement::createUserInNoSQL(const User& user) {
    try {
        nosqlHandler.insertDocument("mydb", "users_dipen", "{\"id\": " + std::to_string(user.id) +
            ", \"name\": \"" + user.name + "\", \"age\": " + std::to_string(user.age) +
            ", \"gender\": \"" + user.gender + "\"}");
    } catch (const std::exception& e) {
        throw std::runtime_error("Error creating user in NoSQL: " + std::string(e.what()));
    }
}

void UserManagement::deleteUserInNoSQL(int userId) {
    try {
        nosqlHandler.deleteDocument("mydb", "users_dipen", "{\"id\": " + std::to_string(userId) + "}");
    } catch (const std::exception& e) {
        throw std::runtime_error("Error deleting user from NoSQL: " + std::string(e.what()));
    }
}

void UserManagement::updateUserInNoSQL(const User& user) {
    try {
        nosqlHandler.updateDocument("mydb", "users_dipen", "{\"id\": " + std::to_string(user.id) + "}",
            "{\"$set\": {\"name\": \"" + user.name + "\", \"age\": " + std::to_string(user.age) +
            ", \"gender\": \"" + user.gender + "\"}}");
    } catch (const std::exception& e) {
        throw std::runtime_error("Error updating user in NoSQL: " + std::string(e.what()));
    }
}
#endif
void UserManagement::cacheUser(const std::string& userId, const std::string& userData) {
    redisHandler.set(userId, userData);
}

std::string UserManagement::getCachedUser(const std::string& userId) {
    return redisHandler.get(userId);
}
