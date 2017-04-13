#include "Terminal.h"

#ifndef TERMINALGCC_H_
#define TERMINALGCC_H_

class TerminalGcc : public Terminal {
public:
    void printChar(char c);

    int readChar();
};

#endif
