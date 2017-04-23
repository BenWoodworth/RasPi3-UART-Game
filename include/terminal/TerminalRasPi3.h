#ifndef TERMINALRASPI3_H_
#define TERMINALRASPI3_H_

#include <stdint.h>
#include "terminal/Terminal.h"

class TerminalRasPi3 : public Terminal {
public:
    void printChar(uint8_t c);

    uint8_t readChar();
};

#endif
