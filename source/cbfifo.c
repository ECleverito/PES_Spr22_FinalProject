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
// ********** 	File: cbfifo.c			**********
// ***********************************************
// Functions for initializing and interfacing with
// circular FIFO buffers, primarily for use with
// UART peripherals to add robustness
// ***********************************************
//NOTE: This source file contains "wrapped subtracts"
//		for calculating read/write position and CB
//		length based on Elicia White's algorithms
//		from the section titled "Circular Buffers"
//		in Chapter 6 of "Making Embedded Systems
//		Design Patterns for Great Software", 1st
//		 Edition, published by O'Reilly media.
//		Instances of these formulas will be preceded
//		by "White, Chp.6" to indicate this.

#ifndef _CBFIFO_H_
#include "cbfifo.h"
#endif

#include "MKL25Z4.h"
#include <stddef.h>
#include <stdint.h>

//Two cbfifo instances exist - one for the receiving operations
//and another for the transmission. The desired buffer
//for each cbfifo function is dictated by specifying the UART_buff_t
//enum argument when calling cbfifo functions
cbfifo_t RxBuff = { .read = 0, .write = 0, .isFull = 0 };
cbfifo_t TxBuff = { .read = 0, .write = 0, .isFull = 0 };

// Function:  cbfifo_printState - Prints out a formatted output of the contents of the
//									circular buffer FIFO
//
void cbfifo_printState();

size_t cbfifo_enqueue(UART0_buff_t UART0_buff, void *buf, size_t nbyte){
	
	cbfifo_t *target_cbfifo;

	//The specified buffer that
	//has been dictated will determine
	//the target cb fifo
	switch(UART0_buff){

	case RX_BUFF:
		target_cbfifo = &RxBuff;
		break;

	case TX_BUFF:
		target_cbfifo = &TxBuff;
		break;

	}

	uint32_t size = sizeof(target_cbfifo->list)/sizeof(target_cbfifo->list[0]);
	
	//If input buffer is a NULL pointer,
	//an error is returned
	if(buf == NULL)
		return (size_t)-1;
	
	//The interrupt state of the MCU is saved
	//before interrupts are disabled, then
	//interrupts are disabled to avoid a race
	//condition.
	uint32_t masking_state = __get_PRIMASK();
	__disable_irq();


	//User-specified number of bytes (nbytes)
	//are written to the CB or until it is full
	for(int i=0;i<nbyte;i++){
		
		//If CB is full, the number of write
		//operations that have occurred 
		//will indicate how many bytes were
		//written successfully to the CB
		if(target_cbfifo->isFull)
			return i;
		
		target_cbfifo->list[target_cbfifo->write] = *(uint8_t*)(buf+i);
		//White, Chp.6
		target_cbfifo->write = (target_cbfifo->write + 1) & (size - 1);
		
		//If the wrapped subtraction from cbfifo_length()
		//returns 0 after an enqueue, this indicates that
		//the CB is full.
		if(!cbfifo_length(UART0_buff))
			target_cbfifo->isFull = 1;

	}
	//Interrupt state is restored at the end
	__set_PRIMASK(masking_state);
	
	return nbyte;
}

size_t cbfifo_dequeue(UART0_buff_t UART0_buff, void *buf, size_t nbyte){
	
	cbfifo_t *target_cbfifo;

	switch(UART0_buff){

	case RX_BUFF:
		target_cbfifo = &RxBuff;
		break;

	case TX_BUFF:
		target_cbfifo = &TxBuff;
		break;

	}

	uint32_t size = sizeof(target_cbfifo->list)/sizeof(target_cbfifo->list[0]);
	
	//If input buffer is a NULL pointer,
	//an error is returned
	if( buf == NULL)
		return (size_t)-1;

	uint32_t masking_state = __get_PRIMASK();
	__disable_irq();

	//Check if CB is empty before attempting
	//to dequeue
	if(cbfifo_length(UART0_buff)==0 && !target_cbfifo->isFull)
		return 0;
	
	//User-specified number of bytes (nbytes)
	//are read from the CB or until it is empty
	for(int i=0;i<nbyte;i++){
		
		//Check isFull flag before
		//deciding if CB is empty
		if(target_cbfifo->isFull){
			target_cbfifo->isFull=0;
		}
		else{
			if(!cbfifo_length(UART0_buff))
				return i;
		}
		
		*(uint8_t*)(buf+i) = target_cbfifo->list[target_cbfifo->read];
		//White, Chp.6
		target_cbfifo->read = (target_cbfifo->read + 1) & (size - 1);
			
	}
	
	__set_PRIMASK(masking_state);

	return nbyte;

}

size_t cbfifo_length(UART0_buff_t UART0_buff){
	
	cbfifo_t *target_cbfifo;

	switch(UART0_buff){

	case RX_BUFF:
		target_cbfifo = &RxBuff;
		break;

	case TX_BUFF:
		target_cbfifo = &TxBuff;
		break;

	}

	uint32_t size = sizeof(target_cbfifo->list)/sizeof(target_cbfifo->list[0]);
	
	//If CB has been filled by enqueueing,
	//this flag will be set and will return
	//an accurate length
	if(target_cbfifo->isFull)
		return CB_SIZE;

	//White, Chp.6
	return ((target_cbfifo->write - target_cbfifo->read)
					& (size-1));
	
}

size_t cbfifo_capacity(UART0_buff_t UART0_buff){

	cbfifo_t *target_cbfifo;

	switch(UART0_buff){

	case RX_BUFF:
		target_cbfifo = &RxBuff;
		break;

	case TX_BUFF:
		target_cbfifo = &TxBuff;
		break;

	}

	return sizeof(target_cbfifo->list)/sizeof(target_cbfifo->list[0]);
	
}


void init_cbfifo(UART0_buff_t UART0_buff){
	
	cbfifo_t *target_cbfifo;

	switch(UART0_buff){

	case RX_BUFF:
		target_cbfifo = &RxBuff;
		break;

	case TX_BUFF:
		target_cbfifo = &TxBuff;
		break;

	}

	__builtin_memset(&target_cbfifo->list[0],0,(size_t)CB_SIZE);
	
}
