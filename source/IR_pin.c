/*
 * IR_pin.c
 *
 *  Created on: May 1, 2022
 *      Author: erich
 */
#include "MKL25Z4.h"

#include "IR_pin.h"

#include "LEDs.h"

void IR_pin_init(){

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

	toggleLED(RED);
	PORTA->ISFR = 0xffffffff;

}
