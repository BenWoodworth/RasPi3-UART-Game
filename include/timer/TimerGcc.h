#include "Timer.h"

#ifndef TIMERGCC_H_
#define TIMERGCC_H_

class TimerGcc : public Timer {
public:
    void start();
    
    void waitElapsedMicro(uint32_t us);
};

#endif
