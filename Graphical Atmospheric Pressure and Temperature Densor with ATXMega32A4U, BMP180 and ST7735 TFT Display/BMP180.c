#include "BMP180.h"


void BMP180_init()
{
    TWIC_Init(100000);
    delay_ms(100);
    
    BMP180_Calibration();
}


signed char BMP180_read_byte(unsigned char address)
{
      unsigned char temp = 0;
      
      TWIC_Start();
      TWIC_Write(BMP180_Address);
      TWIC_Write(address);
      TWIC_Start();
      TWIC_Write(BMP180_Address | 1);
      temp = TWIC_Read(0);
      TWIC_Stop();
      
      return temp;
}


signed int BMP180_read_word(unsigned char address)
{
      unsigned char hb = 0;
      unsigned char lb = 0;

      signed int temp = 0;

      TWIC_Start();
      TWIC_Write(BMP180_Address);
      TWIC_Write(address);
      TWIC_Start();
      TWIC_Write(BMP180_Address | 1);
      hb = TWIC_Read(1);
      lb = TWIC_Read(0);
      TWIC_Stop();
      temp = ((hb << 8) | lb);

      return temp;
}


void BMP180_write(unsigned char address, unsigned char value)
{
      TWIC_Start();
      TWIC_Write(BMP180_Address);
      TWIC_Write(address);
      TWIC_Write(value);
      TWIC_Stop();
}


void BMP180_Calibration()
{
      _b1 = BMP180_read_word(B1_reg);
      _b2 = BMP180_read_word(B2_reg);
      mb = BMP180_read_word(MB_reg);
      mc = BMP180_read_word(MC_reg);
      md = BMP180_read_word(MD_reg);
      ac1 = BMP180_read_word(AC1_reg);
      ac2 = BMP180_read_word(AC2_reg);
      ac3 = BMP180_read_word(AC3_reg);
      ac4 = BMP180_read_word(AC4_reg);
      ac5 = BMP180_read_word(AC5_reg);
      ac6 = BMP180_read_word(AC6_reg);
}


unsigned int read_uncompensated_temperature()
{
      unsigned int ut = 0;

      BMP180_write(control_reg, temp_conv_cmd);
      delay_ms(5);
      ut = BMP180_read_word(MSB);

      return ut;
}


unsigned long read_uncompensated_pressure(unsigned char OSS)
{
      unsigned char msb_value = 0;
      unsigned char lsb_value = 0;
      unsigned char xlsb_value = 0;

      unsigned long up = 0;

      BMP180_write(control_reg, (0x34 + (OSS << 6)));
      switch(OSS)
      {
          case 1:
          {
              delay_ms(8);
              break;
          }
          case 2:
          {
              delay_ms(14);
              break;
          }
          case 3:
          {
              delay_ms(26);
              break;
          }
          default:
          {
              delay_ms(5);
              break;
          }
      }

      msb_value = BMP180_read_byte(MSB);
      lsb_value = BMP180_read_byte(LSB);
      xlsb_value = BMP180_read_byte(XLSB);

      up = ((((unsigned long)msb_value << 16) | ((unsigned long)lsb_value << 8) | (unsigned long)xlsb_value) >> (8 - OSS));

      return up;
}


float get_temperature(unsigned int UT)
{
      float tmp = 0;

      signed long x1 = 0;
      signed long x2 = 0;

      x1 = ((((signed long)UT - (signed long)ac6) * (signed long)ac5) >> 15);
      x2 = (((signed long)mc << 11) / (x1 + md));
      _b5 = (x1 + x2);
      tmp = ((_b5 + 8) >> 4);
      tmp *= 0.1;

      return tmp;
}


signed long get_pressure(unsigned long UP, unsigned char OSS)
{
      signed long p = 0;
      signed long x1 = 0;
      signed long x2 = 0;
      signed long x3 = 0;
      signed long _b3 = 0;
      signed long _b6 = 0;

      unsigned long _b4 = 0;
      unsigned long _b7 = 0;

      _b6 = (_b5 - 4000);

      x1 = ((_b2 * (_b6 * _b6) >> 12) >> 11);
      x2 = ((ac2 * _b6) >> 11);
      x3 = (x1 + x2);
      _b3 = (((((((signed long)ac1) << 2) + x3) << OSS) + 2) >> 2);
      x1 = ((ac3 * _b6) >> 13);
      x2 = ((_b1 * ((_b6 * _b6) >> 12)) >> 16);
      x3 = (((x1 + x2) + 2) >> 2);
      _b4 = ((ac4 * (unsigned long)(x3 + 32768)) >> 15);
      _b7 = ((unsigned long)(UP - _b3) * (50000 >> OSS));

      if(_b7 < 0x80000000)
      {
          p = ((_b7 << 1) / _b4);
      }
      else
      {
          p = ((_b7 / _b4) << 1);
      }

      x1 = ((p >> 8) * (p >> 8));
      x1 = ((x1 * 3038) >> 16);
      x2 = ((-7357 * p) >> 16);
      p += ((x1 + x2 + 3791) >> 4);

      return (signed long)p;
}