// ***********************************************
// ***********************************************
// **********	PES Spring 2022			**********
// **********	Assignment 3:			**********
// **********	Blinkenlights			**********
// ***********************************************
// ***********************************************
// **********	By: Erich Clever		**********
// **********	Date: Feb 11, 2022		**********
// ********** Instructor: Howdy Pierce	**********
// ***********************************************
// ***********************************************
// **********	Version: 1.0			**********
// ***********************************************
// **********   File: LEDs.c		    **********
// ***********************************************
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

//void LED_test(){
//
//	//Ensure all of the LEDs are OFF
//	LED_OFF(ALL_LEDS);
//
//	//Turn red LED on for 500 ms then off for 100 ms
//	LED_ON(RED);
//	myDelay(500);
//	LED_OFF(RED);
//	myDelay(100);
//
//	//Turn green LED on for 500 ms then off for 100 ms
//	LED_ON(GREEN);
//	myDelay(500);
//	LED_OFF(GREEN);
//	myDelay(100);
//
//	//Turn blue LED on for 500 ms then off for 100 ms
//	LED_ON(BLUE);
//	myDelay(500);
//	LED_OFF(BLUE);
//	myDelay(100);
//
//	//Turn all LEDs on for 100 ms then off for 100 ms twice, consecutively
//	LED_ON(ALL_LEDS);
//	myDelay(100);
//	LED_OFF(ALL_LEDS);
//	myDelay(100);
//	LED_ON(ALL_LEDS);
//	myDelay(100);
//	LED_OFF(ALL_LEDS);
//	myDelay(100);
//
//}
