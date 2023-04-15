#include "MCP3008.h"


void MCP3008_init(void)
{
    PORTB = 0x00;
    DDRB = 0xB0;
    
    SPI1_Init_Advanced(_SPI_MASTER, \
                       _SPI_FCY_DIV16, \
                       _SPI_CLK_LO_LEADING);
                       
    //MCP3008_CS = HIGH;
}


signed int MCP3008_read(unsigned char channel, unsigned char type)
{
     unsigned char LB = 0x00;
     unsigned char HB = 0x00;
     unsigned int value = 0x0000;
     
     MCP3008_CS = LOW;
     
     SPI1_Write(MCP3008_Start);
     HB = SPI1_Read(channel);
     LB = SPI1_Read(0x00);
     
     MCP3008_CS = HIGH;
     
     value = ((unsigned int)HB);
     value <<= 0x08;
     value |= ((unsigned int)LB);
     
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
     
     
     value &= 0x03FF;

     return value;
}