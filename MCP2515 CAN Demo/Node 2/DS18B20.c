#include "DS18B20.h"


signed int DS18B20_get_temp(void)
{
      bit busy;
      signed int temp = 0;

      busy = 0;

      Ow_Reset(DS18B20_port, DS18B20_pin);
      Ow_Write(DS18B20_port, DS18B20_pin, Skip_ROM);
      Ow_Write(DS18B20_port, DS18B20_pin, Convert_Temperature);
      while(busy == 0)
      {
          busy = Ow_Read(DS18B20_port, DS18B20_pin);
      }
      Ow_Reset(DS18B20_port, DS18B20_pin);
      Ow_Write(DS18B20_port, DS18B20_pin, Skip_ROM);
      Ow_Write(DS18B20_port, DS18B20_pin, Read_Scatchpad);
      Delay_ms(400);

      temp =  Ow_Read(DS18B20_port, DS18B20_pin);
      temp += (Ow_Read(DS18B20_port, DS18B20_pin) << 0x08);
      temp >>= 4;
      
      return temp;
}