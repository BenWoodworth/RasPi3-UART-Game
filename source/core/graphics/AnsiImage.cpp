#include "graphics/AnsiImage.h"
#include "graphics/Colors.h"
#include "terminal/Terminal.h"

AnsiPixel* AnsiImage::getPixel(int32_t x, int32_t y) {
    if (this->isInBounds(x, y)) {
        return this->pixels[x + y * width];
    }
    return NULL;
}

void AnsiImage::setPixel(int32_t x, int32_t y, AnsiPixel* ansiPixel) {
    if (this->isInBounds(x, y)) {
        this->pixels[x + y * width] = ansiPixel;
    }
}

void AnsiImage::writeToTerminal(Terminal* terminal) {
    uint8_t lastFgColor = 0;
    uint8_t lastBgColor = 0;

    for (int32_t y = 0; y < this->height; y++) {
        for (int32_t x = 0; x < this->width; x++) {
            AnsiPixel* pixel = this->getPixel(x, y);

            // Skip pixel if it's null
            if (pixel == NULL) {
                terminal->moveCursor(0, 1);
                continue;
            }

            if (x == 0 || pixel->getForeground() != lastFgColor) {
                terminal->setColor(pixel->getForeground(), true);
                lastFgColor = pixel->getForeground();
            }
            if (x == 0 || pixel->getBackground() != lastBgColor) {
                terminal->setColor(pixel->getBackground(), false);
                lastBgColor = pixel->getBackground();
            }

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

void AnsiImage::drawString(int32_t x, int32_t y, std::string word, uint8_t colorBack, uint8_t colorFore){
    int32_t index = 0;
    for(auto c : word){
        setPixel(x+index++,y,new AnsiPixel(colorBack, colorFore, c));
    }
}
