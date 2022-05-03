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
// **********  File: NEC_IR_receiver.h	**********
// ***********************************************
// Main loop, command processor, IR code processing
// and registry, and handler code for both
// processors. Additional commands and functions
// available for linking with IR codes can
// be added here.
// ***********************************************

#ifndef NEC_IR_RECEIVER_H_
#define NEC_IR_RECEIVER_H_

//Smaller registry size used in debug
//mode for testing edge cases when
//registry is full
#ifdef	DEBUG
#define IR_REGISTRY_SIZE (4u)
#else
#define IR_REGISTRY_SIZE (20u)
#endif
#define CMD_STR_BUFFER_SIZE (64u)

#include <stdint.h>

// Function:  listeningLoop - Loop that checks flags updated by UART and
//								PORT A (IR signal on pin 3) and executes
//								corresponding commands
//
void listeningLoop();

// Function:  processIR - Registry is searched for received IR data word
//							and if a match is found, corresponding task
//							handler is called
//
// Inputs: IR_data (uint32_t) - NEC protocol-encoded word of data
//
void processIR(uint32_t IR_data);

// Function:  processCommand - User input is tokenized and if a match is found
//								in the command table, the corresponding handler
//								is called.
//
//								Commands currently available:
//									list - Lists the contents of the IR code registry
//  								 add - Adds a new IR code and assigns a function
//  								help - Display this list of available commands
//
//								Additional commands can be added in NEC_IR_receiver.c
//								file at the seciton labeled "COMMAND PROCESSOR UTILITIES".
//								More details on that process are included there.
//
void processCommand();

// Function:  init - Peripherals used by the IR receiverare initialized
//
void init();

#endif /* NEC_IR_RECEIVER_H_ */
