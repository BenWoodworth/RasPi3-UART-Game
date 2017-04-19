#ifndef TIMERRASPI3_H_
#define TIMERRASPI3_H_

#include <stdint.h>
#include "timer/Timer.h"

class TimerRasPi3 : public Timer {
public:
    void start();
    
    void waitMicro(uint32_t us);
};

#endif
