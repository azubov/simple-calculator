#pragma once

#include <functional>
#include <initializer_list>

class SystemSignal {
public:
    explicit SystemSignal(
        std::initializer_list<int> signals,
        std::function<void()> on_signal_action
    );

    void listen();
    void ready();

private:
    sigset_t mask_;
    std::function<void()> on_signal_action_;
};