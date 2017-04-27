#ifndef ANSIIMAGE_H_
#define ANSIIMAGE_H_

#include <map>
#include <string>
#include "terminal/Terminal.h"
#include "graphics/AnsiPixel.h"

class AnsiImage {
private:
    int32_t width;
    int32_t height;

    AnsiPixel** pixels;
public:
    /// Create an ANSI image with the given width and height.
    AnsiImage(int32_t width, int32_t height, AnsiPixel* fillColor = NULL) {
        this->width = width;
        this->height = height;

        pixels = new AnsiPixel*[width * height];
        for (int i = 0; i < width * height; i++) {
            pixels[i] = fillColor;
        }
    }

    /// Get the width of the image.
    inline int32_t getWidth() {
        return this->width;
    }

    /// Get the height of the image.
    inline int32_t getHeight() {
        return this->height;
    }

    /// Check to see if coordinates are within the bounds of the image.
    inline bool isInBounds(int32_t x, int32_t y) {
        return x >= 0 && x < getWidth() &&
               y >= 0 && y < getHeight();
    }

    /// Get the pixel at the specified coordinate.
    AnsiPixel* getPixel(int32_t x, int32_t y);

    /// Set the pixel at the specified coordinate.
    void setPixel(int32_t x, int32_t y, AnsiPixel* ansiPixel);

    /// Write the image to the terminal.
    void writeToTerminal(Terminal* terminal);

    /// Get part of the image.
    AnsiImage* getSubImage(int32_t x, int32_t y, int32_t width, int32_t height);

    /// Draw an image onto this image.
    void drawImage(int32_t x, int32_t y, AnsiImage* image);

    /// Draw a filled rectangle with the given pixel.
    void drawRect(int32_t x, int32_t y, int32_t width,
                  int32_t height, AnsiPixel* pixel);
};

#endif
