#include "Terminal.h"

#ifndef TERMINALUART_H
#define TERMINALUART_H

class TerminalUart : public Terminal {
public:
    void printChar(char c);

    int readChar();
};

#endif
