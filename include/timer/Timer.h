#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

class Timer {
public:
    /// Start the timer.
    virtual void start() = 0;

    /// Wait for the number of microseconds to elapse
    /// since the timer started.
    virtual void waitMicro(uint32_t us) = 0;

    /// Wait for the number of milliseconds to elapse
    /// since the timer started.
    inline void waitMilli(uint32_t ms) {
        waitMicro(ms * 1000);
    }

    /// Wait for the number of seconds to elapse since
    /// the timer started.
    inline void wait(uint32_t sec) {
        waitMilli(sec * 1000);
    }
};

#endif
