#include "timer/TimerGcc.h"
#include <chrono>
#include <thread>

void TimerGcc::start() {
    /* No Op */
}

void TimerGcc::waitMicro(uint32_t us) {
    //Treads are pretty great
    //Sleep the currtly active treads for the given time
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}
