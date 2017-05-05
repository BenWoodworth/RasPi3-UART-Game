#ifndef TIMERRASPI3_H_
#define TIMERRASPI3_H_

#include <stdint.h>
#include "timer/Timer.h"

class TimerRasPi3 : public Timer {
private:
    volatile uintptr_t* SYS_TIMER = (uintptr_t*)0x20003000UL;
    uint8_t SYS_TIMER_CS = 0;
    // uint8_t SYS_TIMER_CLO = 1;
    // uint8_t SYS_TIMER_CHI = 2;
    uint8_t SYS_TIMER_C0 = 3;
    // uint8_t SYS_TIMER_C1 = 4;
    // uint8_t SYS_TIMER_C2 = 5;
    // uint8_t SYS_TIMER_C3 = 6;

    uint32_t startTime;
public:
    void start();
    
    void waitMicro(uint32_t us);
};

#endif
