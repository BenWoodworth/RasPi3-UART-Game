#include <stddef.h>

#include "gpio.h"
#include "uart.h"

// UART BUSY TRANSMITTING
#define UART_BUSY_TX (1 << 3)

//Rx FIFO empty
#define RX_FIFO_EMPTY (1 << 4)

// Tx FIFO full
#define TX_FIFO_FULL (1 << 5)

// Rx FIFO full
#define RX_FIFO_FULL (1 << 6)

// Tx FIFO empty
#define TX_FIFO_EMPTY (1<< 7)

// Wait for space in the Tx FIFO
void wait_for_tx_slot()
{
    // Spin while Tx FIFO is full
    while (((volatile uint32_t)uart[UART0_FR]) & TX_FIFO_FULL){}
}

// Waits until the UART is not busy
void wait_for_uart_idle()
{
    //spin while UART is busy transmitting
    while (((volatile uint32_t)uart[UART0_FR]) & UART_BUSY_TX){}
}

// Waits for space in the Rx FIFO 
void wait_for_rx_slot()
{
    // Spin while the Rx FIFO is full
    while (((volatile uint32_t)uart[UART0_FR]) & RX_FIFO_FULL){}
}

// Wait for Rx FIFO to receive something
void wait_for_rx_has_char()
{
    // Spin while the Rx FIFO is empty
    while (((volatile uint32_t)uart[UART0_FR]) & RX_FIFO_EMPTY){}
}

void delay(volatile uint32_t count)
{
    while (count)
    {
        count--;
    }
}

// Initalizes the uart port.
// Puts GPIO pins XX and YY to alternative selection 5.
void init_uart()
{
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
    wait_for_uart_idle();

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

/// Gets a single character from the UART port.
extern char get_char()
{
    wait_for_rx_has_char();
    delay(150);
#ifdef DBG
    // debug - print off 4 status bits instead
    // read status, shift to LSB, mask it off
    // output will be a char - need to convert  
    uint32_t ch = uart[UART0_DR];
    ch = (ch >> 8) & 0xF;
    return (char) (ch + '0');
#else
    // Only care about the last 8 bits.
    //char ch = (char)uart[UART0_DR];
    //uart[UART0_IMSC] &= ~(1<<4);
    return (char)(uart[UART0_DR] & 0xFF);
#endif 
}

/// Writes a single character to the uart port.
extern void put_char(char c)
{
    wait_for_tx_slot();
    delay(150);
    uart[UART0_DR] = c;
}

/// Reads the string from uart.  It reads until either
/// buffer_size - 1 characters were read from the buffer (null character is then added to end of buffer).
/// OR a new line is received.  New line characters are not added to the buffer.
/// Returns the number of characters read from the buffer.
extern size_t get_string(char* buffer, size_t buffer_size)
{
    size_t count = 0;
    for (
        char ch = '\0';
        (count < (buffer_size - 1)) && (ch != '\n') && (ch != '\r');
    )
    {
        ch = get_char();

        if ((ch != '\n') && (ch != '\r'))
        {
            put_char(ch); // Echo back.
            buffer[count++] = ch;
        }
        // OS dependent.  May get \r, may get \n.  Either way, we'll
        // want to break out of the loop, and echo back new line (\r\n).
        else if (ch == '\r')
        {
            put_string("\r\n");
        }
        else if (ch == '\n')
        {
            put_string("\r\n");
        }
    }

    buffer[count] = '\0';
    return count;
}

/// Sends an entire null-terminated string
/// to the UART port.  The function will keep sending characters
/// until it reaches a null-character and then it stops.
extern void put_string(const char* str)
{
    char currentChar = str[0];
    for (size_t i = 0; currentChar != '\0'; ++i)
    {
        currentChar = str[i];

        // Depending on which console is being used, this may
        // or may not be needed.  On linux, we've discovered we can't
        // send null characters or the formatting is all wrong.
        if(currentChar!= '\0')
        {
            put_char(currentChar);
        }
    }
    wait_for_uart_idle();
}