#include "LIDAR.h"


void LIDAR_write(unsigned char address, unsigned char value)
{
    TWI_start();
    TWI_write(LIDAR_address);
    TWI_write(address);
    TWI_write(value);
    TWI_stop();
}


unsigned char LIDAR_read_byte(unsigned char address)
{
    unsigned char value = 0x00;

    TWI_start();
    TWI_write(LIDAR_address);
    TWI_write(address);

    TWI_start();
    TWI_write((LIDAR_address + 1));
    value = TWI_read(1);
    TWI_stop();

    return value;
}


unsigned int LIDAR_read_word(unsigned char address)
{
    unsigned char lb = 0x00;
    unsigned int hb = 0x0000;

    TWI_start();
    TWI_write(LIDAR_address);
    TWI_write(address);

    TWI_start();
    TWI_write((LIDAR_address + 1));
    hb = TWI_read(1);
    lb = TWI_read(1);
    TWI_stop();

    hb <<= 0x08;
    hb |= lb;

    return hb;
}


unsigned int LIDAR_get_distance()
{
    unsigned int d = 0x0000;

    LIDAR_write(0x00, 0x04);
    delay_ms(20);
    d = LIDAR_read_word(0x8F);

    return d;
}