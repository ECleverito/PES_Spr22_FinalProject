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
// **********  File: IR_pin.h			**********
// ***********************************************
// Code for initialization of the pin on which
// the IR sensor is connected (PORT A, 3) as well
// as the interrupt routine
// ***********************************************

#ifndef IR_PIN_H_
#define IR_PIN_H_

#define IR_PIN	3

//Values representing thresholds
//for determining contents of received
//IR data based on the values in TPM0 CNT.
//
//NEC is a common IR transmission protocol
//that uses "pulse distance encoding":
//
//		1 = 2.25 ms period with 25% duty cycle
//		0 = 1.125 ms period with 50% duty cycle
//
//Prior to the data bits, "leader code" is always
//sent with much longer duration (9 ms & 4.5 ms)
//than the data bits, therefore those pulses
//are easily distinguishable.
//
//These duration values were calculated using
//the following method:
//
//		sysclock configured for 24MHz
//		TPM0 configured with prescaler 4
//
//		1/((24 MHz)*4) = 166 ns/TPM0 tick
//
//		Min. leader code duration = 4.5 ms
//
//				4.5 ms / 166 ns > 20,000 ticks
//
//		'1' encoding duration => (2.25 ms * .75 off duty cycle)/(166ns)
//									= 10,000 ticks
//
//		'0' encoding duration => (1.125 ms * .5 duty cycle)
//									= 3,375 ticks
//
//By knowing that anything with a pulse longer than 20,000 ticks but
//not long enough to trigger an overflow on TPM0 is leader code, a new
//message can be detected.
//
//Anything longer thatn 3,375 ticks indicates a '1'.
//
#define LEADER_CODE_DURATION (20000)
#define ONE_DURATION 		 (7000)

void IR_pin_init();

#endif /* IR_PIN_H_ */
