#include "lcd.h"
#include "lcd_init.h"

void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{          
	//set area which you want to fill 
	LCD_Address_Set(xsta, ysta, xend-1, yend-1);
	for(uint16_t i = ysta;i < yend;i ++)
	{													   	 	
		for(uint16_t j = xsta;j < xend;j ++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
}

void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[])
{
	uint32_t k = 0;
	LCD_Address_Set(x, y, x+length-1, y+width-1);
	for(uint16_t i = 0;i < length;i ++)
	{
		for(uint16_t j = 0;j < width; j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}			
}