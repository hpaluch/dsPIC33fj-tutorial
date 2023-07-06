/*
 * File:   main02.c
 * Author: Henryk Paluch
 * Created on July 6, 2023
 * Description:
 * Tutorial No. 2 for dsPIC33FJ and Microstick II board.
 * Functions:
 * - switch oscillator from f_osc = 7.37 MHz to max 79.12 MHz (39.56 MIPS) using PLL
 * - PIN10 CLKO- should de f_cy = 79.12/2 MHz = 39.56 MHz
 * - PIN2  RA0 - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
 * 
 * Required hardware:
 * - Microstick II board DM330013-2
 * Hardware setup:
 * - dsPIC33FJ128MC802 inserted into socket U5 (included)
 * - programming switch in position A
 * - LED Jumper J3 Closed
 * 
 * Required software:
 * - MPLAB X IDE v6.00 - last working version
 * - XC16 v2.10
 * - DFP: dsPIC33F-GP-MC_DFP v1.3.64
 */

/* We use Fast RC (FRC) oscillator at f_rc = 7.37 Mhz + PLL to get 79.12 MHz.
 * Instruction cycle frequency is f_cy = f_osc/2 = 79.12/2 = 39.56 MHz
 * which is most close to 40 MIPS target (other PLL configuration would cause
 * overclocking)
 */

// this FCY (f_cy - frequency of instruction cycle) is required
// for proper operation of __delay_us() and __delay_ms()
#define FCY 39560000UL
#include <xc.h>
#include <libpic30.h>  // __delay_us()) and __delay_ms())
#include "clock.h"

int main(void) {
    // RA0 - LED OUTPUT
    LATAbits.LATA0 = 0; // RA0 LED OFF - store value in Latch
    TRISAbits.TRISA0 = 0; // RA0 LED is now output
    // switch clock from FRC 7.37 MHz to FRC+PLL at 79.12 MHz
    CLOCK_Initialize();
    // now we can use __delay_us() and __delay_ms())
    while(1){
        __delay_ms(100); // wait 100ms
        LATAbits.LATA0 ^= 1; // toggle LED at rate 100ms (10Hz),
                            // blink rate = 200ms (5 Hz)
    }

    /* Never reached: */
    return 0;
}
