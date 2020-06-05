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
- Intialzed WTimer so that the ADC is sampled per second

### UART Intialization 
- Instialzed UART0
- Intialzed value to IRBD and FBRD

#### VALUES CALCULATED BY USING THE FORMULA
- IRBD=(CLOCK/16* baurd rate)
- FBRD=( DECIM OF IR*
      UART0_IBRD_R = 8;        
      UART0_FBRD_R = 44;       
