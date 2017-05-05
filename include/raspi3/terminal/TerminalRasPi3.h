#ifndef TERMINALRASPI3_H_
#define TERMINALRASPI3_H_

#include <stdint.h>
#include "terminal/Terminal.h"

class TerminalRasPi3 : public Terminal {
public:
    void printChar(uint8_t ch);

    void printStr(std::string str);

    void printNumDec(int32_t num);

    uint8_t getChar();

    bool hasChar();
};

#endif
