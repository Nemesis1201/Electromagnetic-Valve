// LCD basic C functions
// Written by RobG for msp430
// Date: 9/1/12
// Modified by Nathan Zimmerman

#include "LPC17xx.h"
#include "ssp.h"
#include "lcd.h"
#include "font_5x7.h"

uint8_t colorLowByte = 0;
uint8_t colorHighByte = 0;
uint8_t bgColorLowByte = 0;
uint8_t bgColorHighByte = 0;

const uint8_t frmctr[] = { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D };
const uint8_t invctr[] = { 0x07 };
const uint8_t pwctr1[] = { 0xA2, 0x02, 0x84 };
const uint8_t pwctr2[] = { 0xC5 };
const uint8_t pwctr3[] = { 0x0A, 0x00 };
const uint8_t pwctr4[] = { 0x8A, 0x2A };
const uint8_t pwctr5[] = { 0x8A, 0xEE };
const uint8_t vmctr1[] = { 0x0E };
const uint8_t madctl[] = { 0xA8 };
const uint8_t colmod[] = { 0x05 };

void setColor16(uint16_t color) {
	colorLowByte = color;
	colorHighByte = color >> 8;
}

void setBackgroundColor16(uint16_t color) {
	bgColorLowByte = color;
	bgColorHighByte = color >> 8;
}

void lcd_send(uint8_t data, uint8_t command) {
	uint8_t local_data = data;

	if (command) // IF COMMAND
	{
		LPC_GPIO0 -> FIOCLR |= LCD_RS; // SET RS TO 0 FOR COMMAND
	} else //Else Data
	{
		LPC_GPIO0 -> FIOSET |= LCD_RS; // SET RS TO 1 FOR DATA
	}

	SSP1Send(local_data); // Send out data on SPI

}

void lcd_command_send(uint8_t data) {
	lcd_send(data, WRITE_COMMAND);
}

void lcd_data_send(uint8_t data) {
	lcd_send(data, WRITE_DATA);
}

void writeConfig(uint8_t command, uint8_t num_args, const uint8_t *args) {
	lcd_command_send(command); // Send Command first
	while (num_args--) {
		lcd_data_send(*args++); //Send data per arg
	}
}

void writeConfigWithDelay(uint8_t command, uint8_t x10ms) {
	lcd_command_send(command);
	delay_ms(x10ms);
}

void lcd_init() {

	LPC_GPIO0 -> FIODIR |= LCD_RS;
	LPC_GPIO1 -> FIODIR |= LCD_CS;

	SSP1Init();
	delay_ms(10);
	writeConfigWithDelay(ST7735_SLPOUT, 50); // sleep out
	writeConfig(ST7735_FRMCTR1, 3, frmctr); // frame rate in normal mode
	writeConfig(ST7735_FRMCTR2, 3, frmctr); // frame rate in idle mode
	writeConfig(ST7735_FRMCTR3, 6, frmctr); // frame rate in partial mode
	writeConfig(ST7735_INVCTR, 1, invctr); // display inversion control
	writeConfig(ST7735_PWCTR1, 3, pwctr1); // power control settings
	writeConfig(ST7735_PWCTR2, 1, pwctr2); // power control settings
	writeConfig(ST7735_PWCTR3, 2, pwctr3); // power control settings
	writeConfig(ST7735_PWCTR4, 2, pwctr4); // power control settings
	writeConfig(ST7735_PWCTR5, 2, pwctr5); // power control settings
	writeConfig(ST7735_VMCTR1, 1, vmctr1); // power control settings
	writeConfig(ST7735_INVOFF, 0, 0); // display inversion off
	writeConfig(ST7735_MADCTL, 1, madctl); // screen rotation / display format
	writeConfig(ST7735_COLMOD, 1, colmod); // color mode
	writeConfigWithDelay(ST7735_NORON, 1); // normal display on
	writeConfigWithDelay(ST7735_DISPON, 10); // display on
	delay_ms(10);
}

void setAddr(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {

	lcd_command_send(ST7735_CASET);
	lcd_data_send(0x00); //High byte for address, not used since our screen is small
	lcd_data_send(xStart);
	lcd_data_send(0x00);
	lcd_data_send(xEnd);

	lcd_command_send(ST7735_RASET);
	lcd_data_send(0x00);
	lcd_data_send(yStart);
	lcd_data_send(0x00);
	lcd_data_send(yEnd);

	lcd_command_send(ST7735_RAMWR);
}

void drawChar(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x01;
	uint8_t oc = c - 0x20;
	setAddr(x, y, x + 4, y + 7);

	while (row < 8) {
		while (col < 5) {
			if (font[oc][col] & bit) {
				lcd_data_send(colorHighByte);
				lcd_data_send(colorLowByte);
			} else {
				lcd_data_send(bgColorHighByte);
				lcd_data_send(bgColorLowByte);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

void drawString(uint8_t x, uint8_t y, char *string) {
	uint8_t xs = x;
	while (*string) {
		drawChar(xs, y, *string++);
		xs += 6;
	}
}

void fillScreen(uint16_t color_16) {

	uint8_t colorHighByte = color_16 >> 8;
	uint8_t colorLowByte = color_16;
	uint8_t x = JDT1800_WIDTH;
	uint8_t y = JDT1800_HEIGHT;

	setAddr(0, 0, x - 1, y - 1);

	while (y-- > 0) {
		while (x-- > 0) {
			lcd_data_send(colorHighByte);
			lcd_data_send(colorLowByte);
		}
	}
}

void Output_Pixel(uint16_t x, uint16_t y, uint16_t colorz) {
	uint8_t colorD = colorz >> 8;
	setAddr(128 - y, x, 128 - y, x);
	//	setAddr(x, y,x , y  );
	lcd_data_send(colorD);
	colorD = colorz;
	lcd_data_send(colorD);
}

void delay_ms(unsigned int ms){
	volatile unsigned int j= ms * 10000;
	volatile unsigned int i;
	for(i = 0; i < j; i++);
} // End delay_ms

