#include "timer/TimerGcc.h"
#include <chrono>
#include <thread>

std::chrono::time_point<std::chrono::system_clock> startTime;

void TimerGcc::start() {
    startTime = std::chrono::system_clock::now();
}

void TimerGcc::waitMicro(uint32_t us) {
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto endTime = startTime.time_since_epoch() + std::chrono::microseconds(us);
    if (now < endTime){
        std::this_thread::sleep_for(endTime - now);
    }
}
