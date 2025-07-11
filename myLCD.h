#ifndef _MYLCD_H_
#define _MYLCD_H_

#include "main.h"
#include "string.h"
#include "stdio.h"
#include "string.h"

#define CMD_REG     0     				//REG RS-cmd,data of LCD
#define DATA_REG    1

void LCD_Write(uint8_t data);
void LCD_Send(uint8_t Reg, uint8_t data);
void LCD_Init();
void LCD_Clear();
void LCD_GotoXY(uint8_t x, uint8_t y); // select x: column(start:0) , y: row(0,1)
void LCD_PutString(char* s);
void LCD_PutChar(uint8_t ch);
void LCD_Command(uint8_t cmd); 
void LCD_PutNumber(int *number);
void LCD_PutNumber_Float(float *number);
void LCD_Clock(uint8_t *hours, uint8_t *minutes, uint8_t *second);
#endif	//_MYLCD_H_
