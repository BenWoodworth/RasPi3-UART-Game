#include <stdint.h>

// Converts the given number to the given buffer
// in the form of a binary string.
// Buffer must be at least 33 characters long, otherwise
// bad things WILL happen.
// Returns the pointer to the buffer.
char* to_binary_str(uint32_t numToConvert, char* buffer);

// Converts the given number to the given buffer
// in the form of a hex string.
// Buffer must be at least 5 characters long, otherwise
// bad things WILL happen.
// Returns the pointer to the given buffer.
char* to_hex_str(uint32_t numToConvert, char* buffer);

// Converts the given string to the given buffer
// in the form of a hex string.
// Buffer must be at least 6 characters, or bad things
// WILL happen.
// Returns the pointer to the given buffer.
char* to_decimal_str(uint32_t numToConvert, char* buffer);