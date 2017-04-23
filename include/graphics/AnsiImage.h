#ifndef ANSIIMAGE_H_
#define ANSIIMAGE_H_

#include "terminal/Terminal.h"

struct AnsiPixel {
    uint8_t bgColorR, bgColorG, bgColorB;
    uint8_t fgColorR, fgColorG, fgColorB;
    char character;
};

class AnsiImage {
private:
    uint32_t width;
    uint32_t height;

    AnsiPixel* pixels;
public:

    /// Create an ANSI image with the given width and height.
    AnsiImage(uint8_t width, uint8_t height) {
        this->width = width;
        this->height = height;

        this->pixels = new AnsiPixel[width * height];
    }

    inline uint32_t getWidth() {
        return this->width;
    }

    inline uint32_t getHeight() {
        return this->height;
    }

    /// Get the pixel at the specified coordinate.
    inline AnsiPixel getPixel(uint32_t x, uint32_t y) {
        return this->pixels[x + y * width];
    }

    /// Set the pixel at the specified coordinate.
    inline void setPixel(uint32_t x, uint32_t y, AnsiPixel ansiPixel) {
        this->pixels[x + y * width] = ansiPixel;
    }

    /// Draw the image to the terminal.
    void drawToTerminal(Terminal* terminal);
};

#endif
