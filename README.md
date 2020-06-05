# Internal-Temperature-Sensor
Sensing the internal temperature of the Tiva microcontroller and displaying the temperature using a Putty window.
## Problem Statment
Displaying the internal sensor on a putty window using UART
## Using Texas instrument (TM4C123GH6PM)
- It is cheap to use and is easy to implement for an enthusiast. 
- UART compatible.
- It has inbuit temperature sensor.
## METHOD
- Used the Keil software to build the code and dump it on the Texas instrument
-In the code intialized ADC and UART 

### ADC Intialization
- ADC is intialzed the clock and PE2 pin.
- Intialized WTimer so that the ADC is sampled per second

### UART Intialization 
- Instialized UART0
- Intialized value to IRBD and FBRD

#### VALUES CALCULATED BY USING THE FORMULA
- IRBD=(CLOCK/16* baurd rate)
- FBRD=( Decimal numbers of IRBD * 64)
```
      UART0_IBRD_R = 8;        /* IBRD = int(16,000,000 / (16 * 115,200)) = int(8.680) */
      UART0_FBRD_R = 44;       /* FBRD = round(0.5104 * 64 ) = 44 */   
```

