// LCD basic C functions
// Written by RobG for msp430
// Date: 9/1/12
// Modified by Nathan Zimmerman

#ifndef LCD_H_
#define LCD_H_

#include "ports.h"

#define		LCD_SCLK	P0_7
#define		LCD_RS		P0_0
#define		LCD_MOSI	P0_9
#define		LCD_CS		P1_18

#define ST7735_16_BLACK   0x0000
#define ST7735_16_BLUE    0x001F
#define ST7735_16_RED     0xF800
#define ST7735_16_ORANGE  0xF900
#define ST7735_16_ORANGE2 0xFE00
#define ST7735_16_GREEN   0x07E0
#define ST7735_16_CYAN    0x07FF
#define ST7735_16_MAGENTA 0xF81F
#define ST7735_16_YELLOW  0xFFE0
#define ST7735_16_WHITE   0xFFFF

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09
#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E
#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1
#define ST7735_PWCTR6  0xFC

#define WRITE_COMMAND	0x1
#define WRITE_DATA		0x0

#define JDT1800_WIDTH  160
#define JDT1800_HEIGHT 128

extern void setColor16(uint16_t color);
extern void setBackgroundColor16(uint16_t color);
extern void drawChar(uint8_t x, uint8_t y, char c);
extern void drawString(uint8_t x, uint8_t y, char *string);
extern void drawChar8x12(uint8_t x, uint8_t y, char c);
extern void drawString8x12(uint8_t x, uint8_t y, char *string);
extern void lcd_send(uint8_t data, uint8_t command);
extern void lcd_command_send(uint8_t data);
extern void lcd_data_send(uint8_t data);
extern void writeConfig(uint8_t command, uint8_t num_args, const uint8_t *args);
extern void writeConfigWithDelay(uint8_t command, uint8_t x10ms);
extern void lcd_init();
extern void setAddr(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
extern void fillScreen(uint16_t color_16);
extern void Output_Pixel(uint16_t x, uint16_t y, uint16_t colorz);
extern void delay_ms(unsigned int ms);

#endif /* LCD_H_ */
