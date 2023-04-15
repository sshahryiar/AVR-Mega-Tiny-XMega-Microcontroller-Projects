#include "TMPx75.h"


unsigned int make_word(unsigned char HB, unsigned char LB)
{
    unsigned int tmp = 0;

    tmp = HB;
    tmp <<= 8;
    tmp |= LB;

    return tmp;
}


void TMPx75_init(void)
{   
    Soft_I2C_Init();
    TMPx75_write_byte(pointer_conf_reg, (queue_value_1             \
                                         | OS_POL_LOW              \
                                         | OS_Comp                 \
                                         | normal                  \
                                         | OS_mode_disable         \
                                         | _12_bit_resolution));
    delay_ms(60);
}


void TMPx75_write_byte(unsigned char pointer, unsigned char value)
{
    Soft_I2C_start();
    Soft_I2C_write(TMPx75_write_cmd);
    Soft_I2C_write(pointer);
    Soft_I2C_write(value);
    Soft_I2C_stop();
}                                                               


void TMPx75_write_bytes(unsigned char pointer, signed int value)
{
    unsigned char values[0x02] = {0x00, 0x00};

    values[0] = ((value & 0xFF00) >> 8);                                                                 
    values[1] = (value & 0x00FF);
                                                    
    Soft_I2C_start();
    Soft_I2C_write(TMPx75_write_cmd);
    Soft_I2C_write(pointer);
    Soft_I2C_write(values[0]);
    Soft_I2C_write(values[1]);
    Soft_I2C_stop();
}                                                 
               

signed int TMPx75_read_byte(unsigned char pointer)
{
    unsigned char value = 0x00;                                     
    
    Soft_I2C_start();
    Soft_I2C_write(TMPx75_write_cmd);
    Soft_I2C_write(pointer);
    Soft_I2C_start();
    Soft_I2C_write(TMPx75_read_cmd);
    value = Soft_I2C_read(0);
    Soft_I2C_stop();
                 
    return value; 
}                     

                           
signed int TMPx75_read_bytes(unsigned char pointer)
{
    register signed int value = 0;
    
    unsigned char lb = 0;
    unsigned char hb = 0;    
    
    Soft_I2C_write(TMPx75_write_cmd);
    Soft_I2C_write(pointer);
    Soft_I2C_start();
    Soft_I2C_write(TMPx75_read_cmd);
    hb = Soft_I2C_read(1);
    lb = Soft_I2C_read(0);
    Soft_I2C_stop();
                                
    value = make_word(hb, lb);
    
    return value;            
}                                               


float TMPx75_get_temp(void)
{
    float temp = 0.0;
    
    temp = ((0x7FF0 & TMPx75_read_bytes(pointer_temp_reg)) >> 4);
    temp *= 0.0625;
    
    return temp;
}