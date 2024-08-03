#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H

#include <hiredis/hiredis.h>
#include <string>

class RedisHandler {
public:
    RedisHandler(const std::string& host, int port);
    ~RedisHandler();
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key);

private:
    redisContext* context;
};

#endif // REDIS_HANDLER_H

