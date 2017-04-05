#include "Terminal.h"

#ifndef TERMINALCONSOLE_H
#define TERMINALCONSOLE_H

class TerminalConsole : public Terminal {

    void printChar(char c);

    int readChar();
};

#endif
