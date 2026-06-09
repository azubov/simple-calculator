#pragma once

#include "Server.h"

#include <zmq.hpp>

class ZmqServer : public Server {
public:
    explicit ZmqServer(const std::string& endpoint);
    std::pair<bool, std::string> receive() override;
    void send(const std::string& reply) override;

private:
    zmq::context_t context_;
    zmq::socket_t socket_;
};