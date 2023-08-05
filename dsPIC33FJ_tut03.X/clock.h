// file clock.h - header for dsPIC clock switch to PLL
#ifndef CLOCK_H
#define	CLOCK_H

// switch clock from FRC 7.37 MHz to FRC+PLL at 79.12 MHz ( 39.56 MIPS)
void CLOCK_Initialize(void);
#endif	/* CLOCK_H */
