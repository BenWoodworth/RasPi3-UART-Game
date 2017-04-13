#include "Timer.h"

#ifndef TIMERRASPI3_H_
#define TIMERRASPI3_H_

class TimerRasPi3 : public Timer {
public:
    void start();
    
    void waitElapsedMicro(uint32_t us);
};

#endif
