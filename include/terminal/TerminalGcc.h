#ifndef TERMINALGCC_H_
#define TERMINALGCC_H_

#include <stdint.h>
#include "terminal/Terminal.h"

class TerminalGcc : public Terminal {
public:
    void printChar(uint8_t c);

    int readChar();
};

#endif
