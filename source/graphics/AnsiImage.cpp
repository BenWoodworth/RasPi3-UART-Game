#include "graphics/AnsiImage.h"
#include "terminal/Terminal.h"

void AnsiImage::drawToTerminal(Terminal* terminal) {
    uint32_t lastFg = 1 << 24;
    uint32_t lastBg = lastFg;

    for (uint32_t x = 0; x < this->width; x++) {
        for (uint32_t y = 0; y < this->height; y++) {
            AnsiPixel pixel = this->getPixel(x, y);

            // Set the background color if it changed
            uint32_t curFg =
                (pixel.fgColorR << 16) |
                (pixel.fgColorG << 8) |
                (pixel.fgColorB);

            if (lastFg != curFg) {
                lastFg = curFg;

                terminal->setForegroundColor(
                    pixel.fgColorR, pixel.fgColorG, pixel.fgColorB
                );
            }

            // Set the foreground color if it changed
            uint32_t curBg =
                (pixel.bgColorR << 16) |
                (pixel.bgColorG << 8) |
                (pixel.bgColorB);

            if (lastBg != curBg) {
                lastFg = curBg;

                terminal->setBackgroundColor(
                    pixel.bgColorR, pixel.bgColorG, pixel.bgColorB
                );
            }

            // Write the character
            terminal->printChar(pixel.character);
        }

        // Put the cursor on the next line
        terminal->moveCursorToLineStart(1);
    }
}
