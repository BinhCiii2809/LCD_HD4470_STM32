#ifndef _MYGPIO_H_
#define _MYGPIO_H_

#include "main.h"
	//lights status
#define D_ON	 	GPIO_PIN_RESET
#define D_OFF 		GPIO_PIN_SET
	//lights list
#define D1 			50
#define D2 			51
	//--buttons list
#define P1			3
#define P2			4
#define P3			5
#define P4			6
	//buttons status
#define BUTTON_ACTIVE				GPIO_PIN_RESET	
#define BUTTON_INACTIVE				GPIO_PIN_SET
	//--swtich list
#define SW1			SW1_PIN
#define SW2			SW2_PIN
//#define SW3			SW3_PIN
	//switch status
#define SW1_ACTIVE					100	//right
#define SW2_ACTIVE					101	//center
//#define SW3_ACTIVE					102 //left

void Light_cmd(uint8_t d, GPIO_PinState status); //light status control with d: which lights? 
GPIO_PinState PushButton_read(uint8_t p); //FC return 0 or 1,p: which button?
uint8_t Switch_read(void);

#endif	//_MYGPIO_H_
