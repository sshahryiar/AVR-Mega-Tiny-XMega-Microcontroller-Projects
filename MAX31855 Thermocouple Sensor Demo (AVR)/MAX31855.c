#include "MAX31855.h"


void MAX31855_init(void)
{
  DDRB = 0x2C;
  SPI1_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV4, _SPI_CLK_LO_TRAILING);
  delay_ms(100);
}


signed long MAX31855_read(void)
{
  signed char i = 0x04;
  signed long value = 0x00000000;

  MAX31855_SS_pin_LOW;

  while(value > 0)
  {
    value |= SPI1_Read(0x00);
    value <<= 8;
    i--;
  };

  MAX31855_SS_pin_HIGH;

  return value;
}


unsigned char MAX31855_get_data(float *T_r, float *T_amb)
{
  signed long tmp = 0x00000000;
  signed long value = 0x00000000;
  float t = 0.0;

  value = MAX31855_read();

  tmp = (value & 0x7FFC0000);
  tmp >>= 18;
  t = ((float)((float)tmp) * 0.25);

  if((value & 0x80000000) != 0x00000000)
  {
  t = -t;
  }

  *T_r = t;

  tmp = (value & 0x0000FFF0);
  tmp >>= 4;
  t = ((float)((float)tmp) * 0.0625);

  if((value & 0x00008000) != 0x00000000)
  {
  t = -t;
  }

  *T_amb = t;

  return ((unsigned char)(value & 0x00000007));
}