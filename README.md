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
  - `PIN10 CLKO` - should be f<sub>cy</sub> = 7.37/2 MHz = 3.685 MHz
    - verified on Digilent AD2 scpe:  3.6706 MHz - error = `(3.6706/3.685-1)*100 = -0.39%`
    - see also [dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work](dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work) - in Digilent WaveForms software
  - `PIN2 RA0 LED` - blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
    - verified on Digilent AD2 scope: f = 4.9811 Hz (200.77 ms) - error = `(200.77 / 200 -1)* 100 = 0.38%` (
       period is inverse of frequency, therefore this error is positive)
    - see also [dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-RA0_LED.dwf3work](dsPIC33FJ_tut01.X/digilent-ad2/dsPIC33FJ-tut01-P10_OSCO.dwf3work) - in Digilent WaveForms software
    - please note that small error is induced by code-overhead that adds to delay.

## Tutorial 2 - use FRC + PLL at 79.12 MHz, blink LED in main loop using delay()

* [dsPIC33FJ_tut02.X/](dsPIC33FJ_tut02.X/)
  - Tutorial No. 2
  - use FRC (at 7.37 MHz) + PLL to get f<sub>osc</sub>= 79.12 MHz (most close value to 80 MHz target)
  - `PIN10 CLKO` - should be f<sub>cy</sub> = 79.12/2 MHz = 39.56 MHz (= 39.56 MIPS)
    - I'm unable to verify it on Digilent AD2 (it has maximum sampling frequency 100 Mhz which is not enough to
      get precise waveform)
  - `PIN2 RA0` - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
    - verified on Digilent AD2 scope: f = 4.9832 Hz (200.68 ms) - error = `(200.68/200-1)*100= 0.34%`
    - see also [dsPIC33FJ_tut02.X/digilent-ad2/dsPIC33FJ-tut02-RA0_LED.dwf3work](dsPIC33FJ_tut02.X/digilent-ad2/dsPIC33FJ-tut02-P10_OSCO.dwf3work) - in Digilent WaveForms software

PLL notes:

- used example from: http://ww1.microchip.com/downloads/en/DeviceDoc/DS-70596A.pdf
- on DS70596A-page 48-27, Example 48-2
- equation for PLL is (for M=43, N1=2, N2=2): `f_osc = f_in * M / N1 / N2 = 7.36 * 43 / 2 / 2 = 79.12 MHz`, or:

  $$ f_{osc} = f_{in} \times \frac{ M }{ N1 \times N2 } = f_{in} \times M / N1 / N2 = 7.36 \times 43 / 2 / 2 = 79.12 \\,\text{MHz} $$

- so we are a bit under wanted 80.00 MHz, because using higher M=44 would yield 80.96 MHz,
  which is overclocked over maximum 80.00 MHz.

## Tutorial 3 - Using OC PWM as DAC

Here we will use Output Compare 1 (OC1) module (standard since
8-bit PIC) for "slow" PWM (we will later use MC motor control PWM
for much faster results). PWM is set to fixed 25% duty - to verify that
it works as expected. PWM Resolution is 8-bit limited by TMR2 period which is set to 256.

* [dsPIC33FJ_tut03.X/](dsPIC33FJ_tut03.X/)

Existing features (from previous tutorial):
* PIN10 CLKO - should de f<sub>cy</sub> = 79.12/2 MHz = 39.56 MHz
* PIN2  RA0 - LED blinking with rate 200ms (=5Hz), toggle rate 100ms (10 Hz)
* PIN4 & 5 = reserved for programming debugging

Additional features:
* PIN3 Timer2 overflow, Toggle f<sub>cy</sub>/256 = 39.56/256 = 154.53 kHz, Frequency = 77.27 kHz
  Timer2 (TMR2) is used as time base for Output Compare 1 (OC1) PWM
* PIN6 RB2,RP2: OC1 - PWM with frequency 154.53 kHz, and Fixed duty 25%

WARNING! Measured values are slightly lower:
- expected TMR2 freq 77.27 kHz
- got 77.024 kHz
- error: -0.3%
Which corresponds to clock error (see previous tutorial)

Here are measurements using `Digilent Analog Discovery 2` scope and
software WaveForms v3.20.1:

![Tutorial 3 - OC1 PWM 25%](dsPIC33FJ_tut03.X/digilent-ad2/dsPIC33FJ-TUT3-PWM2-duty25pct.png)

And here is workspace file: (dsPIC33FJ_tut03.X/digilent-ad2/dsPIC33FJ-TUT03.dwf3work](dsPIC33FJ_tut03.X/digilent-ad2/dsPIC33FJ-TUT03.dwf3work]) for WaveForms software.


# Below are future tutorials - work in progress
 
## Tutorial 4+ - requisites for ADC and PWM as DAC

For real DSP example we need signal input and output.

For input we need:
- anti-alias filter, to filter frequencies above fs/2 (they would appear
  as parasitic low frequencies - called "aliasing")
  - [AN699 Anti-Aliasing, Analog Filters for Data Acquisition Systems](https://ww1.microchip.com/downloads/en/Appnotes/00699b.pdf) - quite good
- ADC (included on dsPIC33FJ)

For output we need:
- PWM (there is no DAC on PDIP version of dspIC33FJ)
- low-pass output filter - to filter out PWM base frequency and harmonics
  - [AN538 Using PWM to Generate Analog Output](https://ww1.microchip.com/downloads/en/AppNotes/00538c.pdf)

In both cases we may need FilterLab program:
- example: https://microchipdeveloper.com/asp0107:filter-design-example

Example for both at speech processing sample frequency (fs = 8kHz) is on
- [DM330011: MPLAB STARTER KIT FOR DSPIC DSCS](https://www.microchip.com/en-us/development-tool/dm330011)
- WARNING! Above URL was removed without notice. However we can still find
  at least data sheet, etc.:
- manual: https://ww1.microchip.com/downloads/en/DeviceDoc/51700B.pdf


# Known traps

* MCC Tool does not support dsPIC33FJ series (yes, that's it). So we have
  to code manually - however we can sometime reuse MCC generated code
  for similar CPU.
* PDIP version of dsPIC33FJ does NOT include 2 channel Audio
  DAC (please see feature matrix on datasheet `DS70291G-page 2` - it
  is really that). So we will use PWM + RC filter in future as poor-man
  DAC.

# ADC Resources

Most important - MPLAB starter kit for dsPIC (I don't have one, but there are important
docs and code examples):

- https://www.microchip.com/en-us/development-tool/dm330011
- User Guide: https://ww1.microchip.com/downloads/en/DeviceDoc/51700B.pdf

More theory on ADC and anti-aliasing (to prevent high frequency to appear as
parasitic low frequency - aliasing, there is needed low-pass filter):

- [AN699 Anti-Aliasing, Analog Filters for Data Acquisition Systems](https://ww1.microchip.com/downloads/en/Appnotes/00699b.pdf) - quite good
- [ADN003 Select the Right Operational Amplifier for your Filtering Circuits](https://ww1.microchip.com/downloads/en/DeviceDoc/adn003.pdf) not much detail...

From above User Guide (51700B.pdf) we know that on ADC input there is 

> This sixth-order Sallen-Key low-pass filter has a cut-off frequency of 3300 Hz.
> The output of the anti-aliasing filter is connected to input AN0 of the ADC module on the device.

From source https://ww1.microchip.com/downloads/en/DeviceDoc/SASK%20Record%20Play%20Demo%20With%20Intro.zip 
We can find:

```c
// SASK Record Play Demo With Intro/h/ADCChannelDrv.h
#define ADC_CHANNEL_FCY	40000000
#define ADC_FSAMP	8000	/* Sampling Frequency	*/

#define ADCON1VAL 0x0744  /* 12 bit ADC with signed fractional format
		     	  * Triggered by Timer 3 and auto start 
		   	  * sampling after conversion complete. */
#define ADCON2VAL 0x0000  /* AVdd and AVss voltage reference, 
		   	  * use channel 0 with no scan	*/
#define ADCON3VAL 0x0010  /* Tad is 16 Tcy				*/     
#define ADCHSVAL  0x0000  /* AN0 input on channel 0		*/	  
#define ADPCFGVAL 0xFFFE  /* AN0 input is Analog			*/
#define ADCSSLVAL 0x0000  /* No channel scanning			*/

// src/ADCChannelDrv.c
void ADCChannelInit	(ADCChannelHandle * pHandle,int * pBufferInDMA)
{
// ...
	AD1CON1 	= ADCON1VAL;    /* Load the ADC registers with  value 	*/
	AD1CON2 	= ADCON2VAL;    /* specified in 12bitADCDriver.h	*/
	AD1CON3 	= ADCON3VAL;
	AD1CHS0 	= ADCHSVAL;
	AD1PCFGLbits.PCFG0 = 0;
	AD1CSSL 	= ADCSSLVAL;

	TMR3 		= 0;
	PR3		= (ADC_CHANNEL_FCY/ADC_FSAMP) - 1;
}

```

So filter cut-off is 3_300 Hz (3 kHz) and ADC sample rate is 8_000 Hz (8 kHz)


# PWM DAC Resources

Related application notes:
- `AN538 Using PWM to Generate Analog Output`
- https://ww1.microchip.com/downloads/en/AppNotes/00538c.pdf

From above User Guide (51700B.pdf) we know that on PWM output there is connected 
low-pass filter:

> The PWM signal from the Output Compare module on the dsPIC33FJ256GP506
> device on the board is demodulated by the PWM low-pass filter (A4). This fourth-order
> filter uses two Op amps (U8:A and U8:B) on the MCP6022 quad Op amp IC.



But there are no more details (for example one important - cut-off frequency)

From source  we can find:

```c
// SASK Record Play Demo With Intro/h/OCPWMDrv.h
#define OCPWM_FCY	40000000
#define OCPWM_FPWM	64000
#define OCPWM_FSAMP	8000	/* Sampling Frequency	*/
#define OCPWM_FPWM_FSAMP_RATIO 	(OCPWM_FPWM/OCPWM_FSAMP)
#define OCPWM_TMRPRESCALE 			1
#define OCPWM_MAX_PWM_PERIOD	(((OCPWM_FCY/OCPWM_FPWM)*OCPWM_TMRPRESCALE) - 1)

// c

void OCPWMStart	(OCPWMHandle * pHandle)
{
//...
PR2	= OCPWM_MAX_PWM_PERIOD;		/* PWM Period			*/
OC1RS	= ((OCPWM_MAX_PWM_PERIOD)/2);	/* Initial Duty Cycle at 50% 	*/
OC1R	= ((OCPWM_MAX_PWM_PERIOD)/2);
OC1CON	= OCPWM_OCCON_WORD;		/* Turn module on		*/
// ...
}

// how is Duty cycle computed
#define OCPWM_HIGHEST_INPUT_VALUE	32767
#define OCPWM_LOWEST_INPUT_VALUE	-32768
#define OCPWM_INPUT_RANGE	(OCPWM_HIGHEST_INPUT_VALUE - (OCPWM_LOWEST_INPUT_VALUE))

unsigned int sample;
unsigned int pwmDutyCycle;

	/* Compute Duty cycle values for every input sample	*/
	sample = data[i] - (OCPWM_LOWEST_INPUT_VALUE);
	pwmDutyCycle = ((sample * OCPWM_MAX_PWM_PERIOD))/OCPWM_INPUT_RANGE;
	// the pwmDutyCycle has enforced boundaries:
	// 	minimum pwmDutyCycle = 1
	// 	maximum pwmDutyCycle =  OCPWM_MAX_PWM_PERIOD - 1
```
So it seems that PWM period (or freq) is 64 000 Hz (64 kHz). So for each sample
(at 8 kHz) there are 8 PWM periods on output.

# Resources

* My old int dsPIC33FJ intro project on GitHub - based on Microchip
  C30 example:

  - https://github.com/hpaluch/dsPIC33fj-hello.X

* [PIC Microstick II][PIC Microstick II]
* [dsPIC33FJ128MC802][dsPIC33FJ128MC802]

Very good study material - how to do audio + DMA and also option so use PWM + RC filter as DAC:

- `MPLAB STARTER KIT FOR DSPIC DSCS` https://www.microchip.com/en-us/development-tool/dm330011
- Do not forget to download https://ww1.microchip.com/downloads/en/DeviceDoc/SASK%20Record%20Play%20Demo%20With%20Intro.zip and study it

[PIC Microstick II]: https://www.microchip.com/DevelopmentTools/ProductDetails/dm330013-2
[dsPIC33FJ128MC802]: https://www.microchip.com/wwwproducts/en/dsPIC33FJ128MC802
