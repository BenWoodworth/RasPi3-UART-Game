#ifndef TERMINALRASPI3_H_
#define TERMINALRASPI3_H_

#include <stdint.h>
#include "terminal/Terminal.h"

class TerminalRasPi3 : public Terminal {
private:
    uint64_t RPI_PERI_BASE_ADDR = 0x3F200000UL; // TODO Correct?

    uint8_t UART0_DR = 0;
    uint8_t UART0_FR = 6;
    uint8_t RX_FIFO_EMPTY = 1 << 4;
    uint8_t TX_FIFO_FULL = 1 << 5;

    volatile uint32_t *uart = (uint32_t*)(RPI_PERI_BASE_ADDR + 0x1000);
public:
    void printChar(uint8_t ch);

    void printStr(std::string str);

    void printNumDec(int32_t num);

    uint8_t getChar();

    bool hasChar();
};

#endif
