#ifndef ANSIIMAGEBUILDER_H_
#define ANSIIMAGEBUILDER_H_

#include "core/graphics/AnsiImage.h"
#include "core/graphics/AnsiPixel.h"

class AnsiImageBuilder {
private:
    int32_t width, height;
    std::string layout;

    AnsiPixel** pixels;

public:
    /// Construct an ANSI image builder.
    /// Width and height are the resulting image dimensions.
    /// Layout is a string of characters that will be mapped to pixels.
    AnsiImageBuilder(int32_t width, int32_t height, std::string layout) {
        this->width = width;
        this->height = height;
        this->layout = layout;

        // Initialize pixels with NULL pointers
        pixels = new AnsiPixel*[width * height];
        for (int i = 0; i < width * height; i++) {
            pixels[i] = NULL;
        }
    }

    /// Build the ANSI image.
    AnsiImage* build();

    /// Map a character in the layout to a pixel.
    /// Ch is the character to map.
    /// Pixel* parameters are the pixel data.
    /// Returns this builder, for chaining.
    AnsiImageBuilder* mapChar(char ch, AnsiPixel* pixel);
};

#endif
