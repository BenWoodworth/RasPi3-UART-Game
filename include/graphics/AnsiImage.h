#ifndef ANSIIMAGE_H_
#define ANSIIMAGE_H_

#include <map>
#include <string>
#include "terminal/Terminal.h"

struct AnsiPixel {
    char character;
    uint32_t foreground;
    uint32_t background;
};

class AnsiImage {
private:
    uint32_t width;
    uint32_t height;

    AnsiPixel** pixels;

    void init(uint32_t width, uint32_t height) {
        this->width = width;
        this->height = height;

        pixels = new AnsiPixel*[width * height];
        for (int i = 0; i < width * height; i++) {
            pixels[i] = NULL;
        }
    }
public:
    /// Create an ANSI image with the given width and height.
    AnsiImage(uint32_t width, uint32_t height) {
        init(width, height);
    }

    AnsiImage(uint32_t width, uint32_t height, std::map<char, AnsiPixel> mapping, std::string imageLayout) {
        init(width, height);

        for (int i = 0; i < imageLayout.size(); i++) {
            char c = imageLayout[i];
            if (mapping.find(c) != mapping.end()) {
                pixels[i] = &mapping[c];
            }
        }
    }

    inline uint32_t getWidth() {
        return this->width;
    }

    inline uint32_t getHeight() {
        return this->height;
    }

    /// Get the pixel at the specified coordinate.
    inline AnsiPixel* getPixel(uint32_t x, uint32_t y) {
        return this->pixels[x + y * width];
    }

    /// Set the pixel at the specified coordinate.
    inline void setPixel(uint32_t x, uint32_t y, AnsiPixel* ansiPixel) {
        this->pixels[x + y * width] = ansiPixel;
    }

    /// Draw the image to the terminal.
    void drawToTerminal(Terminal* terminal);
};

#endif
