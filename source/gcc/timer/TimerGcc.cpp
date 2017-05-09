#include <chrono>

#include "gcc/timer/TimerGcc.h"

std::chrono::time_point<std::chrono::system_clock> startTime;

void TimerGcc::start() {
    startTime = std::chrono::system_clock::now();
}

void TimerGcc::waitMicro(uint32_t us) {
    auto endTime = startTime.time_since_epoch() + std::chrono::microseconds(us);
    
    auto now = std::chrono::system_clock::now().time_since_epoch();

    
    while(now < endTime){
          now = std::chrono::system_clock::now().time_since_epoch();
    }

}
