#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H

#include <sw/redis++/redis++.h>
#include <string>
#include <stdexcept>

class RedisHandler {
public:
    RedisHandler(const std::string& host, int port);
    
    void hset(const std::string& key, const std::string& field, const std::string& value);
    std::string hget(const std::string& key, const std::string& field);
    void del(const std::string& key);

private:
    sw::redis::Redis redisClient;
};

#endif // REDIS_HANDLER_H

