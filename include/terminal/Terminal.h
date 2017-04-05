#ifndef TERMINAL_H
#define TERMINAL_H

/// An abstraction of a terminal
class Terminal {
public:
    /// Prints a character to the terminal.
    virtual void printChar(char ch) = 0;

    /// Prints a null-terminated string to the terminal.
    void printStr(char *str);

    /// Reads a character from the terminal buffer.
    /// Will not wait for a character to be entered.
    /// If there is no character to read, returns -1.
    virtual int readChar() = 0;
};

#endif
