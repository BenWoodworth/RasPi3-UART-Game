#include <string>
#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include "terminal/TerminalGcc.h"

#ifdef _WIN32
    #include <conio.h>
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define KEY_ENTER '/r'
#else 
    #include <termios.h>
    #include <sys/select.h>

    #define ESC 27
    #define KEY_UP 65
    #define KEY_DOWN 66
    #define KEY_LEFT 68
    #define KEY_RIGHT 67
    #define KEY_ENTER '/r'
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
        // Found this online. Magic that workd, credit below
        // http://cc.byexamples.com/2007/04/08/non-blocking-user-input-in-loop-without-ncurses/

        // TODO: Move this stuff to initialize function
        struct termios ttystate;
        //get the terminal state
        tcgetattr(STDIN_FILENO, &ttystate);
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
        //set the terminal attributes.
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate); 

        struct timeval tv;
        fd_set fds;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
        select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
        return FD_ISSET(STDIN_FILENO, &fds);
    #endif
}

uint32_t TerminalGcc::getChar() {
    #ifdef _WIN32
        return getch();
    #else
        return fgetc(stdin);
    #endif
}
