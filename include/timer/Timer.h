#ifndef TIMER_H_
#define TIMER_H_

class Timer {
public:
    /// Start the timer.
    void start() = 0;

    /// Wait for the number of microseconds to elapse
    /// since the timer started.
    void waitElapsedMicro(uint32_t us) = 0;

    /// Wait for the number of milliseconds to elapse
    /// since the timer started.
    inline void waitElapsedMilli(uint32_t ms) {
        waitElapsedMicro(ms * 1000);
    }

    /// Wait for the number of seconds to elapse since
    /// the timer started.
    inline void waitElapsed(uint32_t sec) {
        waitElapsedMicro(sec * 1000000);
    }
};

#endif
