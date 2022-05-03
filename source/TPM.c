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
// **********	  File: TPM.c			**********
// ***********************************************
// Code for initializing TPM0 for use in timing
// duration of IR signal components for use in
// decoding
// ***********************************************

#include "MKL25Z4.h"

#include "TPM.h"

void TPM0_init(){

	//Send clock
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//48 MHz clock select and PLL
	//(PLL selection config. performed
	//in UART_init() in UART.c prior)
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

	//Prescaler value of 4 in order to fit
	//max. pulse length of 9 ms used in NEC
	//IR encoding in CNT.
	TPM0->SC = TPM_SC_PS(0b010);

	//Use while in debug mode
	TPM0->CONF = TPM_CONF_DBGMODE(3);

	//Reset CNT initially and
	//set MOD to max value to
	//allow detection of NEC
	//leader code.
	TPM0->CNT = 0;
	TPM0->MOD = 0xFFFF;

	//Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}
