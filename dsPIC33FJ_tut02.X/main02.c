/*
 * File:   main02.c
 * Author: Henryk Paluch
 * Created on July 6, 2023
 * Description:
 * Tutorial No. 2 for dsPIC33FJ and Microstick II board.
 * Functions:
 * - switch oscillator from f_osc = 7.37 MHz to 80 MHz (40 MIPS)
 * - PIN10 CLKO- should de f_cy = 80/2 MHz = 40 MHz
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


/* We use Fast RC (FRC) oscillator. According to datasheet DS70291G-page 144
 * multiplied with PLL to 80 MHz
 * PLL Osc frequency is f_osc = 80 MHz
 * Instruction cycle frequency is f_cy = f_osc/2 = 80 /2 = 40 MHz
 * which equals to 40 MIPS (Mega instructions per second)
 */

// this FCY (f_cy) required for proper operation of __delay_us() and __delay_ms()
#define FCY 40000000UL 
#include "xc.h"
#include <libpic30.h>  // __delay_us()) and __delay_ms())

int main(void) {
    // RA0 - LED OUTPUT
    LATAbits.LATA0 = 0; // RA0 LED OFF - store value in Latch
    TRISAbits.TRISA0 = 0; // RA0 LED is now output
    while(1){
        __delay_ms(100); // wait 100ms
        LATAbits.LATA0 ^= 1; // toggle LED at rate 100ms (10Hz),
                            // blink rate = 200ms (5 Hz)
    }

    /* Never reached: */
    return 0;
}
