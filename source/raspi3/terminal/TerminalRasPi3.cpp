#include <string>
#include <stdint.h>
#include "terminal/TerminalRasPi3.h"

void TerminalRasPi3::printChar(uint8_t ch) {
    // Wait until not full
    while (((volatile uint32_t)uart[UART0_FR]) & TX_FIFO_FULL);

    // Send character
    uart[UART0_DR] = ch;
}

void TerminalRasPi3::printStr(std::string str) {
    for (int i = 0; str[i]; i++) {
        printChar(str[i]);
    }
}

void TerminalRasPi3::printNumDec(int32_t num) {
    std::to_string(num);
}

uint8_t TerminalRasPi3::getChar() {
    // Wait for a character
    while (!hasChar());

    // Get the character
    return (uint8_t)(uart[UART0_DR] & 0xFF);
}

bool TerminalRasPi3::hasChar() {
    return !(((volatile uint32_t) uart[UART0_FR]) & RX_FIFO_EMPTY);
}
