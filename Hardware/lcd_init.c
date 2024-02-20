#include "lcd_init.h"


/*******************
hint template
ignore this block
********************/

/*******************
send any thing to st7789 by spi 
i.e. cmd, data...etc
********************/ 
void LCD_Writ_Bus(uint8_t dat) 
{	
	//LCD_CS_Clr();
	//cmd length -> 8byte
	for(uint8_t i=0;i<8;i++)
	{			  
		LCD_SCLK_Clr();
		if(dat&0x80)
		{
		   LCD_MOSI_Set();
		}
		else
		{
		   LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat <<= 1;
	}	
  //LCD_CS_Set();	
}

/*******************
write 1 byte data
********************/ 
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_CS_Clr();
	LCD_Writ_Bus(dat);
	LCD_CS_Set();
}

/*******************
write 2 byte data
********************/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_CS_Clr();
	//right shift 8 bits
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
	LCD_CS_Set();
}

/*******************
write cmd
********************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_CS_Clr();
	LCD_DC_Clr();//can find why at lcd_init.h
	LCD_Writ_Bus(dat);
	LCD_CS_Set();
	LCD_DC_Set();
}


/*******************
set screen addr
********************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	switch (USE_HORIZONTAL){
		case 0:
			LCD_WR_REG(0x2a);//set row addr
			LCD_WR_DATA(x1);
			LCD_WR_DATA(x2);
			LCD_WR_REG(0x2b);//set col addr
			LCD_WR_DATA(y1);
			LCD_WR_DATA(y2);
			LCD_WR_REG(0x2c);//write cmd into register
			break;
		
		case 1:
			LCD_WR_REG(0x2a);
			LCD_WR_DATA(x1);
			LCD_WR_DATA(x2);
			LCD_WR_REG(0x2b);
			LCD_WR_DATA(y1+80);
			LCD_WR_DATA(y2+80);
			LCD_WR_REG(0x2c);
			break;
		
		case 2:
			LCD_WR_REG(0x2a);
			LCD_WR_DATA(x1);
			LCD_WR_DATA(x2);
			LCD_WR_REG(0x2b);
			LCD_WR_DATA(y1);
			LCD_WR_DATA(y2);
			LCD_WR_REG(0x2c);
			break;
		
		default:
			LCD_WR_REG(0x2a);
			LCD_WR_DATA(x1+80);
			LCD_WR_DATA(x2+80);
			LCD_WR_REG(0x2b);
			LCD_WR_DATA(y1);
			LCD_WR_DATA(y2);
			LCD_WR_REG(0x2c);
			break;
	}
}

void LCD_Init(void)
{
	//reset st7789
	LCD_RES_Clr();
	HAL_Delay(50);
	LCD_RES_Set();
	HAL_Delay(50);
	
	//open back light 
	LCD_BLK_Set();
	HAL_Delay(50);
	
	LCD_CS_Clr();
	//disable sleep
	LCD_WR_REG(0x11);
	LCD_WR_REG(0x11);
	HAL_Delay(50);
	
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);
	switch(USE_HORIZONTAL){
		case 0:
			LCD_WR_DATA8(0x00);
			break;
		
		case 1:
			LCD_WR_DATA8(0xC0);
			break;
		
		case 2:
			LCD_WR_DATA8(0x70);
			break;
		
		default:
			LCD_WR_DATA8(0xA0);
			break;
	}
	
	LCD_WR_REG(0x3A); 
	LCD_WR_DATA8(0x55);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x2B);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x0F);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);
		
	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);
	
	LCD_WR_REG(0xD6);     
	LCD_WR_DATA8(0xA1); 
	
	
	LCD_WR_REG(0xE0);     
	LCD_WR_DATA8(0xF0);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x07);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x25);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x3C);   
	LCD_WR_DATA8(0x36);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x12);   
	LCD_WR_DATA8(0x29);   
	LCD_WR_DATA8(0x30); 

	LCD_WR_REG(0xE1);     
	LCD_WR_DATA8(0xF0);   
	LCD_WR_DATA8(0x02);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x21);   
	LCD_WR_DATA8(0x25);   
	LCD_WR_DATA8(0x32);   
	LCD_WR_DATA8(0x3B);   
	LCD_WR_DATA8(0x38);   
	LCD_WR_DATA8(0x12);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x27);   
	LCD_WR_DATA8(0x31);  

	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29); 
} 