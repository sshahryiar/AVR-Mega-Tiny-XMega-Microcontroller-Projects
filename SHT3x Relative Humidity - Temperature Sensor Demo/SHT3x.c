#include "SHT3x.h"


unsigned int make_word(unsigned char hb, unsigned char lb)
{
    unsigned int value = 0x0000;

    value = hb;
    value <<= 0x08;
    value |= lb;

    return value;
}


void SHT3x_init(void)
{
    TWI_Init(I2C_bus_speed);
    delay_ms(100);
    SHT3x_reset();
    SHT3x_heater_state(SHT3x_heater_off);
}


void SHT3x_reset(void)
{
    SHT3x_write_command(SHT3x_SOFT_RESET);
    delay_ms(15);
}


unsigned int SHT3x_read_status_reg(void) 
{
    unsigned char crc = 0x00;
    unsigned char lb = 0x00;
    unsigned int hb = 0x0000;

    SHT3x_write_command(SHT3x_READ_STATUS);

    TWI_Start();
    TWI_Write(SHT3x_I2C_address | 1);
    hb = TWI_Read(1);
    lb = TWI_Read(1);
    crc = TWI_Read(0);
    TWI_Stop();

    hb <<= 0x08;
    hb |= lb;

    return hb;
}


void SHT3x_heater_state(unsigned char state)
{
    switch(state)
    {
        case SHT3x_heater_on:
        {
            SHT3x_write_command(SHT3x_ENABLE_INTERNAL_HEATER);
            break;
        }

        default:
        {
            SHT3x_write_command(SHT3x_DISABLE_INTERNAL_HEATER);
            break;
        }
    };
}


void SHT3x_write_command(unsigned int value)
{
    unsigned char hb = 0x00;
    unsigned char lb = 0x00;

    lb = (value & 0x00FF);
    hb = ((value & 0xFF00) >> 0x08);
    
    TWI_Start();
    TWI_Write(SHT3x_I2C_address);
    TWI_Write(hb);
    TWI_Write(lb);
    TWI_Stop();
}


unsigned char SHT3x_calculate_crc8(unsigned char *value) 
{
    signed char i = 0x00;
    signed char j = 0x00;
    unsigned char crc_value = 0xFF;

    for(i = 0x00; i < 0x02; i++)
    {
        crc_value ^= value[i];

        for(j = 0x08; j > 0x00; --j)
        {
           if(crc_value & 0x80)
           {
               crc_value = ((crc_value << 1) ^ 0x131);
           }
           else
           {
               crc_value <<= 1;
           }
        };
    };

    return crc_value;
}


unsigned char SHT3x_read_temp_humidity(float *sht_t, float *sht_rh)
{
    unsigned char read_buffer[0x06] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    signed long t_tmp = 0x0000;
    signed long h_tmp = 0x0000;
    float t_value = 0.0;
    float h_value = 0.0;

    SHT3x_write_command(SHT3x_MEAS_HIGH_REP);
    delay_ms(20);
    
    TWI_Start();
    TWI_Write(SHT3x_I2C_address | 1);
    read_buffer[0x00] = TWI_Read(1);
    read_buffer[0x01] = TWI_Read(1);
    read_buffer[0x02] = TWI_Read(1);
    read_buffer[0x03] = TWI_Read(1);
    read_buffer[0x04] = TWI_Read(1);
    read_buffer[0x05] = TWI_Read(0);
    TWI_Stop();

    if((read_buffer[0x02] != SHT3x_calculate_crc8(read_buffer)) || (read_buffer[0x05] != SHT3x_calculate_crc8((read_buffer + 0x03))))
    {
        return SHT3x_ERROR;
    }

    t_tmp = make_word(read_buffer[0x00], read_buffer[0x01]);
    t_tmp = (((4375 * t_tmp) >> 14) - 4500);
    t_value = (((float)t_tmp) / 100.0);
    *sht_t = t_value;

    h_tmp = make_word(read_buffer[0x03], read_buffer[0x04]);
    h_tmp = ((625 * h_tmp) >> 12);
    h_value = (((float)h_tmp) / 100.0);
    
    *sht_rh = h_value;
    
    return SHT3x_NO_ERROR;
}