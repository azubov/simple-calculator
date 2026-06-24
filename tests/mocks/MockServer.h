#pragma once

#include "Server.h"

#include <gmock/gmock.h>

class MockServer : public Server {
public:
    MOCK_METHOD((std::pair<bool, std::string>), receive, (), ());
    MOCK_METHOD(void, send, (const std::string&), ());
};
