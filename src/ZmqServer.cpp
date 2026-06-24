#include "ZmqServer.h"

ZmqServer::ZmqServer(const std::string& endpoint)
    : context_(1)
    , socket_(context_, zmq::socket_type::rep) {
    socket_.bind(endpoint);
}

std::pair<bool, std::string> ZmqServer::receive() {
    zmq::message_t request;
    auto res = socket_.recv(request, zmq::recv_flags::dontwait);
    if (res) {
        return {true, request.to_string()};
    }
    return {false, ""};
}

void ZmqServer::send(const std::string& reply) {
    socket_.send(zmq::buffer(reply), zmq::send_flags::none);
}