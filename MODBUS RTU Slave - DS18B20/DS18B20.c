#include "DS18B20.h"


signed int get_temp()
{
      bit busy;
      signed int temp = 0;

      busy = 0;

      Ow_Reset(&PORTA, DS18B20_pin);
      Ow_Write(&PORTA, DS18B20_pin, Skip_ROM);
      Ow_Write(&PORTA, DS18B20_pin, Convert_Temperature);
      while(busy == 0)
      {
          busy = Ow_Read(&PORTA, DS18B20_pin);
      }
      Ow_Reset(&PORTA, DS18B20_pin);
      Ow_Write(&PORTA, DS18B20_pin, Skip_ROM);
      Ow_Write(&PORTA, DS18B20_pin, Read_Scatchpad);
      Delay_ms(400);

      temp =  Ow_Read(&PORTA, DS18B20_pin);
      temp += (Ow_Read(&PORTA, DS18B20_pin) << 0x08);
      temp >>= 4;
      
      return temp;
}