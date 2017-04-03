#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

// ----------------Constants ----------------

// ---- Register addresses ----

// All of these appear on page 247 of
// "Exploring Raspberry Pi" book by Derek Molloy.

// Address for the peripherals.
// On the Pi 1 and earlier, this is 0x20200000, however,
// on the Pi 2, its 0x3F200000
// Pi 3, meanwhile, is also 0x3F200000
//
// OK_LED_SELECT_FUNC is what we need to set the OK LED's
//                    select register to.
// OK_LED_SELECT_REG is the select register for the OK LED.
// OK_LED_SET_REG is the set register to use when setting the 
//                OK LED
// OK_LED_CLR_REG is the clear register to use when clearing the
//                OK LED.
// OK_LED_SET_MASK is the mask to set the SET/CLEAR registers
//                 to to set or clear the OK LED.
#ifdef PI2
    #define RPI_PERI_BASE_ADDR 0x3F200000UL
    #define OK_LED_SELECT_FUNC 0x00200000
    #define OK_LED_SELECT_REG GPFSEL4
    #define OK_LED_SET_REG GPSET1
    #define OK_LED_CLR_REG GPCLR1
    #define OK_LED_SET_MASK (1 << 15) // Pi 2 and newer, this is GPI 47.
#else
    #define RPI_PERI_BASE_ADDR 0x20200000UL
    #define OK_LED_SELECT_FUNC 0x00040000
    #define OK_LED_SELECT_REG GPFSEL1
    #define OK_LED_SET_REG GPSET0
    #define OK_LED_CLR_REG GPCLR0
    #define OK_LED_SET_MASK (1 << 16)
#endif

static volatile uintptr_t *gpio = (uintptr_t*) RPI_PERI_BASE_ADDR;

// The BCM2835 has 54 GPIO pins.
// These are the function addresses for the GPIO.
// These are offset from the peripherial base address.
// Each of these are 32-bit registers that control the function of a GPIO.
// There are 6 control registers, each control the functions of a block
// of 10 pins.
// Each control register has 10 sets of 3 bits per GPIO pin - the ALT values
//
// 000 = GPIO Pin X is an input
// 001 = GPIO Pin X is an output
// 100 = GPIO Pin X takes alternate function 0
// 101 = GPIO Pin X takes alternate function 1
// 110 = GPIO Pin X takes alternate function 2
// 111 = GPIO Pin X takes alternate function 3
// 011 = GPIO Pin X takes alternate function 4
// 010 = GPIO Pin X takes alternate function 5
//
// See table on page 236 to see what each "alternate function" is for each pin.

// | Register Name  | 31-30 | 29-27  | 26-24  | 23-21  | 20-18  | 17-15  | 14-12  | 11-9   | 8-6   | 5-3   | 2-0   |
// | GPFSEL0        | XXXXX | FSEL9  | FSEL8  | FSEL7  | FSEL6  | FSEL5  | FSEL4  | FSEL3  | FSEL2 | FSEL1 | FSEL0 |
// | GPFSEL1        | XXXXX | FSEL19 | FSEL18 | FSEL17 | FSEL16 | FSEL15 | FSEL14 | FSEL13 | FSEL12| FSEL11| FSEL10|
// | GPFSEL2        | XXXXX | FSEL29 | FSEL28 | FSEL27 | FSEL26 | FSEL25 | FSEL24 | FSEL23 | FSEL22| FSEL21| FSEL20|
// | GPFSEL3        | XXXXX | FSEL39 | FSEL38 | FSEL37 | FSEL36 | FSEL35 | FSEL34 | FSEL33 | FSEL32| FSEL31| FSEL30|
// | GPFSEL4        | XXXXX | FSEL49 | FSEL48 | FSEL47 | FSEL46 | FSEL45 | FSEL44 | FSEL43 | FSEL42| FSEL41| FSEL40|
// | GPFSEL5        | XXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | FSEL53 | FSEL52| FSEL51| FSEL50|
//
// Register offsets.  These values are set to the offset from RPI_PERI_BASE_ADDR.
// To gain access to these registers, use gpio[REGSISTER_NAME].
#define GPFSEL0 0
#define GPFSEL1 1
#define GPFSEL2 2
#define GPFSEL3 3
#define GPFSEL4 4
#define GPFSEL5 5

// These set of registers in the PI are the output registers for setting the GPIOS to HIGH.
// | Register Name | Bit Mapping                                                                                           |
// | GPSET0        | 31-0 mapps to GPIO31 to GPIO0.  Set the bit to 1 to turn the GPIO HIGH.  Setting to 0 has no effect.  |
// | GPSET1        | 31-22 is don't care. 21-0 are mapped to GPIO53 to GPIO32.  Set bit to 1 to turn HIGH, 0 has no effect |
//
// Register Addresses:
#define GPSET0 7
#define GPSET1 8

// These set of registers in the PI are the output registers for setting the GPIOs to LOW.
// | Register Name | Bit Mapping                                                                                           |
// | GPCLR0        | 31-0 mapps to GPIO31 to GPIO0. Set the bit to 1 to turn the GPIO LOW.  Setting to 0 has no effect.    |
// | GPCLR1        | 31-22 is don't care. 21-0 are mapped to GPIO53 to GPIO32. Set bit to 1 to turn LOW, 0 has no effect.  |
//
// Register Addresses:
#define GPCLR0 10
#define GPCLR1 11

// These set of registers in the PI are for reading from the GPIO.  These are read-only.
// | Register Name | Bit Mapping                                                                                  |
// | GPLVL0        | 31-0 maps to GPIO31 to GPIO0. A bit set to 1 is high, 0 is low.                              |
// | GPLVL1        | 31-22 is don't care. 21-0 are mapped to GPIO53 to GPIO32. A bit set to 1 is high, 0 is low.  |
//
// Register Addresses:
#define GPLVL0 13
#define GPLVL1 14

// These set of registers in the PI are for setting pull up and pull down operation.
// | Register Name | Bit Mapping                                                                                  |
// | GPPUD         | 31-2 are not used.  1-0 are used to set the pull-up/pull-down function (see below)           |
// 00 - no pull-up/pull-down
// 01 - pull-down
// 10 - pull-up
// 11 - Not Used.
#define GPPUD 37

// These set of registers applies the pull-up/pull-down setting in GPPUD to a specific set of
// GPIO.
// | Register Name | Bit Mapping                                                                                                       |
// | GPPUDCLK0     | 31-0 mapps to GPIO31 to GPIO0. Set the bit to 1 to asset the clock.    Setting to 0 has no effect.                |
// | GPPUDCLK1     | 31-22 is don't care. 21-0 are mapped to GPIO53 to GPIO32.  Set the bit to 1 to asset the clock, 0 has no effect.  |
//
// Register Addresses:
#define GPPUDCLK0 38
#define GPPUDCLK1 39

// --------- Functions --------

// ---- Pin-to-GPIO conversion ----
// Found from pg 236 in Molloy.
// | Pin Function | Pin Number | Pin Number | Pin Function |
// | 3.3V         | 1          | 2          | 5V           |
// | GPIO2        | 3          | 4          | 5V           |
// | GPIO3        | 5          | 6          | GND          |
// | GPIO4        | 7          | 8          | GPIO14       |
// | GND          | 9          | 10         | GPIO15       |
// | GPIO17       | 11         | 12         | GPIO18       |
// | GPIO27       | 13         | 14         | GND          |
// | GPIO22       | 15         | 16         | GPIO23       |
// | 3.3V         | 17         | 18         | GPIO24       |
// | GPIO10       | 19         | 20         | GND          |
// | GPIO9        | 21         | 22         | GPIO25       |
// | GPIO11       | 23         | 24         | GPIO8        |
// | GND          | 25         | 26         | GPIO7        |
// | ID_SD        | 27         | 28         | ID_SC        | // Don't use either of these in this row!
// | GPIO5        | 29         | 30         | GND          |
// | GPIO6        | 31         | 32         | GPIO12       |
// | GPIO13       | 33         | 34         | GND          |
// | GPIO19       | 35         | 36         | GPIO16       |
// | GPIO26       | 37         | 38         | GPIO20       |
// | GND          | 39         | 40         | GPIO21       |       

/// Converts the given pin number to the GPIO number
/// on the PI.  Returns -1 if the pin number is not a valid number.
extern int8_t convert_pin_to_gpio(int8_t pinNumber);

/// Converts the given GPIO number to a pin number.
/// Returns -1 if the pin number is not a valid number.
extern int8_t convert_gpio_to_pin(int8_t gpioNumber);

// write to MMIO register  This function is used by the RPI.  Note
// ANY OTHER GNU compiler will also include this function.  You will
// need to comment this code out for non-RPI GNU compilers 
extern void mmio_write(uint32_t* reg, uint32_t data);

#endif // GPIO_H_