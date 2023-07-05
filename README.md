# Tutorial for dsPIC33FJ on Microstick II

Here is step by step tutorial that will be hopefully
someday full example of real-time DSP - ADC conversion,
processing, and DAC conversion. However it will take
some time...

Common required hardware for all projects:

* [Microstick II][PIC Microstick II] board.
* [dsPIC33FJ128MC802][dsPIC33FJ128MC802] inserted in socket U5
* Programming switch in position `A`
* LED Jumper J3 Closed
 
Required software:

* MPLAB X IDE v6.00 - last version that works.

  - Do NOT use v6.05 - it will freeze forever when Master/Slave project
    is associated (not used in this case, but anyway...)
  - Do NOT use v6.10 - it has broken support for PKOB (PicKit on Board
    programmers) and alos for PicKit 3 - that X IDE version is simply
    rubbish...

* XC16 v2.10 

# List of projects

Important note:

All MPLAB X IDE projects has 2 configurations:
- `default` - used for programming and debugging real Microstick II hardware
- `Simulator` - running code in software simulator - no hardware required.

Before building and/or Debugging/running please select right configuration in MPLAB X IDE toolbar.


## Tutorial 1 - use FRC oscillator, blink LED in main loop using delay() 

* [dsPIC33FJ_tut01.X/](dsPIC33FJ_tut01.X/)
  - Tutorial No. 1
  - PIN10 CLKO- should be f<sub>cy</sub> = 7.37/2 MHz = 3.685 MHz
    - verified on Digilent AD2 scpe:  3.6706 MHz
    - see also [dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work](dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work) - in Digilent WaveForms software
  - PIN2  RA0 - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
    - verified on Digilent AD2 scope: f = 4.9811 Hz (200.77 ms)
    - see also [dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-RA0_LED.dwf3work](dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work) - in Digilent WaveForms software

# Known traps

* MCC Tool does not support dsPIC33FJ series (yes, that's it)
* PDIP version of dsPIC33FJ does NOT include 2 channel Audio
  DAC (please see feature matrix on datasheets - it is really
  that). So we will use PWM + RC filter in future as poor-man
  DAC.

# Resources

* My old int dsPIC33FJ intro project on GitHub - based on Microchip
  C30 example:

  - https://github.com/hpaluch/dsPIC33fj-hello.X

* [PIC Microstick II][PIC Microstick II]
* [dsPIC33FJ128MC802][dsPIC33FJ128MC802]

[PIC Microstick II]: https://www.microchip.com/DevelopmentTools/ProductDetails/dm330013-2
[dsPIC33FJ128MC802]: https://www.microchip.com/wwwproducts/en/dsPIC33FJ128MC802
