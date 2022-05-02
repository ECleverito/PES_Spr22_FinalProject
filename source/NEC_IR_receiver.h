/*
 * NEC_IR_receiver.h
 *
 *  Created on: May 2, 2022
 *      Author: erich
 */

#ifndef NEC_IR_RECEIVER_H_
#define NEC_IR_RECEIVER_H_

#ifdef	DEBUG
#define IR_CODE_BUFFER_SIZE (4u)
#else
#define IR_CODE_BUFFER_SIZE (20u)
#endif
#define CMD_STR_BUFFER_SIZE (64u)

typedef enum{

	LISTENING,
	NEW_CODE,

}receiver_state_t;

void listeningLoop();

void processCommand();

void init();

#endif /* NEC_IR_RECEIVER_H_ */
