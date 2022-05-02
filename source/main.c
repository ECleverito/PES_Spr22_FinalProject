
#include "MKL25Z4.h"

#include "NEC_IR_receiver.h"

int main(void) {

	init();

    while(1){

    	listeningLoop();

    }

    return 0;

}


