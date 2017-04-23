#include "graphics/AnsiImage.h"
#include "terminal/Terminal.h"

void AnsiImage::drawToTerminal(Terminal* terminal) {
    uint32_t lastFg = -1;
    uint32_t lastBg = -1;

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            AnsiPixel* pixel = this->getPixel(x, y);

            // Skip pixel if it's null
            if (pixel == NULL) {
                terminal->moveCursor(0, 1);
                continue;
            }

            // Set the foreground color if it changed
            if (lastFg != pixel->foreground) {
                lastFg = pixel->foreground;
                terminal->setColor(pixel->foreground, true);
            }

            // Set the background color if it changed
            if (lastBg != pixel->background) {
                lastBg = pixel->background;
                terminal->setColor(pixel->background, false);
            }

            // Write the character
            terminal->printChar(pixel->character);
        }

        // Put the cursor on the next line
        // terminal->moveCursorToLineStart(1); // TODO
        terminal->printStr("\r\n");
    }
}
