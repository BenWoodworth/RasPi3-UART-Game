#ifndef TERMINALRASPI3_H_
#define TERMINALRASPI3_H_

#include <stdint.h>

#include "core/terminal/Terminal.h"

class TerminalRasPi3 : public Terminal {
private:
    uint64_t RPI_PERI_BASE_ADDR = 0x3F200000UL; // TODO Correct?
    uint8_t GPFSEL1 = 1;
    uint8_t GPPUD = 37;
    uint8_t GPPUDCLK0 = 38;

    uint8_t UART0_DR = 0;
    uint8_t UART0_FR = 6;
    uint8_t UART0_IBRD = 9;
    uint8_t UART0_FBRD = 10;
    uint8_t UART0_LCRH = 11;
    uint8_t UART0_CR = 12;
    uint8_t UART0_IMSC = 14;
    uint8_t UART0_ICR = 17;
    
    uint8_t UART_BUSY_TX = 1 << 3;
    uint8_t RX_FIFO_EMPTY = 1 << 4;
    uint8_t TX_FIFO_FULL = 1 << 5;

    volatile uintptr_t *gpio = (uintptr_t*) RPI_PERI_BASE_ADDR;
    volatile uint32_t *uart = (uint32_t*)(RPI_PERI_BASE_ADDR + 0x1000);

    inline void delay(volatile uint32_t cycles) {
        while (cycles--);
    }

    void initUart();
public:
    TerminalRasPi3() {
        initUart();
    }

    void printChar(uint8_t ch);

    void printStr(std::string str);

    void printNumDec(int32_t num);

    uint8_t getChar();

    bool hasChar();
};

#endif
