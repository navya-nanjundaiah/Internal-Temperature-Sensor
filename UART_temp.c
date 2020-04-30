#include <stdio.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
//#include "inc/UART.h"

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

/* U0Rx receive connected to PA0 */
/* U0Tx transmit connected to PA1 */

#define UART_FR_TXFF            0x00000020  /* UART Transmit FIFO Full */
#define UART_FR_RXFE            0x00000010  /* UART Receive FIFO Empty */
#define UART_LCRH_WLEN_8        0x00000060  /* 8 bit word length */
#define UART_LCRH_FEN           0x00000010  /* UART Enable FIFOs */
#define UART_CTL_UARTEN         0x00000001  /* UART Enable */
#define SYSCTL_RCGC1_UART0      0x00000001  /* UART0 Clock Gating Control */
#define SYSCTL_RCGC2_GPIOA      0x00000001  /* port A Clock Gating Control */

void UART_Init(void);
char UART_InChar(void);
void UART_OutChar(int data);
void Adc_Init(void);

char* msg = "\n\rTEMPERATURE\n\r";

int main(void){
    
	  volatile int temperature,temp,m,n;

    UART_Init();
	  Adc_Init();

		while( *msg)
        UART_OutChar(*msg++);
			

    while( 1 ) {
			 while((ADC0_RIS_R & 8) == 0)
            ;                    /* wait for conversion complete */
			  temp=(((147- (247 * (ADC0_SSFIFO3_R) / 4096))&0xF0)>>4);
        temperature =((147 - (247* (ADC0_SSFIFO3_R) / 4096))&0x0F);
			  // temperature =(147 - (247* (ADC0_SSFIFO3_R) / 4096))/2;
			  //temp=((temperature-32)*5)/9;
        ADC0_ISC_R = 8;          /* clear completion flag */
			 // c=(temperature&0X0F);
			 m=temp|0x30;
			 n=temperature|0x30;
			  UART_OutChar(m);
			  UART_OutChar(n);
			  
			  //m=(temperature&0xF0
			  //UART_OutChar(m);
			 
        
    }
	
}

/* UART_Init
* Initialize the UART for 115,200 baud rate (assuming 16 MHz bus clock),
* 8 bit word length, no parity bits, one stop bit, FIFOs enabled
* Input: none
* Output: none
*/
void UART_Init(void)
{
      SYSCTL_RCGCUART_R |= 0x01;            /* activate UART0 */
      SYSCTL_RCGCGPIO_R |= 0x01;            /* activate port A */

      while((SYSCTL_PRGPIO_R&0x0001) == 0){}; /* ready? */

      UART0_CTL_R &= ~UART_CTL_UARTEN;      /* disable UART */
      UART0_IBRD_R = 8;        /* IBRD = int(16,000,000 / (16 * 115,200)) = int(8.680) */
      UART0_FBRD_R = 44;       /* FBRD = round(0.5104 * 64 ) = 44 */
                               /* 8 bit word length (no parity bits, one stop bit, FIFOs) */
      UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
			UART0_CC_R=5;
      UART0_CTL_R |= UART_CTL_UARTEN;       /* enable UART */
      GPIO_PORTA_AFSEL_R |= 0x03;           /* enable alt funct on PA1-0 */
      GPIO_PORTA_DEN_R |= 0x03;             /* enable digital I/O on PA1-0 */
      GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011; /* configure PA1-0 as UART */
      GPIO_PORTA_AMSEL_R &= ~0x03;          /*  analog functionality on PA */
}

/* UART_InChar
* Wait for new serial port input
* Input: none
* Output: ASCII code for key typed
*/
/*char UART_InChar(void)
{
      while( (UART0_FR_R & UART_FR_RXFE) != 0)
          ;
      return((char)(UART0_DR_R & 0xFF));
}*/

/* UART_OutChar
* Output 8-bit to serial port
* Input: letter is an 8-bit ASCII character to be transferred
* Output: none
*/
void UART_OutChar(int data)
{
      while((UART0_FR_R & UART_FR_TXFF) != 0)
          ;
      UART0_DR_R = data;
}
void Adc_Init(void)
{
	       SYSCTL_RCGCADC_R |= 1;       /* enable clock to ADC0 */
         SYSCTL_RCGCWTIMER_R |= 1;    /* enable clock to WTimer Block 0 */
 
	/* initialize ADC0 */
        ADC0_ACTSS_R &= ~8;          /* disable SS3 during configuration */
        ADC0_EMUX_R &= ~0xF000;
        ADC0_EMUX_R |= 0x5000;       /* timer trigger conversion seq 0 */
        ADC0_SSMUX3_R = 0;           /* get input from channel 0 */
        ADC0_SSCTL3_R |= 0x0E;       /* take chip temperature, set flag at 1st sample */
        ADC0_ACTSS_R |= 8;           /* enable ADC0 sequencer 3 */
 
        /* initialize wtimer 0 to trigger ADC at 1 sample/sec */
        WTIMER0_CTL_R = 0;           /* disable WTimer before initialization */
        WTIMER0_CFG_R = 0x04;        /* 32-bit option */
        WTIMER0_TAMR_R = 0x02;       /* periodic mode and down-counter */
        WTIMER0_TAILR_R = 16000000;  /* WTimer A interval load value reg (1 s) */
        WTIMER0_CTL_R |= 0x20;       /* timer triggers ADC */
        WTIMER0_CTL_R |= 0x01;       /* enable WTimer A after initialization */
}

