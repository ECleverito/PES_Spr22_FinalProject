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
// **********  File: TPM.h				**********
// ***********************************************
// Code for initializing TPM0 for use in timing
// duration of IR signal components for use in
// decoding
// ***********************************************

#ifndef TPM_H_
#define TPM_H_

//Initialize TPM0 for following config:
//
//		-24 MHz source clock and prescaler of 4 (~166 ns tick)
//		-Overflows at 10 ms (longer than any of NEC leader codes, so this
//			indicates a new message. Gaps between IR packets is ~60 ms)
//
void TPM0_init();

#endif /* TPM_H_ */
