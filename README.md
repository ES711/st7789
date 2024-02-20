# ST7789

## 專案說明

這份專案中包含以下模組

1. ST7789全彩LCD顯示器

**採用freeRTOS的方式進行開發**

螢幕每1秒會刷新一次畫面，目前為兩個不同的畫面循環顯示

## IO設定

**電路板已經layout，請不要修改腳位設定**

### GPIO

* PA3 -> GPIO_Output -> CS
* PB3 -> GPIO_Output -> SCL
* PB4 -> GPIO_Output -> MOSI
* PB5 -> GPIO_Output -> DC
* PC8 -> GPIO_Output -> LED
* PD14 -> GPIO_Output -> RES
* PD15 -> GPIO_Output -> BLK

#### Tips
st7789是使用spi的方式進行通訊，但是腳位有限，因此我們改為用軟體模擬spi的方式

### RCC
* High Speed Clock(HSE) -> Crystal/Ceramic Resonator

### Clock Configuration
* Input frequency -> 26 Mhz

### SYS
* Debug -> Serial Wire

### Middleware
* FREERTOS -> CMSIS_V2

    其餘都不用修改

## Project Manager
* Code Generator ->  Generator peripheral...
    
    要勾選這樣才會把每個io的.h/.c生成出來

## 程式說明

### 主程式

#### taskST7789  -> 負責控制st7789

以下為向st7789發送畫面的方法
```c
LCD_ShowPicture(0,0,240,240,gImage_image);
```

圖片的規格
* 240x240
* 16bits 
* 水平掃描
* R:5bits;G:5bits;B:5bits;

在專案中我們會將圖片轉換成.h的形式，再使用include的方式將載入
```c
const unsigned char gImage_image[115200] = { /* 0X10,0X10,0X00,0XF0,0X00,0XF0,0X01,0X1B, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
.
.
.
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};
```

##### Tips
圖片的.h可以透過Image2Lcd生成，請參考專案中的資料夾(千萬不要嘗試自己刻!)

---

#### taskBlank -> 負責控制LED閃爍

只是讓LED閃爍確定freeRTOS可以正常工作而已，沒什麼用

### Hardware資料夾

#### lcd_init.c/.h

大部分皆是需要參考document來設定暫存器，因此不要更動裡面的程式碼

需要注意的腳位有兩個

##### DC腳
確定st7789是要接收數據或是命令
* 0 -> 接收命令
* 1 -> 接收數據

##### DIN腳
就是spi當中的MOSI，讓st7789來接收從stm發送過來的資料

##### LCD_Writ_Bus(uint8_t dat)
模擬spi協定

##### LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
設定座標，也就是從螢幕的哪個位置開始繪製

#### lcd.c/.h

##### LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
把螢幕的某個位置填充上同一種顏色

* color需要傳入16位元的色碼(0xFFFF -> white)

* xsta、ysta不一定要是(0, 0)

#### LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[])
顯示圖片

* pic[]這個參數就是要將我們用Image2Lcd轉換出來的圖片

* xsta、ysta一定要是(0, 0)才可以把圖片完整顯示出來

## 銘謝
* John Wu
* 優信電子
* 中景園電子