#include "Terminal.h"

#ifndef TERMINALUART_H
#define TERMINALUART_H

class TerminalUart : public Terminal {

    void printChar(char c);

    int readChar();
};

#endif
