// SSP Basic SPI functions
// Date: 9/1/2012

#include "LPC17xx.h"
#include "ssp.h"
#include "ports.h"

void SSP1Init( void ) // Minimal startup SPI / no interrupts
{
  uint8_t i, Dummy=Dummy;
  LPC_SC->PCONP |= (0x1<<10); // Select power/clock for SSP1
  LPC_SC->PCLKSEL0 &= ~(0x3<<20); // Set speed
  LPC_PINCON->PINSEL0 &= ~((0x3<<14)|(0x3<<16)|(0x3<<18));  //  15:14 --> P0.7 CLR, 17:16 --> P0.8 CLR, 19:18 --> P0.9 CLR
  LPC_PINCON->PINSEL0 |= ((0x2<<14)|(0x2<<16)|(0x2<<18)); //  15:14 --> P0.7 to SCLK, 17:16 --> P0.8 to MISO1, 19:18 --> P0.9 to MOSI1
  LPC_SSP1->CR0 = (7 << 0) |(1 << 8);
  // 3:0 --> 7 for 8 bit transfer
  // 5:4 --> 0 for SPI format
  // 7:6 --> 0 for clock polarity/phase selection
  // 15:8 --> 7 for clock divider
  LPC_SSP1->CPSR = 0x2; // CLK speed
  for ( i = 0; i < FIFOSIZE; i++ )
  {
	Dummy = LPC_SSP1->DR; //Flush like a b0$$
  }
  LPC_SSP1->CR1 = (1<<1); // Startup

}

void SSP1Send(uint8_t buf) // Minimal SPI send , hardcoded select to LCD display
{
	uint8_t local_buf = buf; //Local send var
	LPC_GPIO1 -> FIOCLR |= P1_18; // SET Chip Select Low AKA select LCD device
	while ((LPC_SSP1->SR & ((1<<1)|(1<<4))) != (1<<1)); // Ensure module is not in use
	LPC_SSP1->DR = local_buf; // Send Data
	while(((LPC_SSP1->SR) & (1<<4))); // Wait until SSP1 is complete in sending data
	LPC_GPIO1 -> FIOSET |= P1_18; // SET Chip Select High AKA de-select LCD device.
}
