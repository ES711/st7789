#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "main.h"
/*
0, 1 -> vertical
2, 3 -> horizontal
*/
#define USE_HORIZONTAL 0

/*
lcd screen width and height
*/
#define LCD_W 240
#define LCD_H 240

/*
spi software simulate
*/
#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOB, SCL_Pin, GPIO_PIN_RESET)
#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOB, SCL_Pin, GPIO_PIN_SET)

//DIN = MOSI
#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOB, MOSI_Pin, GPIO_PIN_RESET)
#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOB, MOSI_Pin, GPIO_PIN_SET)

#define LCD_RES_Clr() HAL_GPIO_WritePin(GPIOD, RES_Pin, GPIO_PIN_RESET)
#define LCD_RES_Set() HAL_GPIO_WritePin(GPIOD, RES_Pin, GPIO_PIN_SET)

/*
DC -> receive data or cmd
0 -> cmd
1 -> data
*/
#define LCD_DC_Clr() HAL_GPIO_WritePin(GPIOB, DC_Pin,GPIO_PIN_RESET)
#define LCD_DC_Set() HAL_GPIO_WritePin(GPIOB, DC_Pin, GPIO_PIN_SET)
 		     
#define LCD_CS_Clr() HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_Set() HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr() HAL_GPIO_WritePin(GPIOD, BLK_Pin, GPIO_PIN_RESET)
#define LCD_BLK_Set() HAL_GPIO_WritePin(GPIOD, BLK_Pin, GPIO_PIN_SET)


void LCD_Writ_Bus(uint8_t dat);//simulate spi
void LCD_WR_DATA8(uint8_t dat);//write 1 byte
void LCD_WR_DATA(uint16_t dat);//write 2 byte 
void LCD_WR_REG(uint8_t dat);//write cmd 
//set coordinate
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
//init lcd 
void LCD_Init(void);

#endif