#pragma once

#include <string>
#include <utility>

class Server {
public:
    virtual std::pair<bool, std::string> receive() = 0;
    virtual void send(const std::string& reply) = 0;
    virtual ~Server() = default;
};