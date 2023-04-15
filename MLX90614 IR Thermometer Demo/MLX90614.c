#include "MLX90614.h"


void MLX90614_init()
{
    Soft_I2C_Init();
    delay_ms(100);
}


void MLX90614_enter_sleep_mode(unsigned char device_address)
{
    Soft_I2C_Start();
    Soft_I2C_Write(device_address);
    Soft_I2C_Write(0xFF);
    Soft_I2C_Write(MLX90614_PEC_for_sleep_mode);
    Soft_I2C_Stop();
}


unsigned int MLX90614_read(unsigned char device_address, unsigned char location)
{

    unsigned char PEC = 0x00;
    unsigned char lb = 0x00;
    unsigned int hb = 0x0000;
    
    Soft_I2C_Start();
    Soft_I2C_Write(device_address);
    Soft_I2C_Write(location);
    Soft_I2C_Start();
    Soft_I2C_Write((device_address + 1));
    lb = Soft_I2C_Read(1);
    hb = Soft_I2C_Read(1);
    PEC = Soft_I2C_Read(0);
    Soft_I2C_Stop();
    
    hb <<= 8;
    hb |= lb;
    
    return hb;
}


void MLX90614_write_ROM(unsigned char device_address, unsigned char location, unsigned int value, unsigned char PEC)
{
    unsigned char hb = 0x00;
    unsigned char lb = 0x00;
    unsigned int temp = 0x0000;
    
    lb = (temp & 0x00FF);
    temp &= 0xFF00;
    temp >>= 0x08;
    hb = temp;
    
    Soft_I2C_Start();
    Soft_I2C_Write((device_address + 1));
    Soft_I2C_Write(location);
    Soft_I2C_Write(lb);
    Soft_I2C_Write(hb);
    Soft_I2C_Write(PEC);
    Soft_I2C_Stop();
}


void MLX90614_erase_ROM(unsigned char device_address, unsigned char location)
{
    MLX90614_write_ROM(device_address, location, 0x0000, MLX90614_PEC_for_ROM_erase);
}


float MLX90614_get_temperature(unsigned int value, unsigned char unit)
{
     float temperature = 0.0;
     
     if(value <= Temp_count_Max)
     {
           temperature = value;
           temperature *= slope;

           switch(unit)
           {
               case unit_Celcius:
               {
                   temperature -= _0C_in_K;
                   break;
               }
               case unit_Fahrenheit:
               {
                   temperature = MLX90614_get_temperature(value, unit_Celcius);
                   temperature = C_to_F(temperature);
                   break;
               }
               default:
               {
                   break;
               }
           }
     
           return temperature;
     }
}