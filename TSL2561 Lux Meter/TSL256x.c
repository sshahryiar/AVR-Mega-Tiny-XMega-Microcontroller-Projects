#include "TSL256x.h"


void TSL256x_init()
{
     Soft_I2C_Init();
     delay_ms(200);
     TSL256x_write(control_reg, 0x03);
     TSL256x_write(timing_reg, 0x00);
     TSL256x_write(interrupt_reg, 0x00);
     TSL256x_write(control_reg, 0x00);
}


unsigned char TSL256x_read_byte(unsigned char reg)
{
     unsigned char value = 0;
     
     Soft_I2C_Start();
     Soft_I2C_Write(TSL256x_write_mode);
     Soft_I2C_Write(TSL256x_CMD | reg);
     Soft_I2C_Start();
     Soft_I2C_Write(TSL256x_read_mode);
     value = Soft_I2C_Read(0);
     Soft_I2C_Stop();
     
     return value;
}


unsigned int TSL256x_read_word(unsigned char reg)
{
     unsigned char hb = 0;
     unsigned char lb = 0;
     unsigned int value = 0;
     
     lb = TSL256x_read_byte(reg);
     hb = TSL256x_read_byte(reg + 1);
     
     value = hb;
     value <<= 8;
     value |= lb;

     return value;
}


void TSL256x_write(unsigned char reg, unsigned char value)
{
     Soft_I2C_Start();
     Soft_I2C_Write(TSL256x_write_mode);
     Soft_I2C_Write(reg);
     Soft_I2C_Write(value);
     Soft_I2C_Stop();
}


void get_raw_data(unsigned int *ch_0, unsigned int *ch_1)
{
     *ch_0 = TSL256x_read_word(data_0_low_reg);
     *ch_1 = TSL256x_read_word(data_1_low_reg);
}


unsigned long calculate_lux(unsigned int iGain, unsigned int tInt)
{
    float b = 0;
    float m = 0;
    float ratio = 0;
    
    unsigned int ch0 = 0;
    unsigned int ch1 = 0;
    
    TSL256x_write(control_reg, 0x03);
    get_raw_data(&ch0, &ch1);
    delay_ms(14);
    TSL256x_write(control_reg, 0x00);
    
    if((ch0 == 0xFFFF) || (ch1 == 0xFFFF))
    {
        return 0;
    } 
    
    ch0 *= (402.0 / tInt);
    ch1 *= (402.0 / tInt);
    
    if(!iGain)
    {
        ch0 <<= 4;
        ch1 <<= 4;
    }
    
    ratio = (ch1 / ch0);
    
    if((ratio >= 0) && (ratio <= 0.125))
    {
        b = 0.0304;
        m = 0.0272;
    }
    else if((ratio > 0.125) && (ratio <= 0.25))
    {
        b = 0.0325;
        m = 0.044;
    }
    else if((ratio > 0.25) && (ratio <= 0.375))
    {
        b = 0.0351;
        m = 0.0544;
    }
    else if((ratio > 0.375) && (ratio <= 0.5))
    {
        b = 0.0381;
        m = 0.0624;
    }
    else if((ratio > 0.5) && (ratio <= 0.61))
    {
        b = 0.0224;
        m = 0.031;
    }
    else if((ratio > 0.61) && (ratio <= 0.8))
    {
        b = 0.0128;
        m = 0.0153;
    }
    else if((ratio > 0.8) && (ratio <= 1.3))
    {
        b = 0.00146;
        m = 0.00112;
    }
    else if(ratio > 1.30)
    {
        b = 0;
        m = 0;
    }
    
    ratio = ((b - (m * ratio)) * ch0);
    ratio *= 1.51;
    
    return ratio;
}