#include "ITG3200.h"


void ITG3200_init()
{
    TWI_Init(100000);
    delay_ms(100);
    ITG3200_write_byte(PWR_MGM_REG, H_RESET);
    ITG3200_write_byte(SMPLRT_DIV_REG, 0x09);
    ITG3200_write_byte(DLPF_FS_REG, (FS_SEL | LPF_98HZ));
    delay_ms(600);
}


void ITG3200_write_byte(unsigned char address, unsigned char value)
{
     TWI_Start();
     TWI_Write(ITG3200_Write);
     TWI_Write(address);
     TWI_Write(value);
     TWI_Stop();
}


void ITG3200_write_word(unsigned char address, unsigned int value)
{
     unsigned int temp = 0x0000;

     temp = (value & 0xFF00);
     temp >>= 0x08;

     TWI_Start();
     TWI_Write(ITG3200_Write);
     TWI_Write(address);
     TWI_Write(temp);
     TWI_Write(value & 0x00FF);
     TWI_Stop();
}


unsigned char ITG3200_read_byte(unsigned char address)
{
     unsigned char value = 0x00;

     TWI_Start();
     TWI_Write(ITG3200_Write);
     TWI_Write(address);
     TWI_Start();
     TWI_Write(ITG3200_Read);
     value = TWI_Read(0);
     TWI_Stop();

     return value;
}


unsigned int ITG3200_read_word(unsigned char address)
{
     unsigned int hb = 0x00;
     unsigned char lb = 0x00;

     TWI_Start();
     TWI_Write(ITG3200_Write);
     TWI_Write(address);
     TWI_Start();
     TWI_Write(ITG3200_Read);
     hb = TWI_Read(1);
     lb = TWI_Read(0);
     TWI_Stop();

     hb <<= 0x08;
     hb |= lb;

     return hb;
}


void get_raw_values(signed int *x_val, signed int *y_val, signed int *z_val)
{
     signed int val_x = 0x0000;
     signed int val_y = 0x0000;
     signed int val_z = 0x0000;
     unsigned char samples = 0x08;

     while(samples > 0)
     {
         val_x += ITG3200_read_word(GYRO_XOUT_H_REG);
         val_y += ITG3200_read_word(GYRO_YOUT_H_REG);
         val_z += ITG3200_read_word(GYRO_ZOUT_H_REG);
         samples--;
     }

     val_x >>= 0x03;
     val_y >>= 0x03;
     val_z >>= 0x03;

     *x_val = val_x;
     *y_val = val_y;
     *z_val = val_z;
}


void get_corrected_raw_values(signed int *x_val, signed int *y_val, signed int *z_val, signed int *x_off, signed int *y_off, signed int *z_off)
{
     *x_val -= *x_off;
     *y_val -= *y_off;
     *z_val -= *z_off;
}


void get_deg_per_second(signed int *x_val, signed int *y_val, signed int *z_val, float scale)
{
     signed int val_x = 0x0000;
     signed int val_y = 0x0000;
     signed int val_z = 0x0000;
     
     val_x = *x_val;
     val_y = *y_val;
     val_z = *z_val;
     
     *x_val = (val_x / scale);
     *y_val = (val_y / scale);
     *z_val = (val_z / scale);
}


signed int ITG3200_get_temperature()
{
    signed int temp = 0;

    temp = ITG3200_read_word(TEMP_OUT_H_REG);
    temp += 13200;
    temp /= 2.80;
    temp += 3500;

    return temp;
}