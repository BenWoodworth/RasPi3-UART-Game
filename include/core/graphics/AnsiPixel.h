#ifndef ANSIPIXEL_H_
#define ANSIPIXEL_H_

#include "graphics/Colors.h"

class AnsiPixel {
private:
    char character;
    uint8_t foreground;
    uint8_t background;

public:
    /// Construct a new AnsiPixel.
    AnsiPixel(uint8_t background = Colors::NONE, uint8_t foreground = Colors::NONE,
              char character = ' ') {
        this->character = character;
        this->foreground = foreground;
        this->background = background;
    }

    /// Get the character on this pixel.
    inline char getCharacter() {
        return character;
    }

    /// Get the foreground color of this pixel.
    inline uint8_t getForeground() {
        return foreground;
    }

    /// Get the background color of this pixel.
    inline uint8_t getBackground() {
        return background;
    }
};

#endif
