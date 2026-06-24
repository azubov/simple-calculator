#include "SystemSignal.h"
#include "Log.h"

#include <csignal>
#include <systemd/sd-daemon.h>

SystemSignal::SystemSignal(
    std::initializer_list<int> signals, std::function<void()> on_signal_action
)
    : mask_{}
    , on_signal_action_(std::move(on_signal_action)) {

    sigemptyset(&mask_);
    for (int sig : signals) {
        sigaddset(&mask_, sig);
    }
    pthread_sigmask(SIG_BLOCK, &mask_, nullptr);
}

void SystemSignal::listen() {
    Log::info("Listening for the signal..");
    int sig = 0;
    sigwait(&mask_, &sig);
    sd_notify(0, "STOPPING=1");
    Log::info("Signal received");
    on_signal_action_();
}

void SystemSignal::ready() {
    sd_notify(0, "READY=1");
}