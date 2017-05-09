#include "pi3/timer/TimerPi3.h"

void TimerPi3::start() {
    this->startTime = SYS_TIMER[SYS_TIMER_C0];
}

void TimerPi3::waitMicro(uint32_t us) {
    uint32_t currentTime = SYS_TIMER[SYS_TIMER_C0];
    uint32_t elapsed = this->startTime - currentTime;
    
    // If time already elapsed, return
    if (us <= elapsed) {
        return;
    }

    // Add the delay to the current count
    // and, put that into compare 0's register
    SYS_TIMER[SYS_TIMER_C0] = currentTime + us - elapsed;

    // Clear M0
    SYS_TIMER[SYS_TIMER_CS] = 1;

    // Wait until the CS register has a 1 in
    // the 0 position, which happens when the
    // timer expires.
    while (!(SYS_TIMER[SYS_TIMER_CS] & 1));
}
