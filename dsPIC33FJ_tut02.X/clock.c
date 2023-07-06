// file clock.c - switch from FRC 7.37 MHz to FRC+PLL at 79.12 MHz

#include <xc.h>
// intentionally include clock.h to detect prototype mismatch
#include "clock.h"

// switch clock from FRC 7.37 MHz to FRC+PLL at 79.12 MHz
void CLOCK_Initialize(void)
{
        // Now switch from FRC f = 7.37Mhz to 80MHz (40MIPS) using PLL
    // From DS70596A-page 48-27, Example 48-2
    //      of http://ww1.microchip.com/downloads/en/DeviceDoc/DS-70596A.pdf
    // Configure PLL prescaler, PLL postscaler, and PLL divisor
    PLLFBD = 41; // M = 43
    CLKDIVbits.PLLPRE=0; // N1 = 2
    CLKDIVbits.PLLPOST=0; // N2 = 2
    // f_osc = f_in * M / N1 / N2 = 7.36 * 43 / 2 /2 = 79.12
    // Initiate clock switch to internal FRC with PLL (NOSC = 0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);
    // Wait for clock switch to occur
    while (OSCCONbits.COSC != 0b001){/*nop*/};
    // Wait for PLL to lock
    while(OSCCONbits.LOCK!=1){/*nop*/};
    // now we should be running on f = 80MHz, f_cy = 40 MHz (40MIPS)
}
