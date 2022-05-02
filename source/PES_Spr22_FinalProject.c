
#include "MKL25Z4.h"

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

#include "UART.h"
#include "LEDs.h"
#include "IR_pin.h"
#include "sysclock.h"

void init();

extern bool newMessage;
extern bool IR_bit_Zero_Flag;
extern bool IR_bit_One_Flag;

int main(void) {

	init();

	uint32_t IR_data = 0;
	uint8_t IR_data_bit = 0;

    while(1){

    	if(newMessage)
    	{
			IR_data = 0;
			IR_data_bit = 0;
    		newMessage = false;

    	}

    	if(IR_bit_Zero_Flag){

    		IR_data &= ~(1 << (31-IR_data_bit));
    		IR_bit_Zero_Flag=0;
    		IR_data_bit++;

    	}

    	if(IR_bit_One_Flag){

    		IR_data |= (1 << (31-IR_data_bit));
    		IR_bit_One_Flag=0;
    		IR_data_bit++;

    	}

		if(IR_data_bit >= 32){
    		printf("%x\r\n",IR_data);
    		IR_data_bit = 0;

		}

    }

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
