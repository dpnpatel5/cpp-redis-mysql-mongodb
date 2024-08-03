#include "redis_handler.h"
#include <iostream>

RedisHandler::RedisHandler(const std::string& host, int port) {
    context = redisConnect(host.c_str(), port);
    if (context == nullptr || context->err) {
        if (context) {
            std::cerr << "Redis connection error: " << context->errstr << std::endl;
            redisFree(context);
        } else {
            std::cerr << "Redis connection error: Can't allocate redis context" << std::endl;
        }
    }
}

RedisHandler::~RedisHandler() {
    if (context) {
        redisFree(context);
    }
}

void RedisHandler::set(const std::string& key, const std::string& value) {
    redisReply* reply = (redisReply*)redisCommand(context, "SET %s %s", key.c_str(), value.c_str());
    if (reply == nullptr) {
        std::cerr << "Redis SET command error" << std::endl;
    }
    freeReplyObject(reply);
}

std::string RedisHandler::get(const std::string& key) {
    redisReply* reply = (redisReply*)redisCommand(context, "GET %s", key.c_str());
    std::string value;
    if (reply == nullptr) {
        std::cerr << "Redis GET command error" << std::endl;
    } else if (reply->type == REDIS_REPLY_STRING) {
        value = reply->str;
    }
    freeReplyObject(reply);
    return value;
}

