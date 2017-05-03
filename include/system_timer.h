#ifndef SYSTEM_TIMER_H_
#define SYSTEM_TIMER_H_

#include <stdint.h>

#ifdef PI2
    #define SYSTEM_TIMER_ADDR 0x3F003000UL
#else
    #define SYSTEM_TIMER_ADDR 0x20003000UL
#endif

static volatile uintptr_t *sys_timer = (uintptr_t*) SYSTEM_TIMER_ADDR;

// From BCM2865 Section 12 (pg 172) on system timers:
// The system timer provides 32 timer channels and a 
// single 64-bit free running counter.  Each channel
// has an output compare register which is compared
// against the 32 least significant bits of the 
// free running counter values.
// When 2 values match, the system timer generates
// a signal to indicate a match for the appropriate channel,
// which is fed into the interrupt controller.
// The ISR reads the output compare register
// and adds the appropriate offset for the next timer tick.

// -------- Registers --------

// System Timer Control/Status.
// | 31:4 | Unused |
// | 3    | M3, 1 is timer 3 match detected, 0 is none since last cleared |
// | 2    | M2, 1 is timer 2 match detected, 0 is none since last cleared |
// | 1    | M1, 1 is timer 2 match detected, 0 is none since last cleared |
// | 0    | M0, 1 is timer 2 match detected, 0 is none since last cleared |
// Write a 1 to any of the MX bits to clear the corresponding interrupt request line.
// Offset: 0x00.
#define SYS_TIMER_CS 0

// System Timer Counter, Lower 32 bits.
// Offset: 0x04
#define SYS_TIMER_CLO 1

// System Timer Counter, Upper 32 bits.
// Offset 0x08.
#define SYS_TIMER_CHI 2

// For all compare registers,
// whenever the lower 32-bits of the free-running counter
// matches one of the compare values the corresponding
// bit in the system timer control/status (CS) register
// is set.

// System Timer compare 0.
// Offset 0x0C.
#define SYS_TIMER_C0 3

// System Timer compare 1.
// Offset 0x10.
#define SYS_TIMER_C1 4

// System Timer compare 2.
// Offset 0x14.
#define SYS_TIMER_C2 5

// System Timer compare 3.
// Offset 0x18.
#define SYS_TIMER_C3 6

/// Delays the calling thread by the given
/// number of micro seconds.
void timer_delay_us(uint32_t delayUs);

/// Delays the calling thread by the given
/// number of milliseconds.
void timer_delay_ms(uint32_t delayMs);

/// Delays the calling thread by the given
/// number of seconds.
void timer_delay_sec(uint32_t delaySec);

#endif // SYSTEM_TIMER_H_