#ifndef ANSIIMAGE_H_
#define ANSIIMAGE_H_

#include <map>
#include <string>
#include "terminal/Terminal.h"
#include "graphics/AnsiPixel.h"

class AnsiImage {
private:
    uint32_t width;
    uint32_t height;

    AnsiPixel** pixels;
public:
    /// Create an ANSI image with the given width and height.
    AnsiImage(uint32_t width, uint32_t height) {
        this->width = width;
        this->height = height;

        pixels = new AnsiPixel*[width * height];
        for (int i = 0; i < width * height; i++) {
            pixels[i] = NULL;
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

    /// Write the image to the terminal.
    void writeToTerminal(Terminal* terminal);

    /// Get part of the image.
    AnsiImage* getSubImage(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    /// Draw an image onto this image.
    void drawImage(int32_t x, int32_t y, AnsiImage* image);

    /// Draw a filled rectangle with the given pixel.
    void drawRect(uint32_t x, uint32_t y, uint32_t width,
                  uint32_t height, AnsiPixel* pixel);
};

#endif
