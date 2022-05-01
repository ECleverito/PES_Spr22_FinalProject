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
// **********   File: LEDs.h		    **********
// ***********************************************
// ***********************************************

#ifndef LEDS_H_
#define LEDS_H_

//Pins connected to LEDs
#define GREEN_LED_PIN 19
#define RED_LED_PIN 18
#define BLUE_LED_PIN 1

//GPIO ports of pins connected to LEDs
#define GREEN_LED_GPIO_PORT	GPIOB
#define RED_LED_GPIO_PORT	GPIOB
#define BLUE_LED_GPIO_PORT	GPIOD

#define GREEN_LED_PCR	PORTB->PCR[GREEN_LED_PIN]
#define RED_LED_PCR		PORTB->PCR[RED_LED_PIN]
#define BLUE_LED_PCR	PORTD->PCR[BLUE_LED_PIN]

//SIM masks for routing clock to GPIO ports
#define GREEN_LED_SCGC5_MASK SIM_SCGC5_PORTB_MASK
#define RED_LED_SCGC5_MASK SIM_SCGC5_PORTB_MASK
#define BLUE_LED_SCGC5_MASK SIM_SCGC5_PORTD_MASK

//Enum for specifying the LED to turn on
typedef enum{
	RED = RED_LED_PIN,
	GREEN = GREEN_LED_PIN,
	BLUE = BLUE_LED_PIN,
	ALL_LEDS = 0,
}LED_t;

// Function:  initLED - Initializes an LED for control
//
// Input arguments:
//					myLED (LED_t): Color of LED to initialize. Options
//									can be any of those offered by LED_t
//									enum defined above.
//
void initLED(LED_t myLED);

// Function:  toggleLED - Toggles an LED's state
//
// Input arguments:
//					myLED (LED_t): Color of LED to toggle. Options
//									can be any of those offered by LED_t
//									enum defined above.
//
void toggleLED(LED_t myLED);

// Function:  LED_ON - Turns on an LED
//
// Input arguments:
//					myLED (LED_t): Color of LED to turn on. Options
//									can be any of those offered by LED_t
//									enum defined above.
//
void LED_ON(LED_t myLED);

// Function:  LED_OFF - Turns off an LED
//
// Input arguments:
//					myLED (LED_t): Color of LED to turn off. Options
//									can be any of those offered by LED_t
//									enum defined above.
//
void LED_OFF(LED_t myLED);

// Function:  LED_test - Turns all LEDs on and off to test
//							them. Sequence should be the
//							following:
//								1. Red LED ON for 500 ms
//								2. LEDs OFF for 100 ms
//								3. Green LED ON for 500 ms
//								4. LEDs OFF for 100 ms
//								5. Blue LED ON for 500 ms
//								6. LEDs OFF for 100 ms
//								7. All LEDs ON for 100 ms
//								8. LEDs OFF for 100 ms
//								9. All LEDs ON for 100 ms
//								10. LEDs OFF for 100 ms
//
void LED_test();

#endif /* LEDS_H_ */
