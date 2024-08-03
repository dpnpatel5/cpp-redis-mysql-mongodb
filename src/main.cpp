#include "user_management.h"
#include "redis_handler.h"
#include <iostream>

#ifdef USE_MYSQL
#include "rdbms_handler.h"
#elif defined(USE_NOSQL)
#include "nosql_handler.h"
#else
#error "No database type specified. Please define USE_MYSQL or USE_NOSQL."
#endif

int main() {
    #ifdef USE_MYSQL
    std::cout << "Application using MySql Database\n";
    RDBMSHandler rdbms("localhost", "dipen", "root123", "dipen_db");
    #elif defined(USE_NOSQL)
    std::cout << "Application using NoSql Database\n";
    NoSQLHandler nosql("mongodb://localhost:27017");
    #endif

    RedisHandler redis("localhost", 6379);

    #ifdef USE_MYSQL
    UserManagement userMgmt(rdbms, redis);
    #elif defined(USE_NOSQL)
    UserManagement userMgmt(nosql, redis);
    #endif

    int choice;
    do {
        std::cout << "1. Create User\n2. Delete User\n3. Update User\n4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline character left in the buffer

        switch (choice) {
            case 1: {
                int id, age;
                std::string name, gender;
                std::cout << "Enter user ID: ";
                std::cin >> id;
                std::cin.ignore(); // Ignore newline character left in the buffer
                std::cout << "Enter user name: ";
                std::getline(std::cin, name);
                std::cout << "Enter user age: ";
                std::cin >> age;
                std::cin.ignore(); // Ignore newline character left in the buffer
                std::cout << "Enter user gender: ";
                std::getline(std::cin, gender);
                User user(id, name, age, gender);
                userMgmt.createUser(user);
                break;
            }
            case 2: {
                int userId;
                std::cout << "Enter user ID to delete: ";
                std::cin >> userId;
                userMgmt.deleteUser(userId);
                break;
            }
            case 3: {
                int id, age;
                std::string name, gender;
                std::cout << "Enter user ID to update: ";
                std::cin >> id;
                std::cin.ignore(); // Ignore newline character left in the buffer
                std::cout << "Enter new user name: ";
                std::getline(std::cin, name);
                std::cout << "Enter new user age: ";
                std::cin >> age;
                std::cin.ignore(); // Ignore newline character left in the buffer
                std::cout << "Enter new user gender: ";
                std::getline(std::cin, gender);
                User user(id, name, age, gender);
                userMgmt.updateUser(user);
                break;
            }
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice\n";
                break;
        }
    } while (choice != 4);

    return 0;
}

