#include "MAX72xx.h"


void MAX72xx_init()
{        
    CS = 1; 
    MAX72xx_write(shutdown_reg, run_cmd);
    MAX72xx_write(decode_mode_reg, Code_B_decode_digit_0_to_3);
    MAX72xx_write(scan_limit_reg, digit_0_to_3);
    MAX72xx_write(intensity_reg, 0x19);
    delay_ms(100);
}                                                                

                                                          
void MAX72xx_write(unsigned char address, unsigned char value)
{
    unsigned char s = 16;
    unsigned int data_word = 0;               
                  
    data_word = (((unsigned int)address << 8) | value);                 
    CS = 0;        
    
    while(s > 0)
    {       
        if((data_word & 0x8000) != 0)
        {
            DIN = 1;
        }           
        else
        {
            DIN = 0;
        } 
        CLK = 0;
        delay_ms(1);
        CLK = 1; 
        data_word <<= 1;
        s--;
    }
    CS = 1;
}