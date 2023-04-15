#include "US42V2.h"


void US42V2_init(void)
{
    TWI_Init(I2C_bus_speed);
    delay_ms(100);
}


unsigned int US42V2_get_distance(unsigned char slave_address)
{
     unsigned char hb = 0x00;
     unsigned char lb = 0x00;
     
     unsigned int temp = 0x0000;
     
     TWI_Start();
     TWI_Write(slave_address);
     TWI_Write(US42V2_get_range_cmd);
     TWI_Stop();

     delay_ms(100);

     TWI_Start();
     TWI_Write(slave_address | 1);
     hb = TWI_Read(1);
     lb = TWI_Read(0);
     TWI_Stop();
     
     temp = hb;
     temp <<= 0x08;
     temp |= lb;
     
     return temp;        
}


void US42V2_change_slave_address(unsigned char old_slave_address, unsigned char new_slave_address)
{
        TWI_Start();
        TWI_Write(old_slave_address);
        TWI_Write(US42V2_change_address_unlock_1_cmd);
        TWI_Write(US42V2_change_address_unlock_2_cmd);
        TWI_Write(new_slave_address);
        TWI_Stop();
}