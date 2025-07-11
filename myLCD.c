#include "myLCD.h"

void LCD_Write(uint8_t data)							//Declare LCD data pins
{
	HAL_GPIO_WritePin(LCDD4_GPIO_Port, LCDD4_Pin, (GPIO_PinState)((data >> 0) & 0x01));
	HAL_GPIO_WritePin(LCDD5_GPIO_Port, LCDD5_Pin, (GPIO_PinState)((data >> 1) & 0x01));
	HAL_GPIO_WritePin(LCDD6_GPIO_Port, LCDD6_Pin, (GPIO_PinState)((data >> 2) & 0x01));
	HAL_GPIO_WritePin(LCDD7_GPIO_Port, LCDD7_Pin, (GPIO_PinState)((data >> 3) & 0x01));
  
	HAL_GPIO_WritePin(LCDE_GPIO_Port,LCDE_Pin, GPIO_PIN_SET );								//Activate E pin, then toggle to trigger LCD latch
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCDE_GPIO_Port,LCDE_Pin, GPIO_PIN_RESET);
}
void LCD_Send(uint8_t Reg, uint8_t data)
{
	if (Reg==0) HAL_GPIO_WritePin(LCDRS_GPIO_Port, LCDRS_Pin, (GPIO_PinState)(CMD_REG)); 
	else HAL_GPIO_WritePin(LCDRS_GPIO_Port, LCDRS_Pin, (GPIO_PinState)(DATA_REG)); 
	LCD_Write(data >> 4);												//4bit HIGH
	LCD_Write(data);
}

void LCD_Command(uint8_t cmd){
	LCD_Send(CMD_REG, cmd); 
}

void LCD_Init()
{
	HAL_GPIO_WritePin(LCDRW_GPIO_Port, LCDRW_Pin, (GPIO_PinState)(CMD_REG));    // select mode: WRITE
		
	LCD_Send(CMD_REG, 0x33);                  	 //check FC
	LCD_Send(CMD_REG, 0x32);                 		// initialization 8bit -> 4bit
	LCD_Send(CMD_REG, 0x28);                   // function set: 4 bit, 2 row, 5x8
	LCD_Send(CMD_REG, 0x0C);                  // display and points off	
	LCD_Send(CMD_REG, 0x06);                 	// entry mode set
}
void LCD_Clear()                                //clear
{
	LCD_Send(CMD_REG, 0x01);
}

void LCD_GotoXY(uint8_t x, uint8_t y)         // select x: column(end: 15) , y: row
{	//Set DDRAM address
  if(y == 0)
	  LCD_Send(CMD_REG, 0x80 + x);								// first address
  else if(y == 1)
	  LCD_Send(CMD_REG, 0xC0 + x);
	
}

void LCD_PutChar(uint8_t ch)              // write char
{	
		LCD_Send(DATA_REG, ch);

}

void LCD_PutString(char* s)              // write string
{
	for(uint8_t i = 0; i < strlen(s); i++)
	{
		LCD_Send(DATA_REG, s[i]);
	}
}

void LCD_PutNumber(int *number)                 
{
	char num[100];
	sprintf(num, "%d", *number);
	LCD_PutString(num);
}

void LCD_PutNumber_Float(float *number)                 
{
	char num[100];
	sprintf(num, "%g", *number);
	LCD_PutString(num);
}

void LCD_Clock(uint8_t *hours, uint8_t *minutes, uint8_t *second){
	
	char clock[9];
	sprintf(clock, "%02d:%02d:%02d", *hours, *minutes, *second);
	LCD_PutString(clock);
}
