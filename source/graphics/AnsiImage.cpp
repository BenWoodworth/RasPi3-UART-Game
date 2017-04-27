#include "graphics/AnsiImage.h"
#include "graphics/Colors.h"
#include "terminal/Terminal.h"

void AnsiImage::writeToTerminal(Terminal* terminal) {
    for (int32_t y = 0; y < this->height; y++) {
        for (int32_t x = 0; x < this->width; x++) {
            AnsiPixel* pixel = this->getPixel(x, y);

            // Skip pixel if it's null
            if (pixel == NULL) {
                terminal->moveCursor(0, 1);
                continue;
            }

            // TODO Optimization: Don't set same color twice in a row
            // Set foreground and background colors
            terminal->setColor(pixel->getForeground(), true);
            terminal->setColor(pixel->getBackground(), false);

            // Write the character
            terminal->printChar(pixel->getCharacter());
        }

        // Put the cursor on the next line
        terminal->resetStyling();
        terminal->newLine();
    }
}

AnsiImage* AnsiImage::getSubImage(int32_t x, int32_t y, int32_t width, int32_t height) {
    AnsiImage* result = new AnsiImage(width, height);
    for (int32_t toX = 0; toX < width; toX++) {
        for (int32_t toY = 0; toY < height; toY++) {
            result->setPixel(toX, toY, this->getPixel(x + toX, y + toY));
        }
    }
    return result;
}

void AnsiImage::drawImage(int32_t x, int32_t y, AnsiImage* image) {
    for (int32_t fromX = 0; fromX < image->width; fromX++) {
        for (int32_t fromY = 0; fromY < image->height; fromY++) {
            int32_t toX = x + fromX;
            int32_t toY = y + fromY;

            // If out of bounds of this image...
            if (toX < 0 || toX >= this->width || toY < 0 || toY >= this->height) {
                continue; // ...then don't copy this pixel
            }

            AnsiPixel* fromPixel = image->getPixel(fromX, fromY);
            if (fromPixel != NULL) {
                this->setPixel(toX, toY, fromPixel);
            }
        }
    }
}

void AnsiImage::drawRect(int32_t x, int32_t y, int32_t width,
                         int32_t height, AnsiPixel* pixel) {
    for (int32_t drawX = x; drawX < x + width; drawX++) {
        for (int32_t drawY = y; drawY < y + height; drawY++) {
            this->setPixel(drawX, drawY, pixel);
        }
    }
}
