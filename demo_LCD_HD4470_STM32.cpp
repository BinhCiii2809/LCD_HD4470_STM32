/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include "myGPIO.h"
#include "myLCD.h"
/* USER CODE END Includes */
//--------------------------
/* USER CODE BEGIN PV */
uint8_t D1_Val=0, 	P1State=BUTTON_INACTIVE, 
					P2State=BUTTON_INACTIVE, 
					P3State=BUTTON_INACTIVE, 
					P4State=BUTTON_INACTIVE, flag=0;
int num= 12345;
uint8_t hh=12,mm=00,ss=00;
int led_blink= NO_MODE;
long long lastToggle, lastButton=0, lastCurrent=0, lastBlink;
int sp=0;
int tick=5;
//---------------------
void update_clock(){
	if(HAL_GetTick()- lastCurrent >1000){
		ss++;
		if(ss>=60){
			ss=0;
			mm++;			
		}
		if(mm>=60){
			mm=0;
			hh++;
		}
		if(hh>=24)
			hh=0;
		lastCurrent= HAL_GetTick();	
		
	}
}
//-----------------------
void bai2_LCD(){
	LCD_GotoXY(0,0);
	LCD_PutString("CLOCK:");
	LCD_GotoXY(6,0);
	LCD_Clock(&hh,&mm,&ss);
	update_clock();
}
//------------------------------
void bai3_LCD(){
	//read button
	uint8_t curP1State= PushButton_read(P1);
	uint8_t curP2State= PushButton_read(P2);
	uint8_t curP3State= PushButton_read(P3);
	uint8_t curP4State= PushButton_read(P4);
	if (curP1State == BUTTON_ACTIVE && P1State == BUTTON_INACTIVE){
		P1State = BUTTON_ACTIVE;
		sp++;
	}
	else if(curP1State == BUTTON_INACTIVE && P1State == BUTTON_ACTIVE){
		P1State = BUTTON_INACTIVE;
	}
	
	if (curP2State == BUTTON_ACTIVE && P2State == BUTTON_INACTIVE){
		P2State = BUTTON_ACTIVE;
		sp--;
	}
	else if(curP2State == BUTTON_INACTIVE && P2State == BUTTON_ACTIVE){
		P2State = BUTTON_INACTIVE;
	}	
	
	if (curP3State == BUTTON_ACTIVE && P3State == BUTTON_INACTIVE){
		P3State = BUTTON_ACTIVE;
	}
	else if(curP3State == BUTTON_INACTIVE && P3State == BUTTON_ACTIVE){
		P3State = BUTTON_INACTIVE;
		flag=1;
		lastCurrent= HAL_GetTick();
	}
	
	if (curP4State == BUTTON_ACTIVE && P4State == BUTTON_INACTIVE){
		P4State = BUTTON_ACTIVE;
		flag=0;
	}
	else if(curP4State == BUTTON_INACTIVE && P4State == BUTTON_ACTIVE){
		P4State = BUTTON_INACTIVE;
	}
	//---------
	if(sp <0) sp=0;
	if(flag==1){
		if(HAL_GetTick() - lastCurrent >1000){
			sp++;
			lastCurrent= HAL_GetTick();
		}
	}
	//Init
	LCD_GotoXY(0,0);
	LCD_PutString("San pham:");
	LCD_GotoXY(9,0);
	LCD_PutNumber(&sp);
}
//----------------------
void bai4_LCD(){
	//read button
	uint8_t curP1State= PushButton_read(P1);
	uint8_t curP2State= PushButton_read(P2);
	uint8_t curP3State= PushButton_read(P3);
	uint8_t curP4State= PushButton_read(P4);
	if (curP1State == BUTTON_ACTIVE && P1State == BUTTON_INACTIVE){
		P1State = BUTTON_ACTIVE;
		lastCurrent=HAL_GetTick();
		flag^=1;
	}
	else if(curP1State == BUTTON_INACTIVE && P1State == BUTTON_ACTIVE){
		P1State = BUTTON_INACTIVE;
	}
	
	if (curP2State == BUTTON_ACTIVE && P2State == BUTTON_INACTIVE){
		P2State = BUTTON_ACTIVE;
		hh++;
		if(hh>=24) hh=0;
	}
	else if(curP2State == BUTTON_INACTIVE && P2State == BUTTON_ACTIVE){
		P2State = BUTTON_INACTIVE;
	}	
	
	if (curP3State == BUTTON_ACTIVE && P3State == BUTTON_INACTIVE){
		P3State = BUTTON_ACTIVE;
		mm++;
		if(mm>=60) mm=0;
	}
	else if(curP3State == BUTTON_INACTIVE && P3State == BUTTON_ACTIVE){
		P3State = BUTTON_INACTIVE;
		
	}
	
	if (curP4State == BUTTON_ACTIVE && P4State == BUTTON_INACTIVE){
		P4State = BUTTON_ACTIVE;
		ss++;
		if(ss>=60) ss=0;
	}
	else if(curP4State == BUTTON_INACTIVE && P4State == BUTTON_ACTIVE){
		P4State = BUTTON_INACTIVE;
	}
	
	if(flag) update_clock();
	//Init
	LCD_GotoXY(0,0);
	LCD_Clock(&hh,&mm,&ss);
}

/* USER CODE END PV */
int main(void){
	/* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(LCDLED_GPIO_Port, LCDLED_Pin, GPIO_PIN_SET); //enable LED of LCD
	LCD_Init();
	LCD_Clear();
	/* USER CODE END 2 */
	
}
