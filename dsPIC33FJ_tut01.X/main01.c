/*
 * File:   main01.c
 * Author: Administrator
 * Created on July 5, 2023, 3:19 PM
 * Description:
 * Tutorial No. 1 for dsPIC33FJ and Microstick II board.
 * Functions:
 * - PIN10 CLKO- should de f_cy = 7.37/2 MHz = 3.685 MHz
 * - PIN2  RA0 - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
 * 
 * Required hardware:
 * - Microstick II board DM330013-2
 * Hardware setup:
 * - dsPIC33FJ128MC802 inserted into socket U5 (included)
 * - programming switch in position A
 * - LED Jumepr J3 Closed
 * 
 * Required software:
 * - MPLAB X IDE v6.00 - last working version
 * - XC16 v2.10
 * - DPF 1.3.64
 */

// Start OF Configuration EEPROM
// DSPIC33FJ128MC802 Configuration Bit Settings
// 'C' source line config statements
// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// END OF Configuration EEPROM

/* We use Fast RC (FRC) oscillator. According to datasheet DS70291G-page 144
 * Oscillator frequency is f_osc = 7.37 MHz
 * Instruction cycle frequency is f_cy = f_osc/2 = 7.37 /2 = 3.685 MHz.
 * 
 */

// this FCY (f_cy) required for proper operation of __delay_us() and __delay_ms()
#define FCY 3685000UL 
#include "xc.h"
#include <libpic30.h>  // __delay_us()) and __delay_ms())

int main(void) {
    // RA0 - LED OUTPUT
    LATAbits.LATA0 = 0; // LED OFF
    TRISAbits.TRISA0 = 0; // RA1 is now output
    while(1){
        __delay_ms(100); // wait 100ms
        LATAbits.LATA0 ^= 1; // toggle LED at rate 100ms (10Hz),
                            // blink rate = 200ms (5 Hz)
    }
    return 0;
}
