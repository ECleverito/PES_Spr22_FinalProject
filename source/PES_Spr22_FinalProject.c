
#include "MKL25Z4.h"

#include "stdio.h"

#include "UART.h"
#include "LEDs.h"
#include "IR_pin.h"
#include "sysclock.h"

void init();

int main(void) {

	init();

    while(1)
    	;
    return 0;

}

void init(){

  	sysclock_init();
  	UART0_init();
  	initLED(RED);
  	toggleLED(RED);
  	IR_pin_init();

  	char introString[] = "********************************************************************************\n\r"
  						 "\t\t\tIR Universal Receiver\n\r"
				 	 	 "********************************************************************************\n\r"
  						 "\n\r"
  						 "Available commands (case insensitive):\n\n\r"
  						          "\tlistcodes - Lists the codes that have been received\n\r"
  								  "\t   listen - Listens for new codes\n\r"
  						 "\n\r";

  	int i = 0;
  	while( introString[i++] != '\0' )
  		putchar(introString[i]);

}
