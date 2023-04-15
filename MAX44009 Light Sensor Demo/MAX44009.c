#include "MAX44009.h"
#include "lcd_print.c"


void MAX44009_init(void)
{
    TWI_Init(100000);
    delay_ms(100);

    MAX44009_write(INTERRUPT_ENABLE_REG, 0x00);
    MAX44009_write(CONFIGURATION_REG, 0x03);
    MAX44009_write(THRESHOLD_TIMER_REG, 0xFF);
}


void MAX44009_write(unsigned char address, unsigned char value)
{
   TWI_Start();
   TWI_Write(MAX44009_Write);
   TWI_Write(address);
   TWI_Write(value);
   TWI_Stop();
}


unsigned char MAX44009_read_byte(unsigned char address)
{
   unsigned char value = 0x00;

   TWI_Start();
   TWI_Write(MAX44009_Write);
   TWI_Write(address);
   
   TWI_Start();
   TWI_Write(MAX44009_Read);
   value = TWI_Read(0);
   TWI_Stop();

   return value;   
}


unsigned long MAX44009_get_LUX_value(void)
{

   signed char exponent = 0x00;  
   unsigned char low_value = 0x00;
   unsigned char high_value = 0x00;
   unsigned long mantisa = 0x0000;      
   
   TWI_Start();
   TWI_Write(MAX44009_Write);
   TWI_Write(LUX_HIGH_BYTE_REG);
   
   TWI_Start();
   TWI_Write(MAX44009_Read);
   high_value = TWI_Read(1);
   low_value = TWI_Read(0);
   TWI_Stop();

   exponent = ((high_value & 0xF0) >> 4);
   mantisa = (((high_value & 0x0F) << 4) | (low_value & 0x0F));

   do
   {
      mantisa <<= 1;
      exponent--;
   }while(exponent > -1);
   
   mantisa = (((float)mantisa) * 0.045);

   return mantisa;
}