#ifndef TERMINAL_H_
#define TERMINAL_H_

class Terminal {
public:
    /// Prints a character to the terminal.
    virtual void printChar(char ch) = 0;

    /// Reads a character from the terminal buffer.
    /// Will not wait for a character to be entered.
    /// If there is no character to read, returns -1.
    virtual int readChar() = 0;

    /// Prints a null-terminated string to the terminal.
    void printStr(char* str) {
        for (int i = 0; str[i]; i++) {
            printChar(str[i]);
        }
    }
};

#endif
