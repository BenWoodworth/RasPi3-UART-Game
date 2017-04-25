#include "graphics/AnsiImage.h"
#include "graphics/Colors.h"
#include "terminal/Terminal.h"

void AnsiImage::drawToTerminal(Terminal* terminal) {
    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
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
