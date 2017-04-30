#ifndef TERMINALGCC_H_
#define TERMINALGCC_H_

#include <string>
#include <stdint.h>
#include "terminal/Terminal.h"

class TerminalGcc : public Terminal {
public:
    void printChar(uint8_t c);

    void printStr(std::string str);

    void printNumDec(int32_t num);

    bool hasChar();

    uint8_t getChar();

    uint8_t getKey(uint8_t ch);
};

#endif
