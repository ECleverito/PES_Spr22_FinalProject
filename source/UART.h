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
// ********** 	File: UART.h			**********
// ***********************************************
// Code for initializing and interfacing with UART0
// and linking it via redlib to stdio functions
// ***********************************************

#ifndef UART_H_
#define UART_H_

//NOTE: THESE VALUES CAN BE MODIFIED FOR CUSTOM
//SERIAL CONNECTION SETTINGS
#define BAUD_RATE		115200
#define DATA_BITS_SIZE	8
#define PARITY_SWITCH	0
#define STOP_BITS_SIZE	2

#define OVERSAMPLE_RATE 16

//This frequency is set in sysclock.c
#define UART_FLL_CLOCK (24e6)

void UART0_init();

int __sys_write(int handle, char *buf, int size);

int __sys_readc(void);

int userInputCheck();

#endif /* UART_H_ */
