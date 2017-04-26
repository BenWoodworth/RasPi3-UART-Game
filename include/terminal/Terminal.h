#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <string>
#include <stdint.h>

class Terminal {
public:
    /// Prints a character to the terminal.
    virtual void printChar(uint8_t ch) = 0;

    /// Prints a string to the terminal.
    virtual void printStr(std::string str) = 0;

    /// Print a decimal number.
    virtual void printNumDec(int32_t num) = 0;

    /// Reads a character from the terminal buffer.
    /// Will not wait for a character to be entered.
    /// If there is no character to read, returns -1.
    virtual uint8_t readChar() = 0;

    /// Clear the terminal.
    void clear();

    /// Send a new line to the terminal.
    void newLine();

    /// Reset Select Graphic Rendition parameters.
    void resetStyling();

    /// Set the visibility of the cursor.
    void setCursorVisibility(bool visible);

    /// Move the cursor.
    void moveCursor(int32_t down, int32_t right);

    /// Set the cursor position.
    void setCursorPosition(int32_t row, int32_t col);

    /// Move the cursor to the beginning of the line the
    /// specified number of rows down.
    void moveCursorToLineStart(int32_t rowsDown);

    /// Set the color given an xterm 256-color.
    /// Sets background if foreground is false.
    void setColor(uint8_t rgb, bool foreground);

    /// Save the cursor position.
    void Terminal::saveCursorPos();

    /// Restore the cursor position.
    void Terminal::restoreCursorPos();
};

#endif
