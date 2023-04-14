#include "DS3234.h"


unsigned char bcd_to_decimal(unsigned char d)
{                                                                                          
    return ((d & 0x0F) + (((d & 0xF0) >> 4) * 10));
}                                
                                                             

unsigned char decimal_to_bcd(unsigned char d)
{
    return (((d / 10) << 4) & 0xF0) | ((d % 10) & 0x0F);
}     


void DS3234_init()
{
    SS = 1;
    SPI1_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV4, _SPI_CLK_LO_TRAILING);
    DS3234_write(control_reg, 0x20);
    DS3234_write(status_reg, 0x48);
    set_time(hr, min, s, ampm, hr_format);
    set_date(dy, dt, mt, yr);
}


unsigned char DS3234_read(unsigned char addr)
{
      unsigned char value = 0;
      
      SS = 0;
      SPI1_Write(addr | read_cmd);
      value = SPI_Read(0x00);
      
      SS = 1;
      return value;
}


void DS3234_write(unsigned char addr, unsigned char value)
{
      unsigned long temp = 0;

      SS = 0;
      temp = (addr | write_cmd);
      SPI1_Write(temp);
      SPI1_Write(value);
      SS = 1;
}


float get_temp()
{
      float t = 0;
      signed char highByte = 0;
      unsigned char lowByte = 0;

      highByte = DS3234_Read(tempMSB_reg);
      lowByte = DS3234_Read(tempLSB_reg);
      lowByte >>= 6;
      t = (lowByte & 0x03);
      t *= 0.25;
      t += highByte;
      return t;
} 


void write_SRAM(unsigned char addr, unsigned char value)
{
     DS3234_write(sramaddr_reg, addr);
     DS3234_write(sramdata_reg, value);
}


unsigned char read_SRAM(unsigned char addr)
{
     unsigned char value = 0;
     
     SS = 0;
     SPI1_Write(sramaddr_reg);
     SPI1_Write(addr);
     SS = 1;
     
     value = DS3234_Read(sramdata_reg);
     
     return value;
}


void get_time(unsigned short hour_format)
{
         unsigned char tmp = 0;
         
         s = DS3234_Read(second_reg);
         s = bcd_to_decimal(s);
         min = DS3234_Read(minute_reg);
         min = bcd_to_decimal(min);
         tmp = DS3234_Read(hour_reg);
         switch(hour_format)
         {
              case hr12:
              {
                   ampm = (tmp & 0x20);
                   ampm >>= 5;
                   hr = (tmp & 0x1F);
                   hr = bcd_to_decimal(hr);
                   break;
              }
              default:
              {
                   hr = (0x3F & tmp);
                   hr = bcd_to_decimal(hr);
                   break;
              }
         }
}


void get_date()
{
      yr = DS3234_Read(year_reg);
      yr = bcd_to_decimal(yr);
      mt = (0x1F & DS3234_Read(month_reg));
      mt = bcd_to_decimal(mt);
      dt = (0x3F & DS3234_Read(date_reg));
      dt = bcd_to_decimal(dt);
      dy = (0x07 & DS3234_Read(day_reg));
      dy = bcd_to_decimal(dy);
}


void set_time(unsigned char hSet, unsigned char mSet, unsigned char sSet, unsigned char am_pm_state, unsigned char hour_format)
{
      unsigned char tmp = 0;

      DS3234_Write(second_reg, (decimal_to_bcd(sSet)));
      DS3234_Write(minute_reg, (decimal_to_bcd(mSet)));
      switch(hour_format)
      {
          case hr12:
          {
               switch(am_pm_state)
               {
                        case pm:
                        {
                             tmp = 0x20;
                             break;
                        }
                        default:
                        {
                             tmp = 0x00;
                             break;
                        }
               }
               DS3234_Write(hour_reg, ((tmp | 0x40 | (0x1F & (decimal_to_bcd(hSet))))));
               break;
          }
          default:
          {
               DS3234_Write(hour_reg, (0xBF & (0x3F & (decimal_to_bcd(hSet)))));
               break;
          }
      }
}


void set_date(unsigned char daySet, unsigned char dateSet, unsigned char monthSet, unsigned char yearSet)
{
    DS3234_Write(day_reg, (decimal_to_bcd(daySet)));
    DS3234_Write(date_reg, (decimal_to_bcd(dateSet)));
    DS3234_Write(month_reg, (decimal_to_bcd(monthSet)));
    DS3234_Write(year_reg, (decimal_to_bcd(yearSet)));
}