#include <string>

#include "core/terminal/Terminal.h"
#include "core/graphics/Colors.h"

Key Terminal::getKey() {
    return Key(getChar());
}

void Terminal::clear() {
    printStr("\x1B[2J");
}

void Terminal::newLine() {
    printStr("\r\n");
}

void Terminal::resetStyling() {
    printStr("\x1B[0m");
}

void Terminal::setCursorVisibility(bool visible) {
    printStr("\x1B[?25");
    printChar(visible ? 'h' : 'l');
}

void Terminal::moveCursor(int32_t down, int32_t right) {
    // Move cursor up/down
    if (down != 0) {
        printStr("\x1B[");
        if (down > 0) {
            printNumDec(down);
            printChar('B'); // Cursor down
        } else {
            printNumDec(-down);
            printChar('A'); // Cursor up
        }
    }
    
    // Move cursor left/right
    if (right != 0) {
        printStr("\x1B[");
        if (right > 0) {
            printNumDec(right);
            printChar('C'); // Cursor right
        } else {
            printNumDec(-right);
            printChar('D'); // Cursor left
        }
    }
}

void Terminal::setCursorPosition(int32_t row, int32_t col) {
    printStr("\x1B[");
    printNumDec(row);
    printChar(';');
    printNumDec(col);
    printChar('f');
}

void Terminal::moveCursorToLineStart(int32_t rowsDown) {
    printStr("\x1B[");
    if (rowsDown > 0) {
        printNumDec(rowsDown);
        printChar('E');
    } else {
        printNumDec(-rowsDown);
        printChar('F');
    }
}

void Terminal::setColor(uint8_t color, bool foreground) {
    if (color == Colors::NONE) {
        return;
    }

    printStr("\x1B[");
    printChar(foreground ? '3' : '4');
    printStr("8;5;");
    printNumDec(color);
    printChar('m');
}

void Terminal::saveCursorPos() {
    printStr("\x1B[s");
}

void Terminal::restoreCursorPos() {
    printStr("\x1B[u");
}
