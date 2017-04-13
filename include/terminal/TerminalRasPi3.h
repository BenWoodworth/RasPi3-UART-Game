#include "Terminal.h"

#ifndef TERMINALRASPI3_H_
#define TERMINALRASPI3_H_

class TerminalRasPi3 : public Terminal {
public:
    void printChar(char c);

    int readChar();
};

#endif
