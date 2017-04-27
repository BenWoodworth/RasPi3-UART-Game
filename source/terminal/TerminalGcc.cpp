#include <string>
#include <iostream>
#include <stdint.h>
#include "terminal/TerminalGcc.h"

#ifdef _WIN32
    #include <conio.h>
#else 
    #include <ncurses.h>
#endif

void TerminalGcc::printChar(uint8_t c) {
    std::cout << c << std::flush;
}

void TerminalGcc::printStr(std::string str) {
    std::cout << str << std::flush;
}

void TerminalGcc::printNumDec(int32_t num) {
    std::cout << num << std::flush;
}

uint8_t TerminalGcc::hasChar(){
    #ifdef _WIN32
    return kbhit();
    #else
    int c = getch();
    if(c != ERR){
        ungetch(c);
        return 1;
    }else{
        return 0;
    }
    #endif
}

uint8_t TerminalGcc::getChar() {
   return getch(); 
}
