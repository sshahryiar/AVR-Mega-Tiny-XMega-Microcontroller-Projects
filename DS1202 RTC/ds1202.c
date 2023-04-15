#include "DS1202.h"


struct  
{             
    unsigned char year;
    unsigned char month;                          
    unsigned char date;  
    unsigned char dow;   
    unsigned char hour;  
    unsigned char min;  
    unsigned char sec;     
}time; 


unsigned char bcd_to_decimal(unsigned char value)
{
    return ((value & 0x0F) + (((value & 0xF0) >> 0x04) * 0x0A));
}


unsigned char decimal_to_bcd(unsigned char value)
{
    return (((value / 0x0A) << 0x04) & 0xF0) | ((value % 10) & 0x0F);
}
                                                                             
                      
void DS1202_GPIO_init(void)
{
    RST_dir_out;
    SCK_dir_out;
    IO_dir_out;
}


void DS1202_init(void)
{
    DS1202_GPIO_init();
    
    RST_out_low;
    SCK_out_low;
    delay_ms(2);
    DS1202_write(control_wreg, 0x00);

    if((time.date > 31) || (time.date < 1) || (time.month > 12) || (time.date < 1))
    {
        DS1202_set_time(10, 10, 10);
        DS1202_set_date(1, 1, 0, 7);
    }
}                                                                        
                                      
                                                               
void DS1202_serial_write(unsigned char value)
{   
    unsigned char n = 0x08;

    while(n > 0)
    {
      if((value & 0x01) != 0)
      {
      	IO_out_high;
      }
      else
      {
      	IO_out_low;
      }
      
      SCK_out_high;
      SCK_out_low;
      
      value >>= 1;

      n--;
    };
}       


unsigned char DS1202_serial_read(void)
{     
    unsigned char n = 0x08;
    unsigned char value = 0x00;

    IO_dir_in;

    while(n > 0)
    {
      value >>= 1;
      
      if(IO_in != 0)
      {
      	value |= 0x80;
      }
      
      SCK_out_high;
      SCK_out_low;
      
      n--;
    };

    IO_dir_out;

    return value;
}

                  
void DS1202_write(unsigned char addr, unsigned char value)        
{                                                                                                                
    RST_out_high;
    DS1202_serial_write(addr);
    DS1202_serial_write(value);
    RST_out_low;
}     
                                            
                                                 
unsigned char DS1202_read(unsigned char addr)
{                                             
    unsigned char result = 0x00;

    RST_out_high;
    DS1202_serial_write(addr);
    result = DS1202_serial_read();
    RST_out_low;

    return result;
}     


unsigned char read_RAM(unsigned char addr)
{ 
    unsigned char value = 0;

    if((ramlocstartr + addr) <= ramlocendr)
    {
        value = DS1202_read((ramlocstartr + addr));
    }

    return value;
}            


void DS1202_write_RAM(unsigned char addr, unsigned char value)
{    
    if((ramlocstartw + addr) <= ramlocendw)
    {
        DS1202_write((ramlocstartw + addr), value);
    }
}


void DS1202_get_time(void)
{          
    time.hour = DS1202_read(hr_rreg);
    time.hour = bcd_to_decimal((0x3F & time.hour));
    time.min = DS1202_read(min_rreg);
    time.min = bcd_to_decimal((0x7F & time.min));
    time.sec = DS1202_read(sec_rreg);
    time.sec = bcd_to_decimal((0x7F & time.sec));
}                                    


void DS1202_get_date(void)
{    
    time.date = DS1202_read(date_rreg);
    time.date = bcd_to_decimal((0x3F & time.date));
    time.month = DS1202_read(month_rreg);
    time.month = bcd_to_decimal((0x1F & time.month));
    time.dow = DS1202_read(dow_rreg);
    time.dow = bcd_to_decimal((0x07 & time.dow));
    time.year = DS1202_read(year_rreg);
    time.year = bcd_to_decimal((0xFF & time.year));
}


void DS1202_get_time_and_date(void)
{
    DS1202_get_time();
    DS1202_get_date();
}


void DS1202_set_time(unsigned char p1, unsigned char p2, unsigned char p3)
{                                                                 
    time.hour = p1;
    p1 = decimal_to_bcd(time.hour);
    DS1202_write(hr_wreg, p1);
    time.min = p2;
    p2 = decimal_to_bcd(time.min);
    DS1202_write(min_wreg, p2);
    time.sec = p3;
    p3 = decimal_to_bcd(time.sec);
    DS1202_write(sec_wreg, p3);
}        
                                         

void DS1202_set_date(unsigned char p1, unsigned char p2, unsigned char p3, unsigned char p4)
{            
    time.date = p1;
    p1 = decimal_to_bcd(time.date);
    DS1202_write(date_wreg, p1);
    time.month = p2;
    p2 = decimal_to_bcd(time.month);
    DS1202_write(month_wreg, p2);
    time.year = p3;
    p3 = decimal_to_bcd(time.year);
    DS1202_write(year_wreg, p3);
    time.dow = p4;
    p4 = decimal_to_bcd(time.dow);
    DS1202_write(dow_wreg, p4);
}    