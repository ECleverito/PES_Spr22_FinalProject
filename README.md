# PES_Spr22_FinalProject #

My final project for the Spring 2022 section of Principles of Embedded Systems, taught by Howdy Pierce at CU Boulder, was an interrupt-based IR Receiver with a UART user interface for adding new IR codes to its registry and assigning GPIO toggling functions to new codes. The IR receiver works with the NEC pulse duration-encoded scheme, which is very common in consumer remotes.

## Hardware ##
Vishay 1838 IR Receiver Module
NXP FRDM KL25Z development board
  Signal pin (1) connected to PTA3
  
 ![hw_setup](https://user-images.githubusercontent.com/16659086/166406644-9b3e41e8-62d3-402a-ab95-eebd68823acd.jpg)
 
## SW Overview ##
PTA3 is configured as an input pin to generate interrupts on every edge detected. Remote control IR signals operate at 38 kHz typically, and the NEC protocol uses the following timing:

![image](https://user-images.githubusercontent.com/16659086/166406891-b998c2fb-825a-4eb7-8cdc-28b7ae3b164d.png)

Each interrupt from PTA3 examines the current value held in TPM0's CNT register, which is reset on every interrupt. In this manner, the duration of every pulse can be measured. The "Leader Code" above can be ignored, and the different durations of 0's and 1's shown above (1's period = 2.25 ms w/ 25% duty cycle, 0's period = 1.125 ms w/ 50% duty cycle) can be used to decode the signals.

UART interrupts are also running in order for the system to serve as a command processor to allow a user to add new codes and to assign "tasks" to each code. The code base contains four built-in tasks that can be assigned to codes in oder to demonstrate the ability to link any NEC-protocl IR code to GPIO. They are the following tasks:
  -Toggle the onboard Red LED
  -Toggle the onboard Green LED
  -Toggle the onboard Blue LED
  -Turn off all of the onboard LEDs

Additional IR tasks can be added by creating a task handler prototype, adding its description and its handler to the table below, and then defining the actual handler code later on in the file NEC_IR_receiver.c:

![image](https://user-images.githubusercontent.com/16659086/166407282-b77f4ebe-c913-4b50-93d8-0c3f77a2fa4f.png)

The commands available in the case-insensitive command processor are the following:
	list - Lists the contents of the IR code registry
  add - Adds a new IR code and assigns a function
  help - Display this list of available commands

Additional commands may be added in a similar fashion as above in the following section in NEC_IR_receiver.c:

![image](https://user-images.githubusercontent.com/16659086/166407405-9e86ec22-6004-47f4-a2af-4c56639445b9.png)

###UART Settings###
The current codebase UART settings are the following:
  BR: 115200 bps
  Data bits: 8
  Stop bits: 2
  Parity: None
  
These parameters can be changed by editing the file UART.h:

![image](https://user-images.githubusercontent.com/16659086/166407527-d49d8478-ff60-4934-a119-59c2d25768a3.png)

## Demonstration Video ##

https://youtu.be/qNLaBptfRu0




