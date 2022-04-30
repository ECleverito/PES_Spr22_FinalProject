// ***********************************************
// ***********************************************
// **********	PES Spring 2022			**********
// **********	Assignment 6			**********
// **********	By: Erich Clever		**********
// **********	Date: April 6, 2022		**********
// **********Instructor: Howdy Pierce	**********
// ***********************************************
// **********	Version: 1.0			**********
// **********	Tools used: MCUXpresso	**********
// ***********************************************
// ***********************************************
// ********** 	File: cbfifo.h			**********
// ***********************************************
// ***********************************************

#ifndef _CBFIFO_H_
#define _CBFIFO_H_

#include <stdint.h>  // for size_t

//The size of the UART buffers
//is defined here
#define	CB_SIZE	256

//Enum used for selecting between
//the two buffers when using cbfifo
//functions
typedef enum{

	RX_BUFF,
	TX_BUFF

}UART0_buff_t;

// Struct:  cbfifo_t - Circular FIFO buffer of fixed size in which size
//						refers to number of bytes held
//
// Members: list[] (uint8_t) - Array of bytes
//			  read (uint32_t) - Index of next byte to be output
//			  write (uint32_t) - Index of destination for next byte input
//			  isFull (uint8_t) - Flag to indicate if CB is full
//
typedef struct{

	uint8_t list[CB_SIZE];
	uint32_t read,write;
	uint8_t isFull;

}cbfifo_t;

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 * 
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns (size_t) -1.
 */
size_t cbfifo_enqueue(UART0_buff_t UART0_buff, void *buf, size_t nbyte);


/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 * 
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte. 
 * 
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
size_t cbfifo_dequeue(UART0_buff_t UART0_buff, void *buf, size_t nbyte);


/*
 * Returns the number of bytes currently on the FIFO. 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(UART0_buff_t UART0_buff);


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity(UART0_buff_t UART0_buff);

void init_cbfifo(UART0_buff_t UART0_buff);

#endif // _CBFIFO_H_
