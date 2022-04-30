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
// ********** 	File: UART.c			**********
// ***********************************************
// ***********************************************
// **********   	 ATTENTION	    	**********
// ***********************************************
// THE LAYOUT OF THIS UART INITILIZATION AND
// ISR CODE WAS HEAVILY ADAPTED FROM ALEXANDER
// DEAN'S EXAMPLES IN CHAPTER 8 OF "EMBEDDED SYSTEMS
// DESIGN FUNDAMENTALS WITH ARM CORTEX-M BASED
// MICROCONTROLLERS", 2017
// ***********************************************
// ***********************************************

#include "UART.h"

#include "MKL25Z4.h"
#include "cbfifo.h"

void UART0_init(){

	//Variable to calculate "Baud Rate Setting"
	//value for baud rate generator on UART0
	//peripheral
	uint16_t sbr;

	//Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Disable transmitter and receiver before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	//Set UART clock to 24 MHz FLL clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;

	//Set Port A pins to Rx and Tx, respectively
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);

	//Set BR and oversampling rate based on defined preprocessor
	//values available for custom settings in UART.h
	sbr = (uint16_t)((UART_FLL_CLOCK)/(BAUD_RATE * OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(OVERSAMPLE_RATE-1);

	//Disable interrupts for Rx active edge and LIN break detect, select
	//two stop bits
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0);

	//Don't enable loopback mode, use 8 data bit mode, dont use parity bit
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);

	//Don't invert transmit data, do enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(1) | UART0_C3_NEIE(1)
			| UART0_C3_FEIE(1) | UART0_C3_PEIE(1);

	//Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	//Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	//Enable UART0 interrupts
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
	UART0->C2 |= UART_C2_RIE(1);

	//Enable UART transmitter and receiver
	UART0->C2 |= UART0_C2_TE(1) | UART0_C2_RE(1);

}

void UART0_IRQHandler(){

	//Variable for holding value received from UART0
	//or value to write to UART0
	uint8_t ch;

	//Check for errors in status register
	if(UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK |
			UART_S1_FE_MASK | UART_S1_PF_MASK)) {

		//Reset error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
				UART0_S1_FE_MASK | UART0_S1_PF_MASK;

		ch = UART0->D;
	}
	if(UART0->S1 & UART_S1_RDRF_MASK){
		//Character received
		ch = UART0->D;
		//Check if there is room in the receive buffer
		if(!(cbfifo_length(RX_BUFF) == cbfifo_capacity(RX_BUFF)))
			cbfifo_enqueue(RX_BUFF,&ch,1);
		else {
			//discard character - buffer is full!

		}
	}
	//Check if transmitter interrupts enabled and if
	//register is empty/ready for transmission
	if((UART0->C2 & UART0_C2_TIE_MASK) &&
			(UART0->S1 & UART0_S1_TDRE_MASK) ){

		//If there are bytes in the transmit
		//buffer, send them
		if(cbfifo_length(TX_BUFF)>0){
			cbfifo_dequeue(TX_BUFF,&ch,1);
			UART0->D = ch;
		}
		else{

			//If not, disable tx interrupts
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}

	}

}

//Redlib I/O write handler
int __sys_write(int handle, char *buf, int size){

	//Wait until there is enough room for the desired bytes to be written
	//in the transmit buffer
	 while(cbfifo_length(TX_BUFF) > (cbfifo_capacity(TX_BUFF)-size))
		 ;

	 cbfifo_enqueue(TX_BUFF, buf, size);

	 //Enable transmit interrupts
	 if(!(UART0->C2 & UART0_C2_TIE_MASK)){
		 UART0->C2 |= UART0_C2_TIE(1);
	 }

	 return 0;

	 //When should -1 be returned??

}

int __sys_readc(void){

	uint8_t c;

	//Wait until bytes in receive buffer
	while(cbfifo_length(RX_BUFF)==0)
		  ;

	cbfifo_dequeue(RX_BUFF,&c,1);

	return c;

}
