
#include "MKL25Z4.h"

#include "stdio.h"

#include "UART.h"
#include "sysclock.h"

int main(void) {

  	sysclock_init();
  	UART0_init();

  	printf("Hello world\n");

    while(1)
    	;
    return 0;

}
