#ifndef TIMERRASPI3_H_
#define TIMERRASPI3_H_

#include <stdint.h>
#include "timer/Timer.h"

class TimerRasPi3 : public Timer {
private:
    static volatile const uint32_t* SYS_TIMER = (uint32_t*) 0x20003000UL;
    static const uint8_t SYS_TIMER_CS = 0;
    static const uint8_t SYS_TIMER_CLO = 1;
    static const uint8_t SYS_TIMER_CHI = 2;
    static const uint8_t SYS_TIMER_C0 = 3;
    static const uint8_t SYS_TIMER_C1 = 4;
    static const uint8_t SYS_TIMER_C2 = 5;
    static const uint8_t SYS_TIMER_C3 = 6;

    uint32_t start;
public:
    void start();
    
    void waitMicro(uint32_t us);
};

#endif
