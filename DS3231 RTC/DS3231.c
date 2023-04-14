#include "DS3231.h"                                                       
                                                                 
                                                          
unsigned char bcd_to_decimal(unsigned char d)                
{                                                                                          
         return ((d & 0x0F) + (((d & 0xF0) >> 4) * 10));
}                                
                                                             

unsigned char decimal_to_bcd(unsigned char d)
{
         return (((d / 10) << 4) & 0xF0) | ((d % 10) & 0x0F);
}                                                    
                                        
                  
unsigned char DS3231_Read(unsigned char address)
{                                     
         unsigned char value = 0;  
         
         twi_start();
         twi_write(DS3231_Write_addr);
         twi_write(address);
         twi_start();
         twi_write(DS3231_Read_addr);
         value = twi_read(0);
         twi_stop();
         
         return value;
}                     


void DS3231_Write(unsigned char address, unsigned char value)    
{  
         twi_start();
         twi_write(DS3231_Write_addr);
         twi_write(address);
         twi_write(value);
         twi_stop();
}  


void DS3231_init() 
{                                   
         twi_Init(100000);
         DS3231_Write(controlREG, 0x00);  
         DS3231_Write(statusREG, 0x08); 
}                       
      

void getTime(unsigned char *p3, unsigned char *p2, unsigned char *p1, unsigned char *p0, unsigned char hour_format)
{                        
         unsigned char tmp = 0;    
         
         tmp = DS3231_Read(secondREG);
         *p1 = bcd_to_decimal(tmp);
         tmp = DS3231_Read(minuteREG);
         *p2 = bcd_to_decimal(tmp);
         
         switch(hour_format)
         {                                             
                  case 1:          
                  {          
                           tmp = DS3231_Read(hourREG);
                           tmp &= 0x20;
                           *p0 = (unsigned char)(tmp >> 5);
                           tmp = (0x1F & DS3231_Read(hourREG));
                           *p3 = bcd_to_decimal(tmp);
                           break;     
                  }   
                  default:
                  { 
                           tmp = (0x3F & DS3231_Read(hourREG));
                           *p3 = bcd_to_decimal(tmp);
                           break;     
                  } 
         }  
}                                  
                                                     
                                
void getDate(unsigned char *p4, unsigned char *p3, unsigned char *p2, unsigned char *p1)
{
         unsigned char tmp = 0;
         
         tmp = DS3231_Read(yearREG);
         *p1 = bcd_to_decimal(tmp);
         tmp = (0x1F & DS3231_Read(monthREG));
         *p2 = bcd_to_decimal(tmp);
         tmp = (0x3F & DS3231_Read(dateREG));
         *p3 = bcd_to_decimal(tmp);
         tmp = (0x07 & DS3231_Read(dayREG));
         *p4 = bcd_to_decimal(tmp);
}

                                                    
void setTime(unsigned char hSet, unsigned char mSet, unsigned char sSet, unsigned char am_pm_state, unsigned char hour_format)  
{                                                                                                             
         unsigned char tmp = 0;        
         
         DS3231_Write(secondREG, (decimal_to_bcd(sSet)));
         DS3231_Write(minuteREG, (decimal_to_bcd(mSet)));   
         
         switch(hour_format)
         {
                  case 1: 
                  {        
                           switch(am_pm_state)
                           {
                                    case 1:
                                    {            
                                             tmp = 0x60;
                                             break;
                                    }
                                    default:
                                    {    
                                             tmp = 0x40;
                                             break;
                                    }
                           }                           
                           DS3231_Write(hourREG, ((tmp | (0x1F & (decimal_to_bcd(hSet))))));                   
                           break;
                  }                                              
                  
                  default:
                  { 
                           DS3231_Write(hourREG, (0x3F & (decimal_to_bcd(hSet)))); 
                           break;
                  }  
         }   
}                                                  

                                    
void setDate(unsigned char daySet, unsigned char dateSet, unsigned char monthSet, unsigned char yearSet) 
{          
         DS3231_Write(dayREG, (decimal_to_bcd(daySet)));            
         DS3231_Write(dateREG, (decimal_to_bcd(dateSet)));  
         DS3231_Write(monthREG, (decimal_to_bcd(monthSet)));
         DS3231_Write(yearREG, (decimal_to_bcd(yearSet)));   
}

              
void setA1Time(unsigned char hSet, unsigned char mSet, unsigned char am_pm_state, unsigned char hour_format)
{   
         unsigned char tmp = 0;                 
         
         DS3231_Write(alarm1secREG , (0x7F & (decimal_to_bcd(0))));  
         DS3231_Write(alarm1minREG , (0x7F & (decimal_to_bcd(mSet))));    
         
         switch(hour_format)
         {                          
                  case 1: 
                  {        
                           switch(am_pm_state)
                           {
                                    case 1:
                                    {            
                                             tmp = 0x60;
                                             break;
                                    }
                                    default:
                                    {    
                                             tmp = 0x40;
                                             break;
                                    }
                           }                                
                           DS3231_Write(hourREG, ((tmp | (0x1F & (decimal_to_bcd(alarm1hrREG))))));                   
                           break;
                  }                                                       
                  
                  default:
                  { 
                           DS3231_Write(hourREG, (0x3F & (decimal_to_bcd(alarm1hrREG)))); 
                           break;
                  }  
         }  
}


void setA2Time(unsigned char hSet, unsigned char mSet, unsigned char am_pm_state, unsigned char hour_format)
{                                  
         unsigned char tmp = 0;   
                                                                       
         DS3231_Write(alarm2minREG , (0x7F & (decimal_to_bcd(mSet)))); 
         
         switch(hour_format)        
         {                          
                  case 1: 
                  {        
                           switch(am_pm_state)
                           {
                                    case 1:
                                    {            
                                             tmp = 0x60;
                                             break;
                                    }
                                    default:
                                    {    
                                             tmp = 0x40;
                                             break;
                                    }
                           }                                
                           DS3231_Write(hourREG, ((tmp | (0x1F & (decimal_to_bcd(alarm2hrREG))))));                   
                           break;
                  }                                                       
                  
                  default:
                  { 
                           DS3231_Write(hourREG, (0x3F & (decimal_to_bcd(alarm2hrREG)))); 
                           break;
                  }  
         }  
}                 
   

void getA1Time(unsigned char *p2, unsigned char *p1, unsigned char *p0, unsigned char hour_format)
{              
         unsigned char tmp = 0; 
         
         tmp = DS3231_Read(alarm1minREG);
         *p1 = bcd_to_decimal(tmp);
         
         switch(hour_format)
         {                                             
                  case 1:          
                  {          
                           tmp = DS3231_Read(alarm1hrREG);
                           tmp &= 0x20;
                           *p0 = (unsigned char)(tmp >> 5);
                           tmp = (0x1F & DS3231_Read(alarm1hrREG));
                           *p2 = bcd_to_decimal(tmp);
                           break;     
                  }   
                  default:
                  { 
                           tmp = (0x3F & DS3231_Read(alarm1hrREG));
                           *p2 = bcd_to_decimal(tmp);
                           break;     
                  } 
         }  
}              


void getA2Time(unsigned char *p2, unsigned char *p1, unsigned char *p0, unsigned char hour_format)
{     
         unsigned char tmp = 0;  
         
         tmp = DS3231_Read(alarm2minREG);
         *p1 = bcd_to_decimal(tmp);
                                  
         switch(hour_format)             
         {                                             
                  case 1:          
                  {          
                           tmp = DS3231_Read(alarm2hrREG);
                           tmp &= 0x20;
                           *p0 = (unsigned char)(tmp >> 5);
                           tmp = (0x1F & DS3231_Read(alarm2hrREG));
                           *p2 = bcd_to_decimal(tmp);
                           break;     
                  }   
                  default:
                  { 
                           tmp = (0x3F & DS3231_Read(alarm2hrREG));
                           *p2 = bcd_to_decimal(tmp);
                           break;     
                  } 
         }
}

                                
float getTemp()
{                 
         float t = 0.0;
         unsigned char lowByte = 0;
         signed char highByte = 0;
         lowByte = DS3231_Read(tempLSBREG);
         highByte = DS3231_Read(tempMSBREG);  
         lowByte >>= 6;                 
         lowByte &= 0x03;     
         t = ((float)lowByte);
         t *= 0.25;
         t += highByte;          
         return t;
                                      
}                        