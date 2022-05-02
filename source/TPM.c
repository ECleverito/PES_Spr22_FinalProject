/*
 * TPM.c
 *
 *  Created on: May 1, 2022
 *      Author: erich
 */

#include "MKL25Z4.h"

#include "TPM.h"

void TPM0_init(){

	//Send clock
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//48 MHz clock select and PLL
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
//	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	//Prescaler value of 4 in order to fit
	//max. pulse length of 9 ms used in NEC
	//IR encoding in CNT.
	TPM0->SC = TPM_SC_PS(0b010);

	//Use while in debug mode
	TPM0->CONF = TPM_CONF_DBGMODE(3);

	TPM0->CNT = 0;
	TPM0->MOD = 0xFFFF;

	//Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}
