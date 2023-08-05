/*
 * File:   main02.c
 * Author: Henryk Paluch
 * Created on July 6, 2023
 * Description:
 * Tutorial No. 3 for dsPIC33FJ and Microstick II board.
 *   Using standard (slow) Output Compare (OC) Timer2 for PWM
 * Functions:
 * - switch oscillator from f_osc = 7.37 MHz to max 79.12 MHz (39.56 MIPS) using PLL
 * - PIN10 CLKO- should de f_cy = 79.12/2 MHz = 39.56 MHz
 * - PIN2  RA0 - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
 * - PIN3 Timer2 overflow, Toggle at 79.12/256 = 309 kHz, Frequency = 154.5 kHz
 * - PIN4 & 5 = reserved for programming debugging
 * - PIN6 RB2,RP2: OC1 - PWM with frequency 309 kHz, and duty 25%
 * We use standard OC Output Compare for PWM. However it is too slow
 * for good DAC output
 * 
 * Required hardware:
 * - Microstick II board DM330013-2
 * Hardware setup:
 * - dsPIC33FJ128MC802 inserted into socket U5 (included)
 * - programming switch in position A
 * - LED Jumper J3 Closed
 * 
 * Required software:
 * - MPLAB X IDE v6.10 with updates (Updates required for PKOB programmer to work)
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
#include <stdint.h>
#include <libpic30.h>  // __delay_us()) and __delay_ms())
#include "clock.h"

// Linux like type aliases
#define u16 uint16_t

#define HP_PWM_PERIOD 256U // 8-bit PWM resolution
#define HP_PWM_DUTY   HP_PWM_PERIOD/4U  // 25%

// Initialize PWM (our future "DAC")
void PWM_Initialize(void)
{
    // mostly Copy & Paste from DS70209A-page 13-17
    // Initialize Output Compare Module
    OC1CONbits.OCM = 0b000; // Disable Output Compare Module
    OC1R = HP_PWM_DUTY; // Write the duty cycle for the first PWM pulse
    OC1RS = HP_PWM_DUTY; // Write the duty cycle for the second PWM pulse
    OC1CONbits.OCTSEL = 0; // Select Timer 2 as output compare time base
    OC1R = HP_PWM_DUTY; // Load the Compare Register Value
    OC1CONbits.OCM = 0b110; // Select the Output Compare mode 
  
    // Initialize and enable Timer2 that is used as Timer base for PWM
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR2 = 0x00; // Clear timer register
    PR2 = HP_PWM_PERIOD-1; // PR2+1 = PWM resolution
    IPC1bits.T2IP = 0x01; // Set Timer 2 Interrupt Priority Level
    IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
    IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
    T2CONbits.TON = 1; // Start Timer    
}

/* Timer 2 ISR - used as Timer base for PWM */
// Interrupt rate should be fCY/(PR2+1) 79.12/256 = 309 kHz
void __attribute__((__interrupt__,auto_psv)) _T2Interrupt( void )
{
    LATAbits.LATA1 ^= 1; // toggle RA1 PIN3 on timer overflow
    // OC1RS = 300; // Write Duty Cycle value for next PWM cycle
    IFS0bits.T2IF = 0; // Clear Timer 2 interrupt flag
}

// Peripheral Pin Select - Remap Pins for PWM
void PPS_Initialize(void)
{
    __builtin_write_OSCCONL(OSCCON & ~_OSCCON_IOLOCK_MASK); // unlock PPS
    RPOR1bits.RP2R = 0x12;    //PIN6 RB2,RP2->OC1 Output Compare1 (PWM Output)
    __builtin_write_OSCCONL(OSCCON | _OSCCON_IOLOCK_MASK); // lock PPS
}

int main(void) {
    // RA0 PIN2 - LED OUTPUT, RA1 PIN3 Timer2 Overflow toggle
    LATA = 0; // by default everything low on PORTA
    TRISA = ~ (_TRISA_TRISA0_MASK|_TRISA_TRISA1_MASK); // RA0 and RA1 are outputs
    PPS_Initialize();
    // switch clock from FRC 7.37 MHz to FRC+PLL at 79.12 MHz
    CLOCK_Initialize();
    PWM_Initialize();
    // now we can use __delay_us() and __delay_ms())
    while(1){
        __delay_ms(100); // wait 100ms
        LATAbits.LATA0 ^= 1; // toggle LED at rate 100ms (10Hz),
                            // blink rate = 200ms (5 Hz)
    }

    /* Never reached: */
    return 0;
}
