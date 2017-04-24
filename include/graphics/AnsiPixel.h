#ifndef ANSIPIXEL_H_
#define ANSIPIXEL_H_

#include "graphics/Colors.h"

class AnsiPixel {
private:
    char character;
    uint32_t foreground;
    uint32_t background;

public:
    /// Construct a new AnsiPixel.
    AnsiPixel(uint32_t background = Colors::NONE, uint32_t foreground = Colors::NONE,
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
    inline uint32_t getForeground() {
        return foreground;
    }

    /// Get the background color of this pixel.
    inline uint32_t getBackground() {
        return background;
    }
};

#endif
