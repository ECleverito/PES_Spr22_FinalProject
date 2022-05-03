// ***********************************************
// ***********************************************
// **********	PES Spring 2022			**********
// **********	Final Project:			**********
// **********	Universal IR Receiver	**********
// ***********************************************
// ***********************************************
// **********	By: Erich Clever		**********
// **********	Date: May 2, 2022		**********
// ********** Instructor: Howdy Pierce	**********
// ***********************************************
// ***********************************************
// **********	Version: 1.0			**********
// ***********************************************
// **********   File: LEDs.c		    **********
// ***********************************************
// Code for initialization and interface functions
// with LEDs on FRDM KL25Z development board.
// ***********************************************

#include <LEDs.h>
//#include <myDelay.h>
#include "MKL25Z4.h"


void initLED(LED_t myLED){

	switch(myLED)
	{
	case RED:
		//Route the clock
		SIM->SCGC5 |= RED_LED_SCGC5_MASK;

		//Set multiplexer to GPIO
		RED_LED_PCR &= ~PORT_PCR_MUX_MASK;
		RED_LED_PCR |= PORT_PCR_MUX(1);

		//Set as output
		RED_LED_GPIO_PORT->PDDR |= (1 << RED_LED_PIN);

		break;

	case GREEN:
		SIM->SCGC5 |= GREEN_LED_SCGC5_MASK;

		GREEN_LED_PCR &= ~PORT_PCR_MUX_MASK;
		GREEN_LED_PCR |= PORT_PCR_MUX(1);

		GREEN_LED_GPIO_PORT->PDDR |= (1 << GREEN_LED_PIN);

		break;

	case BLUE:
		SIM->SCGC5 |= BLUE_LED_SCGC5_MASK;

		BLUE_LED_PCR &= ~PORT_PCR_MUX_MASK;
		BLUE_LED_PCR |= PORT_PCR_MUX(1);

		BLUE_LED_GPIO_PORT->PDDR |= (1 << BLUE_LED_PIN);

		break;

	case ALL_LEDS:
		SIM->SCGC5 |= BLUE_LED_SCGC5_MASK;
		SIM->SCGC5 |= GREEN_LED_SCGC5_MASK;

		BLUE_LED_PCR &= ~PORT_PCR_MUX_MASK;
		BLUE_LED_PCR |= PORT_PCR_MUX(1);
		GREEN_LED_PCR &= ~PORT_PCR_MUX_MASK;
		GREEN_LED_PCR |= PORT_PCR_MUX(1);
		RED_LED_PCR &= ~PORT_PCR_MUX_MASK;
		RED_LED_PCR |= PORT_PCR_MUX(1);

		GREEN_LED_GPIO_PORT->PDDR |= (1 << GREEN_LED_PIN);
		RED_LED_GPIO_PORT->PDDR |= (1 << RED_LED_PIN);
		BLUE_LED_GPIO_PORT->PDDR |= (1 << BLUE_LED_PIN);
		break;
	}

}

void toggleLED(LED_t myLED){

	switch(myLED){

	case RED:
	case GREEN:
		//Set port toggle bit
		GREEN_LED_GPIO_PORT->PTOR |= (1<< myLED);
		break;

	case BLUE:
		BLUE_LED_GPIO_PORT->PTOR |= (1<< myLED);
		break;

	case ALL_LEDS:
		break;

	}

}

void LED_ON(LED_t myLED){

	switch(myLED){

		case RED:
			//Set port clear bit
			RED_LED_GPIO_PORT->PCOR |= (1<< RED_LED_PIN);
			break;

		case GREEN:
			GREEN_LED_GPIO_PORT->PCOR |= (1<< GREEN_LED_PIN);
			break;

		case BLUE:
			BLUE_LED_GPIO_PORT->PCOR |= (1<< BLUE_LED_PIN);
			break;

		case ALL_LEDS:
			GREEN_LED_GPIO_PORT->PCOR |= (1<< GREEN_LED_PIN);
			RED_LED_GPIO_PORT->PCOR |= (1<< RED_LED_PIN);
			BLUE_LED_GPIO_PORT->PCOR |= (1<< BLUE_LED_PIN);
			break;

	}
}

void LED_OFF(LED_t myLED){

	switch(myLED){

		case RED:
			//Set port set bit
			RED_LED_GPIO_PORT->PSOR |= (1<< RED_LED_PIN);
			break;

		case GREEN:
			GREEN_LED_GPIO_PORT->PSOR |= (1<< GREEN_LED_PIN);
			break;

		case BLUE:
			BLUE_LED_GPIO_PORT->PSOR |= (1<< BLUE_LED_PIN);
			break;

		case ALL_LEDS:
			GREEN_LED_GPIO_PORT->PSOR |= (1<< GREEN_LED_PIN);
			RED_LED_GPIO_PORT->PSOR |= (1<< RED_LED_PIN);
			BLUE_LED_GPIO_PORT->PSOR |= (1<< BLUE_LED_PIN);
			break;

	}
}

