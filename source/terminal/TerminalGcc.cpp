#include <string>
#include <iostream>
#include <stdint.h>
#include "terminal/TerminalGcc.h"

void TerminalGcc::printChar(uint8_t c) {
    std::cout << c << std::flush;
}

void TerminalGcc::printStr(std::string str) {
    std::cout << str << std::flush;
}

void TerminalGcc::printNumDec(int32_t num) {
    std::cout << num << std::flush;
}

uint8_t TerminalGcc::readChar() {
    // TODO
    return 0;
}
