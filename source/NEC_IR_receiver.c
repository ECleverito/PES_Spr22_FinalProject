/*
 * NEC_IR_receiver.c
 *
 *  Created on: May 2, 2022
 *      Author: erich
 */

#include "NEC_IR_receiver.h"

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#include "UART.h"
#include "LEDs.h"
#include "IR_pin.h"
#include "sysclock.h"

//Command handler function pointer type definition
typedef void (*command_handler_t)(int, char *argv[]);

//Struct for adding new commands to the command processor
typedef struct {
  const char *name;
  command_handler_t handler;
} command_table_t;

//Command handler prototypes
void handle_list(int argc, char *argv[]);

void handle_add(int argc, char *argv[]);
//ADD NEW COMMAND HANDLERS ABOVE THIS LINE

//Table where new commands are added
//NOTE: ADD NEW COMMANDS TO THE ARRAY BELOW
//		FOLLOWING THIS FORMAT:
//
//			-1st field: NAME
//				This is the name that will
//				be entered at the command
//				prompt for invoking the
//				associated command. It
//		`		is case-insensitive.
//
//			-2nd field: HANDLER
//				Associated command handler
//				goes in this field after
//				adding its prototype
//				to the section directly above
//
static const command_table_t commands[] = {
		{
				"list",
				handle_list

		},
		{
				"add",
				handle_add

		}
};

//Number of commands determined for cycling
//through them during command processing
static const int num_commands =
  sizeof(commands) / sizeof(command_table_t);

char cmdStr[CMD_STR_BUFFER_SIZE];

//IR task framework definition
typedef void (*IR_task_handler_t)();

//Struct for assigning GPIO tasks to the stored IR commands
typedef struct {
  const char *description;
  IR_task_handler_t handler;
}IR_task_table_t;

void handle_IR_code_1();
void handle_IR_code_2();
void handle_IR_code_3();

static const IR_task_table_t IR_tasks[] = {
		{
				"Toggle onboard red LED",
				handle_IR_code_1

		},
		{
				"Toggle onboard green LED",
				handle_IR_code_2

		},
		{
				"Toggle onboard blue LED",
				handle_IR_code_3

		}
};

typedef struct {
	uint32_t IR_code;
	IR_task_handler_t handler;
	char func_description[64];
}IR_linkedCode_table_t;

IR_linkedCode_table_t myCodes[IR_CODE_BUFFER_SIZE];
uint8_t numCodesAdded = 0;

//Globals from IR interrupt routine
extern bool newIRMessage;
extern bool IR_bit_Zero_Flag;
extern bool IR_bit_One_Flag;

void listeningLoop(){

	//Zero command string buffer
	__builtin_memset(cmdStr,0,CMD_STR_BUFFER_SIZE);

	//Signal to user that the processor is
	//awaiting a command
	printf("? ");

	//User UART0 input variables
	int i = 0;
	char c = 0;

	//IR interrupt data variables
	uint32_t IR_data = 0;
	uint8_t IR_data_bit = 0;

	while(1){

		if(userInputCheck()){
			c = getchar();
			*(cmdStr+i) = c;
			putchar(c);
			i++;
		}

		if(c == '\r'){
			printf("\n\r");
			*(cmdStr+i-1) = '\0';
			processCommand();
			return;
		}

    	if(newIRMessage)
    	{
			IR_data = 0;
			IR_data_bit = 0;
			newIRMessage = false;

    	}

    	if(IR_bit_Zero_Flag){

    		IR_data &= ~(1 << (31-IR_data_bit));
    		IR_bit_Zero_Flag=0;
    		IR_data_bit++;

    	}

    	if(IR_bit_One_Flag){

    		IR_data |= (1 << (31-IR_data_bit));
    		IR_bit_One_Flag=0;
    		IR_data_bit++;

    	}

		if(IR_data_bit >= 32){
    		processIR(IR_data);
    		printf("\n\r");
    		return;

		}
	}

}

void processIR(uint32_t IR_data){

	//Disable IR interrupts

	for(int i=0;i<numCodesAdded;i++){

		if(IR_data == myCodes[i].IR_code){
			myCodes[i].handler();
			return;
		}

	}
	printf("This code has not been added to the registry yet.\n\n\r");

}

void processCommand()
{
  char *p = cmdStr;
  char *end;
  // find end of string
  for (end = cmdStr; *end != '\0'; end++)
    ;
  // Tokenize input in place
  bool in_token = false;
  char *argv[10];
  int argc = 0;
  __builtin_memset(argv, 0, sizeof(argv));

  for (p = cmdStr; p < end; p++) {

	  //Iterate through leading whitespaces
	  if(*p == ' '){

		  //If token was being read
		  //and whitespace detected,
		  //then this signals the
		  //end of the current argument
		  if(in_token){
			  argc++;
			  in_token = false;
			  *p = '\0';
		  }
		  continue;

	  }

	  //If it is the first time that
	  //a whitespace has been detected
	  //outside of a token, the token
	  //begins to be formed
	  if(!in_token)
	  {
		  argv[argc] = p;
		  in_token = true;
	  }

  }

  if(in_token)
	  argc++;

  argv[argc] = NULL;
  if (argc == 0)   // no command
    return;

  //After tokenization, the first argument is compared
  //to all of the command names in a case-insensitive manner
  for (int i=0; i < num_commands; i++) {
	  if (strcasecmp(argv[0], commands[i].name) == 0) {
		  commands[i].handler(argc, argv);
		  break;
	  }
	  else if(i==(num_commands-1)){
		  //If no commands are matched, the user is informed
		  printf("Unknown command: %s\r\n",argv[0]);

	  }

  }


}

void handle_list(int argc, char *argv[]){



	printf("\r\n%d codes out of %d have been added to the system:\n\n\r",
			numCodesAdded,IR_CODE_BUFFER_SIZE);

	for(int i=0; i<numCodesAdded; i++){

		printf("\t%d - %X - %s\n\r",i+1,myCodes[i].IR_code,myCodes[i].func_description);

	}

	printf("\r\n");

}

void handle_add(int argc, char *argv[]){

	if( numCodesAdded == IR_CODE_BUFFER_SIZE ){

		printf("\n\rIR code buffer is full. Reset to clear the buffer to add more.\n\n\r");
		return;

	}

	printf("\r\nSend the IR message that you would like to link.\n\n\r");
	printf("Waiting...\r\n");

	uint32_t IR_data = 0;
	uint8_t IR_data_bit = 0;

	bool messageFound = false;

	while(!messageFound){
		if(newIRMessage)
		{
			IR_data = 0;
			IR_data_bit = 0;
			newIRMessage = false;

		}

		if(IR_bit_Zero_Flag){

			IR_data &= ~(1 << (31-IR_data_bit));
			IR_bit_Zero_Flag=0;
			IR_data_bit++;

		}

		if(IR_bit_One_Flag){

			IR_data |= (1 << (31-IR_data_bit));
			IR_bit_One_Flag=0;
			IR_data_bit++;

		}

		if(IR_data_bit >= 32){
			messageFound = true;
			IR_data_bit = 0;
			//Disable IR interrupts here

			printf("\r\nCode received: %X\n\n\r",IR_data);
			myCodes[numCodesAdded].IR_code = IR_data;

			printf("Assign a function to this code from the following list:\n\n\r");

			for(int i=0; i<(sizeof(IR_tasks)/sizeof(IR_tasks[0])); i++){

				printf("\t%d - %s\n\r",i+1,IR_tasks[i].description);

			}

			int validSelection=0;
			char c = 0;
			uint8_t c_int = 255;

			while(!validSelection){

				c = getchar();
				c_int = c - 49;

				if( c_int >= 0 && c_int <= 2 )
					validSelection=1;
				else
					printf("Please enter a valid option from the list displayed earlier.\n\n\r");

			}

			myCodes[numCodesAdded].handler = IR_tasks[c_int].handler;
			sprintf(myCodes[numCodesAdded].func_description,IR_tasks[c_int].description,
					strlen(IR_tasks[c_int].description));

			numCodesAdded++;

			handle_list(0,0);

		}
	}

}

void init(){

  	sysclock_init();
  	UART0_init();
  	initLED(ALL_LEDS);
  	LED_OFF(ALL_LEDS);
  	IR_pin_init();

  	char introString[] = "********************************************************************************\n\r"
  						 "\t\t\tIR Universal Receiver\n\r"
				 	 	 "********************************************************************************\n\r"
  						 "\n\r"
  						 "Available commands (case insensitive):\n\n\r"
  						          "\tlist - Lists the codes that have been received\n\r"
  								  "\t add - Adds a new code and assigns a function\n\r"
  						 "\n\r";

  	int i = 0;
  	while( introString[i++] != '\0' )
  		putchar(introString[i]);

}

void handle_IR_code_1(){

	toggleLED(RED);

}

void handle_IR_code_2(){

	toggleLED(GREEN);

}

void handle_IR_code_3(){

	toggleLED(BLUE);

}
