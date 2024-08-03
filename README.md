# cpp-redis-mysql-mongodb

Demo for RDBMS (MySQL), NoSQL (MongoDB), and Redis caching for efficient data handling and performance.

## Features

- Supports MySQL for relational database operations.
- Supports MongoDB for NoSQL database operations.
- Uses Redis for caching user data.
- Configurable via CMake options.

## Dependencies

- CMake 3.14 or higher
- MySQL Connector/C++ (`mysqlcppconn`)
- MongoDB C++ driver (`mongocxx` and `bsoncxx`)
- Redis client library (`hiredis`)
- JSONCPP for JSON handling

## Getting Started

### Prerequisites

Make sure you have the following packages installed:

- MySQL Connector/C++
- MongoDB C++ driver
- Redis
- JSONCPP

### Installing Dependencies

#### On Ubuntu

1. **Install MySQL Connector/C++:**

    ```bash
    sudo apt-get install libmysqlcppconn-dev
    ```

2. **Install MongoDB C++ Driver:**

    Follow the instructions [here](https://www.mongodb.com/docs/languages/cpp/cpp-driver/current/installation/linux/) to install the MongoDB C++ driver.

3. **Install Redis Client Library:**

    ```bash
    sudo apt-get install libhiredis-dev
    ```

4. **Install JSONCPP:**

    ```bash
    sudo apt-get install libjsoncpp-dev
    ```

### Building the Project

1. **Clone the repository:**

    ```bash
    git clone https://github.com/dpnpatel5/cpp-redis-mysql-mongodb
    cd cpp-redis-mysql-mongodb
    ```

2. **Configure the project with CMake:**

    By default, the project is configured to use MySQL. You can specify the database type by setting the `DB_TYPE` option to either `MYSQL` or `NOSQL`.

    ```bash
    mkdir build
    cd build
    cmake -DDB_TYPE=MYSQL ..
    ```

    or for NoSQL (MongoDB):

    ```bash
    mkdir build
    cd build
    cmake -DDB_TYPE=NOSQL ..
    ```

3. **Build the project:**

    ```bash
    make
    ```

### Running the Application

After successfully building the project, you can run the executable:

```bash
./my_app

