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
    programmers) and also for PicKit 3 - that IDE version is simply
    rubbish (if it was not ill intention - to force people to buy new hardware?).

* XC16 v2.10 

# List of projects

Important note:

All MPLAB X IDE projects have 2 configurations:
- `default` - used for programming and debugging real Microstick II hardware
- `Simulator` - running code in software simulator - no hardware required.

Before building and/or Debugging/running please select right configuration in MPLAB X IDE toolbar.

## Tutorial 1 - use FRC oscillator, blink LED in main loop using delay() 

* [dsPIC33FJ_tut01.X/](dsPIC33FJ_tut01.X/)
  - Tutorial No. 1
  - PIN10 CLKO- should be f<sub>cy</sub> = 7.37/2 MHz = 3.685 MHz
    - verified on Digilent AD2 scpe:  3.6706 MHz - error = `(3.6706/3.685-1)*100 = -0.39%`
    - see also [dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work](dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work) - in Digilent WaveForms software
  - PIN2  RA0 - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
    - verified on Digilent AD2 scope: f = 4.9811 Hz (200.77 ms) - error = `(200.77 / 200 -1)* 100 = 0.38%` (
       period is inverse of frequency, therefore this error is positive)
    - see also [dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-RA0_LED.dwf3work](dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work) - in Digilent WaveForms software
    - please note that small error is induced by code-overhead that adds to delay.

## Tutorial 2 - use FRC + PLL at 79.12 MHz, blink LED in main loop using delay()

According to datasheet:
- http://ww1.microchip.com/downloads/en/DeviceDoc/DS-70596A.pdf
- on DS70596A-page 48-27, Example 48-2
- equation is (for M=43, N1=2, N2=2): `f_osc = f_in * M / N1 / N2 = 7.36 * 43 / 2 /2 = 79.12 MHz`
- so we are a bit under wanted 80.00 Mhz, because using higher M=44 would yield 80.96 Mhz,
  which is overclocked over maximum 80.00 Mhz.

* [dsPIC33FJ_tut02.X/](dsPIC33FJ_tut02.X/)
  - Tutorial No. 2
  - use FRC (at 7.37 MHz) + PLL to get f<sub>osc</sub>= 79.12 MHz (most close value to 80 MHz target)
  - PIN10 CLKO- should be f<sub>cy</sub> = 79.12/2 MHz = 39.56 MHz (= 39.56 MIPS)
    - I'm unable to verify it on Digilent AD2 (it has maximum sampling frequency 100 Mhz which is not enough)
  - PIN2  RA0 - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
    - verified on Digilent AD2 scope: f = 4.9832 Hz (200.68 ms) - error = `(200.68/200-1)*100= 0.34%`
    - see also [dsPIC33FJ_tut02.X/digilent-ad2/dsPIC33FJ-tut02-RA0_LED.dwf3work](dsPIC33FJ_tut02.X/digilent-ad2/dsPIC33FJ-tut02-P10_OSCO.dwf3work) - in Digilent WaveForms software


# Known traps

* MCC Tool does not support dsPIC33FJ series (yes, that's it). So we have
  to code manually - however we can sometime reuse MCC generated code
  for similar CPU.
* PDIP version of dsPIC33FJ does NOT include 2 channel Audio
  DAC (please see feature matrix on datasheet `DS70291G-page 2` - it
  is really that). So we will use PWM + RC filter in future as poor-man
  DAC.

# Resources

* My old int dsPIC33FJ intro project on GitHub - based on Microchip
  C30 example:

  - https://github.com/hpaluch/dsPIC33fj-hello.X

* [PIC Microstick II][PIC Microstick II]
* [dsPIC33FJ128MC802][dsPIC33FJ128MC802]

[PIC Microstick II]: https://www.microchip.com/DevelopmentTools/ProductDetails/dm330013-2
[dsPIC33FJ128MC802]: https://www.microchip.com/wwwproducts/en/dsPIC33FJ128MC802
