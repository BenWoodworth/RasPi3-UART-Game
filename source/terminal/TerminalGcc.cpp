#include <string>
#include <iostream>
#include <stdint.h>
#include "terminal/TerminalGcc.h"

#ifdef _WIN32
    #include <conio.h>
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define KEY_ENTER /r
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

bool TerminalGcc::hasChar(){
    #ifdef _WIN32
        return kbhit();
    #else
        // TODO: Move this to a constuctor
        // Curses Initialisations
        /*
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        */
        int c = getch();
        if (c != ERR) {
            ungetch(c);
            return true;
        }
        return false;
    #endif
}

uint8_t TerminalGcc::getChar() {
   return getch(); 
}

// 000 = 0 =  Nothing
// 001 = 1 = Up
// 010 = 2 = Down
// 011 = 3 = Left
// 100 = 4 = Right
// 101 = 5 = Enter
// 110 = 6 = Space

uint8_t TerminalGcc::getKey(uint8_t ch) {
    switch(ch){
        case KEY_UP:
            return 1;
            break;
        case KEY_DOWN:
            return 2;
            break;
        case KEY_LEFT:
            return 3;
            break;
        case KEY_RIGHT:
            return 4;
            break;
        case KEY_ENTER:
            return 5;
            break;
        case ' ':
            return 6;
            break;
    }
    return 0;
}
