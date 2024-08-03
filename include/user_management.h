#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <string>

#ifdef USE_MYSQL
#include "rdbms_handler.h"  // Assume you have a header file for MySQL handler
#elif defined(USE_NOSQL)
#include "nosql_handler.h"  // Assume you have a header file for NoSQL handler
#else
#error "No database type specified. Please define USE_MYSQL or USE_NOSQL."
#endif

#include "redis_handler.h"  // Assume you have a header file for Redis handler

class User {
public:
    int id;
    std::string name;
    int age;
    std::string gender;

    // Default constructor
    User() : id(0), age(0) {}

    // Parameterized constructor
    User(int id, const std::string& name, int age, const std::string& gender)
        : id(id), name(name), age(age), gender(gender) {}
};

class UserManagement {
public:
    #ifdef USE_MYSQL
    UserManagement(RDBMSHandler& rdbms, RedisHandler& redis);
    #elif defined(USE_NOSQL)
    UserManagement(NoSQLHandler& nosql, RedisHandler& redis);
    #endif

    void createUser(const User& user);
    void deleteUser(int userId);
    void updateUser(const User& user);

private:
    #ifdef USE_MYSQL
    void createUserInRDBMS(const User& user);
    void deleteUserInRDBMS(int userId);
    void updateUserInRDBMS(const User& user);
    RDBMSHandler& rdbmsHandler;
    #elif defined(USE_NOSQL)
    void createUserInNoSQL(const User& user);
    void deleteUserInNoSQL(int userId);
    void updateUserInNoSQL(const User& user);
    NoSQLHandler& nosqlHandler;
    #endif

    RedisHandler& redisHandler;
    void cacheUser(const User& user); 
    User getCachedUser(const std::string& userId);


};

#endif // USER_MANAGEMENT_H

