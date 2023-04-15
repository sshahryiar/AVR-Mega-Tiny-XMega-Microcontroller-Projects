#include "MCP3008.h"


uint8_t SPI_tranfer(uint8_t value)
{
	SPDR = value;
	
	while(!(SPSR & (1 << SPIF)));

	return SPDR;
}


void MCP3008_init(void)
{
    PORTB = 0x00;
    DDRB = 0xB0;
    
    SPCR = 0x51;
    SPSR = 0x00;
	
	MCP3008_CS_HIGH;
}


int16_t MCP3008_read(uint8_t channel, uint8_t type)
{
     uint8_t LB = 0x00;
     uint8_t HB = 0x00;
     int16_t value = 0x0000;
     
     MCP3008_CS_LOW;
     
     SPI_tranfer(MCP3008_Start);
     HB = SPI_tranfer(channel);
     LB = SPI_tranfer(0x00);
     
     MCP3008_CS_HIGH;
     
     value = ((int16_t)HB);
     value <<= 0x08;
     value |= ((int16_t)LB);
     
     switch(type)
     {
         case MCP3008_SINGLE_MODE:
         {
             value &= 0x03FF;
             break;
         }

         default:
         {
             value &= 0x07FF;
             
             if((value & 0x0400) != 0x0000)
             {
                 value = -value;
             }
             
             break;
         }
     }     

     return value;
}