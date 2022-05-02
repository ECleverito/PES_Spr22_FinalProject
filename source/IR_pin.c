/*
 * IR_pin.c
 *
 *  Created on: May 1, 2022
 *      Author: erich
 */
#include "MKL25Z4.h"

#include "IR_pin.h"

#include "LEDs.h"
#include "TPM.h"

#include "stdbool.h"
#include "stdio.h"

bool newMessage = 0;
bool bitFlag = false;
bool IR_bit_Zero_Flag = false;
bool IR_bit_One_Flag = false;

void IR_pin_init(){

	TPM0_init();

	//Send the clock to PORTA
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Generate interrupt on detection of either edge and
	//for GPIO mode in multiplexer
	PORTA->PCR[13] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(11);

	//Set pin 3 as input
	GPIOA->PDDR &= ~(1 << PIN_3);

	//Enable PORT interrupts
	NVIC_SetPriority(PORTA_IRQn, 2);
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);

}

void PORTA_IRQHandler(){

	uint16_t pulseDuration = TPM0->CNT;
	TPM0->CNT = 0;

	if(TPM0->SC & TPM_SC_TOF_MASK){

		//Overflow flag means this is a new message,
		//as new data has not arrived for a long time.

		//Clear overflow flag by setting it
		TPM0->SC |= TPM_SC_TOF_MASK;
		newMessage = true;
		bitFlag = false;
	}
	else{

		if(pulseDuration > 20000){

			//Leader code. Can ignore.
		}
		else if(bitFlag){

			if( pulseDuration > 7000 ){
				IR_bit_One_Flag = 1;

			}
			else{
				IR_bit_Zero_Flag = 1;
			}
			bitFlag=0;

		}
		else
			bitFlag=1;

	}
//	toggleLED(RED);
	PORTA->ISFR = 0xffffffff;

}
