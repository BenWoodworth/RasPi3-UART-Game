#ifndef UART_H_
#define UART_H_

#include <stddef.h>

#include "gpio.h"

/// UART0's base address is 0x1000 away from the base
/// address of the GPIO base address.
#define UART0_BASE_ADDR (RPI_PERI_BASE_ADDR + 0x1000)

static volatile uint32_t *uart = (uint32_t*)UART0_BASE_ADDR;

// Register offsets.  These values are set to the offset from
// UART0_BASE_ADDR.
// To access these registers, use uart[REGISTER_NAME]

// Offsets taken from https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf page 178.

// Data Register (base + 0x00).
// Used to read and write data.
// Data written to this register is pushed out the UART.
// | 31-12 ignored |
// | 11 Overrun error if set to 1.  Cleared to 0 when there is space in the FIFO for a new character to be written to |
// | 10 Break error if set to 1 |
// | 9 Parity error when set to 1 |
// | 8 Frame error when set to 1 |
// | 7-0 Transmit data to UART when written to, else read data from UART when read | 
#define UART0_DR 0

// Flag Register (base + 0x18).
// | 31-8 Ignored |
// | 7 Transmit FIFO is empty when set. |
// | 6 Receive FIFO is full when set. |
// | 5 Transmit FIFO is full when set. Probably shouldn't Tx when this is set... |
// | 4 Receive FIFO is empty when set.  Probably shouln't try to read from UART when this is set... |
// | 3 UART is busy when set.  Should't send or receive while set. |
// | 2-1 Ignored |
// | Clear TO Send.  Only used when CTS is enabled. |
#define UART0_FR 6

// Baud-rate integer divisor (base + 0x24).
// Must NOT be changed when uart is enabled.
// | 31-16 Ignored |
// | 15-0 Integer part of the baud-rate divisor. |
#define UART0_IBRD 9

// Fractional Baud Rate Divisor (base + 0x28).
// Must NOT be changed when uart is enabled.
// | 31-6 Ignored |
// | 5-0 Fractional Baud Rate divisor |
#define UART0_FBRD 10

// Line Control Register (base + 0x2c).
// Must NOT be changed when uart is enabled.
// | 31-8 Ignored |
// | 7 Stick Partiy Select.  1 to enable stick parity, 0 to not |
// | 6-5 Word Length.  Number of data bits transmitted or received in a frame.  11, 10, 01, 00 is 8, 7, 6, 5 bits respectfully |
// | 4 Enable FIFOS. Set to 0 to have FIFOs be only 1 byte, set to 1 to have an actual queue. |
// | 3 Stop Bit Select.  Set to 1 to have 2 stop bits, else just 1. |
// | 2 Even Parity Select.  Set to 0 for odd parity, 1 for even |
// | 1 Parity Enable.  Set to 0 for no parity, 1 to enable parity |
// | 0 Send Break.  Set to 1 to send a break. |
#define UART0_LCRH 11

// Control Register (base + 0x30).
// | 31-16 Ignored |
// | 15 CTS control enable.  If set to 1, data is only set when CTS is enabled |
// | 14 RTSEN control enable.  If set to 1, data is only requested when there is space in the receive FIFO. |
// | 13-12 Ignored |
// | 11 Request to send (RTS). |
// | 10 Ignored |
// | 9 RXE Receive enable.  Set to 1 to enable receiving data |
// | 8 TXE Transmit enable.  Set to 1 to enable transmitting data |
// | 7 Loopback Enable |
// | 6-1 Ignored |
// | 0 UART enable.  0 to disable, 1 for enable. |
#define UART0_CR 12

// Interupt FIFO Level Select Register (base + 0x34).
#define UART0_IFLS 13

// Interupt Mask Set Clear Register (base + 0x38).
#define UART0_IMSC 14

// Raw Interup Status Register (Base + 0x3c).
#define UART0_RIS 15

// Masked Interupt Status Register (Base + 0x40).
#define UART0_MIS 16

// Masked Interupt Status Register.
#define UART0_ICR 17

/// Initalizes the uart port.
/// Puts GPIO pins XX and YY to alternative selection 5.
extern void init_uart();

/// Gets a single character from the UART port.
extern char get_char();

/// Writes a single character to the uart port.
extern void put_char(char c);

/// Reads the string from uart.  It reads until either
/// buffer_size - 1 characters were read from the buffer (null character is then added to end of buffer).
/// OR a new line is received.
/// Returns the number of characters read from the buffer.
extern size_t get_string(char* buffer, size_t buffer_size);

/// Sends an entire null-terminated string
/// to the UART port.  The function will keep sending characters
/// until it reaches a null-character and then it stops.
extern void put_string(const char* str);

extern void delay(volatile uint32_t count);

#endif // UART_H_
