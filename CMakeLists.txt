cmake_minimum_required(VERSION 3.14)  # FetchContent requires CMake 3.14+
project(MyApp)

set(CMAKE_CXX_STANDARD 17)
# Option to choose the database type
# Set default database type
if(NOT DEFINED DB_TYPE)
    set(DB_TYPE MYSQL CACHE STRING "Database type: MYSQL or NOSQL")
endif()

# Ensure DB_TYPE is valid
if(NOT (DB_TYPE STREQUAL "MYSQL" OR DB_TYPE STREQUAL "NOSQL"))
    message(FATAL_ERROR "Unknown DB_TYPE: ${DB_TYPE}. Please specify MYSQL or NOSQL.")
endif()

# Define compiler options based on DB_TYPE
if(DB_TYPE STREQUAL "MYSQL")
    message(STATUS "Compiling with MySQL support")
    # Add MySQL-specific definitions or source files
    add_definitions(-DUSE_MYSQL)
elseif(DB_TYPE STREQUAL "NOSQL")
    message(STATUS "Compiling with NoSQL support")
    # Add NoSQL-specific definitions or source files
    add_definitions(-DUSE_NOSQL)
endif()

set(CMAKE_PREFIX_PATH "/usr/local")

find_package(bsoncxx REQUIRED)
find_package(mongocxx REQUIRED)

include_directories(/usr/local/include/mongocxx/v_noabi)
include_directories(/usr/local/include/bsoncxx/v_noabi)
include_directories(/usr/local/include/bsoncxx/v_noabi/bsoncxx/third_party/mnmlstc)
include_directories(/usr/include/jsoncpp)

# Add source files
set(SOURCES
    src/main.cpp
    src/rdbms_handler.cpp
    src/nosql_handler.cpp
    src/user_management.cpp
    src/redis_handler.cpp
)

# Add headers
set(HEADERS
    include/rdbms_handler.h
    include/nosql_handler.h
    include/user_management.h
    include/redis_handler.h
)

# Create the executable
add_executable(my_app ${SOURCES})

# Specify include directories
# Specify include directories
target_include_directories(my_app PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(my_app
    mysqlcppconn
    hiredis
    mongocxx
    bsoncxx
    jsoncpp
)

# Optionally, include debugging information
set(CMAKE_BUILD_TYPE Debug)

