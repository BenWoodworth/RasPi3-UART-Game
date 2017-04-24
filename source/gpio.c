#include "gpio.h"

// -------- Functions --------

// Mapping between the pin number (index)
// to the corresponding GPIO number (return value).
int8_t pin_to_gpio_array[40] =
{
    -1, -1, // 1 2
    2, -1,  // 3 4
    3, -1,  // 5 6
    4, 14,  // 7 8
    -1, 15, // 9 10
    17, 18, // 11 12
    27, -1, // 13 14
    22, 23, // 15 16
    -1, 24, // 17 18
    10, -1, // 19 20
    9, 25,  // 21 22
    11, 8,  // 23 24
    -1, 7,  // 25 26
    -1, -1, // 27 28
    5, -1,  // 29 30
    6, 12,  // 31 32
    13, -1, // 33 34
    19, 16, // 35 36
    26, 20, // 37 38
    -1, 21  // 39 40
};

// Mapping between the GPIO number (index)
// to the corresponding pin number (return value).
int8_t gpio_to_pin_array[28] =
{
    -1, // GPIO0
    -1, // GPIO1
    3,  // GPIO2
    5,  // GPIO3
    7,  // GPIO4
    29, // GPIO5
    31, // GPIO6
    26, // GPIO7
    24, // GPIO8
    21, // GPIO9
    19, // GPIO10
    23, // GPIO11
    32, // GPIO12
    33, // GPIO13
    8,  // GPIO14
    10, // GPIO15
    36, // GPIO16
    11, // GPIO17
    12, // GPIO18
    35, // GPIO19
    38, // GPIO20
    40, // GPIO21
    15, // GPIO22
    16, // GPIO23
    18, // GPIO24
    22, // GPIO25
    37, // GPIO26
    13  // GPIO27
};

/// Converts the given pin number to the GPIO number
/// on the PI.  Returns -1 if the pin number is not a valid number.
int8_t convert_pin_to_gpio(int8_t pinNumber)
{
    if ((pinNumber < 0) || (pinNumber > 40))
    {
        return -1;
    }
    
    return pin_to_gpio_array[pinNumber];
}

/// Converts the given GPIO number to a pin number.
/// Returns -1 if the pin number is not a valid number.
int8_t convert_gpio_to_pin(int8_t gpioNumber)
{
    if ((gpioNumber < 0) || (gpioNumber > 28))
    {
        return -1;
    }
    
    return gpio_to_pin_array[gpioNumber];
}

// write to MMIO register  This function is used by the RPI.  Note
// ANY OTHER GNU compiler will also include this function.  You will
// need to comment this code out for non-RPI GNU compilers 
void mmio_write(uint32_t *reg, uint32_t data)
{
    reg[0] = data;
}