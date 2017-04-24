#include "graphics/AnsiImageBuilder.h"

AnsiImage* AnsiImageBuilder::build() {
    AnsiImage* result = new AnsiImage(this->width, this->height);

    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            AnsiPixel* pixel = this->pixels[x + y * this->width];
            result->setPixel(x, y, pixel);
        }
    }

    return result;
}

AnsiImageBuilder* AnsiImageBuilder::map(char ch, char pixelCh uint32_t pixelFg, uint32_t pixelBg) {
    AnsiPixel* pixel = &AnsiPixel{
        pixelCh,
        pixelFg,
        pixelBg
    };

    // Update appropriate pixels.
    for (int i = 0; i < this->width * this->height; i++) {
        if (this->layout[i] == ch) {
            this->pixels[i] = pixel;
        }
    }

    return this;
}
