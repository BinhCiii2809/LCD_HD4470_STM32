#include "myGPIO.h"
void Light_cmd(uint8_t d, GPIO_PinState status){
	switch(d){
		case 50:
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, status);
			break;
		case 51:
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, status);
			break;
	}
}
GPIO_PinState PushButton_read(uint8_t p){
	switch(p){
		case 3:
			return HAL_GPIO_ReadPin(P1_GPIO_Port,P1_Pin);
		case 4:
			return HAL_GPIO_ReadPin(P2_GPIO_Port,P2_Pin);
		case 5:
			return HAL_GPIO_ReadPin(P3_GPIO_Port,P3_Pin);
		case 6:
			return HAL_GPIO_ReadPin(P4_GPIO_Port,P4_Pin);
	}
}

uint8_t Switch_read(void){
	if (!(HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin))) 	return 100;
	else if(!(HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin))) return 101;
//	else if(!(HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin))) return 102;
	return -1;
}
