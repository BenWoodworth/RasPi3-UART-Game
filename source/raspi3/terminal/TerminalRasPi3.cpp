#include <string>
#include <stdint.h>

#include "raspi3/terminal/TerminalRasPi3.h"

void TerminalRasPi3::printChar(uint8_t ch) {
    // Wait until not full
    while (((volatile uint32_t)uart[UART0_FR]) & TX_FIFO_FULL);

    // Wait (TODO Necessary?)
    delay(150);

    // Send character
    uart[UART0_DR] = ch;
}

void TerminalRasPi3::printStr(std::string str) {
    for (int i = 0; str[i]; i++) {
        printChar(str[i]);
    }
}

void TerminalRasPi3::printNumDec(int32_t num) {
    printStr(std::to_string(num));
}

uint8_t TerminalRasPi3::getChar() {
    // Wait for a character
    while (!hasChar());

    // Wait (TODO Necessary?)
    delay(150);

    // Get the character
    return (uint8_t)(uart[UART0_DR] & 0xFF);
}

bool TerminalRasPi3::hasChar() {
    return !(((volatile uint32_t) uart[UART0_FR]) & RX_FIFO_EMPTY);
}

void TerminalRasPi3::initUart() {
    // First things first, we need to set the UART pins to use
    // alternate function 0.  Page 236 of the shows
    // that GPIO 14 is TXD, GPIO 15 is RXD, and they must be set
    // to use alternate function 0 in select register 1.
    // The bits must be set to 100 for GPIO 15 and 14.
    gpio[GPFSEL1] |= 0x24000;

    // According to the BCM2835 manual page 185, we
    // need to do the following to enable UART.
    // 1. Disable the UART.
    // 2. Wait for end-of-transmisstion or reception
    //    of the current character.
    // 3. Flush the transmit queue by setting the FEN
    //    bit to 0 in the line control register (UART_LCRH).
    //    This is bit 4, the enable FIFOs bit.
    // 4. Set the Baud Rate
    // 5. Reprogram the control register, UART_CR
    // 6. Enable the UART.

    // 1. Disable the UART.  Easiest way to do that is
    // to zeroize the control register.
    uart[UART0_CR] = 0;

    // 2. Wait for end-of-transmission
    //spin while UART is busy transmitting
    while (((volatile uint32_t)uart[UART0_FR]) & UART_BUSY_TX);

    // 3. Set FEN bit to 0 of UART-LCRH, which flushes the Tx Queue.
    uart[UART0_LCRH] |= (0 << 4);

    gpio[GPPUD] = 0;
    delay(150);
    gpio[GPPUDCLK0] = (1<<14)|(1<<15);
    delay(150);
    gpio[GPPUDCLK0] = 0; // Writing zero apparently makes it take affect.

    // Clear Pending Interrupts
    uart[UART0_ICR] = 0x7FF;

    // 4. Set the baud rate.  The baud rate is set by:
    // BAUDDIV = FUARTCLK / (16 * BaudRate) where FUARTCLR is
    // the UART reference clock fequency.  BAUDDIV goes into the
    // UART0_IBRD register (the whole number part anyway).
    // The remainder of BAUDDIV is used to calculate what goes in
    // FBRD.
    // FBRD = (BAUDDIV_Remainder * 64) + 0.5
    //
    // According to documentation, the UART clock is 48MHz.
    // for a baud rate of 115200, we use the following formula:
    // 48000000 / (16 * 115200), which is 26.0416, or about 26.
    // The fractional part of the register is 0.0138
    // So FBRD = 0.0416 * 64 + 0.5 which is 1.3312, or ~1.
    uart[UART0_IBRD] = 26;
    uart[UART0_FBRD] = 1;
    // For 9600 baud - stability check
    //uart[UART0_IBRD] = 312;
    //uart[UART0_FBRD] = 32;

    //Enable FIFO and set word length 
    uart[UART0_LCRH] |= (1<<4) | (1<<5) | (1<<6);

    // Mask all interrupts
    uart[UART0_IMSC] |= (
        (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
        (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10)
    );

    // 5.  Reprogram the UART control register.

    // Enable Receive, Enable Tx, Enable UART.
    uart[UART0_CR] |= ((1 << 9) | (1 << 8) | (1 << 0));
}
