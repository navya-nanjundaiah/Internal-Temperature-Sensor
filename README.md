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

### Values are calculated using this formula
- IRBD=UARTSysClk / (ClkDiv * Baud Rate)
- UARTFBRD{ DIVFRAC] = integer(BRDF * 64 + 0.5) // Add 0,5 if you have rounding errors
```
      UART0_IBRD_R = 8;        /* IBRD = int(16,000,000 / (16 * 115,200)) = int(8.680) */
      UART0_FBRD_R = 44;       /* FBRD = round(0.5104 * 64 ) = 44 */   
```
### As alternate clock is used we set UARTCC To 0X5
```
	UART0_CC_R=5;
```

### In the putty window select serial and provide serial line and speed

