#include "PCA9685.h"


void PCA9685_init()
{
     unsigned char MSB = 0x00;
     
     TWI_Init(100000);
     delay_ms(10);
     
     PCA9685_soft_reset();
     delay_ms(1);
     
     PCA9685_write_byte(PCA9685_MODE1_reg, 0x01);
     
     MSB = PCA9685_read_byte(PCA9685_MODE1_reg);
     
     PCA9685_write_byte(PCA9685_MODE1_reg, (0x10 | MSB));
     PCA9685_write_byte(PCA9685_MODE2_reg, 0x04);
     PCA9685_write_byte(PCA9685_PRE_SCALE_reg, 0x06);
     delay_ms(1);
     PCA9685_write_byte(PCA9685_MODE1_reg, MSB);
}


void PCA9685_soft_reset()
{
    TWI_Start();
    TWI_Write(0x00);
    TWI_Write(PCA9685_software_reset);
    TWI_Stop();
}


unsigned char PCA9685_read_byte(unsigned char address)
{
     unsigned char temp = 0x00;
     
     TWI_Start();
     TWI_Write(PCA9685_write_cmd);
     TWI_Write(address);
     TWI_Start();
     TWI_Write(PCA9685_read_cmd);
     temp = TWI_Read(0);
     TWI_Stop();
     
     return temp;
}


void PCA9685_write_byte(unsigned char address, unsigned char value)
{
     TWI_Start();
     TWI_Write(PCA9685_write_cmd);
     TWI_Write(address);
     TWI_Write(value);
     TWI_Stop();
}


void PCA9685_write_word(unsigned char address, unsigned int word_value)
{
     unsigned char hb = 0x00;
     unsigned char lb = 0x00;
     
     lb = (word_value & 0x00FF);
     hb = ((word_value & 0xFF00) >> 0x08);
     
     PCA9685_write_byte(address, lb);
     PCA9685_write_byte((address + 1), hb);
}


void PCA9685_set_PWM_duty(unsigned char ch, unsigned int duty, unsigned int dead_time)
{
     unsigned int off_time = 0x0000;

     off_time = (duty + dead_time);

     if(off_time >= MAX_count)
     {
         off_time = (off_time - MAX_count);
     }

     PCA9685_write_word((PCA9685_CH0_ON_L_reg + (ch << 2)), (dead_time & 0x0FFF));
     PCA9685_write_word((PCA9685_CH0_OFF_L_reg + (ch << 2)), (off_time & 0x0FFF));
}