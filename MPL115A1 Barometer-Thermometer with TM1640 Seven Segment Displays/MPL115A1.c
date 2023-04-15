#include "MPL115A1.h"


void MPL115A1_init(void)
{
  DDRB |= 0xFF;
  PORTB |= 0xFF;
  
  SPI1_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV8, _SPI_CLK_LO_LEADING);
  delay_ms(10); 
  
  CSN_pin = HIGH;
  SDN_pin = HIGH;

  MPL115A1_get_coefficients();
}       
                                        

unsigned char MPL115A1_read(unsigned char address)
{
  unsigned char value = 0x00;

  CSN_pin = LOW;
  delay_ms(10);
  SPI_Write(address); 
  value = SPI_Read(0x00); 
  CSN_pin = HIGH;
  
  return value;        
}                                           
                                               
    
void MPL115A1_write(unsigned char address, unsigned char value)
{                                                     
  CSN_pin = LOW;
  delay_ms(3);
  SPI_Write((address & 0x7F)); 
  SPI_Write(value);                           
  CSN_pin = HIGH;
} 


void MPL115A1_get_coefficients(void)
{     
  unsigned int hb = 0x0000;
  unsigned int lb = 0x0000;
    
  MPL115A1_get_bytes(&hb, &lb, A0_H);
  coefficients.A0_ = ((hb << 0x05) + (lb >> 0x03) + ((lb & 0x07) / 8.0));
            
  MPL115A1_get_bytes(&hb, &lb, B1_H);              
  coefficients.B1_ = (((((hb & 0x1F) * 0x0100) + lb) / 8192.0) - 3.0);    
    
  MPL115A1_get_bytes(&hb, &lb, B2_H);    
  coefficients.B2_ = (((((hb - 0x80) << 0x08) + lb) / 16384.0) - 2.0);
                                        
  MPL115A1_get_bytes(&hb, &lb, C12_H);                 
  coefficients.C12_ = (((hb * 0x100) + lb) / 16777216.0);   
}  


void MPL115A1_get_bytes(unsigned int *hb, unsigned int *lb, unsigned char address) 
{ 
  *hb = MPL115A1_read(address); 
  *lb = MPL115A1_read((address + 0x02));
}
                                                                                                          
                 
void MPL115A1_get_data(float *pres, float *temp)   
{   
   unsigned int hb = 0;
   unsigned int lb = 0;

   unsigned long Padc = 0; 
   unsigned long Tadc = 0;
   
   MPL115A1_write(conv_cmd, 0x00); 

   MPL115A1_get_bytes(&hb, &lb, PRESH);
   Padc = (((hb << 0x08) + lb) >> 0x06);
   
   MPL115A1_get_bytes(&hb, &lb, TEMPH); 
   Tadc = (((hb << 0x08) + lb) >> 0x06);
   
   *pres = ( coefficients.A0_ + (( coefficients.B1_ + ( coefficients.C12_ * Tadc)) * Padc) + ( coefficients.B2_ * Tadc));      
   *pres = (((*pres * 65.0) / 1023.0) + 50.0);      
   
   *temp = (30.0 + ((Tadc - 472) / (-5.35)));
} 