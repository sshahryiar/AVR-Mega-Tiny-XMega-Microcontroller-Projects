#include "SHT1x.h"


void SHT1x_init(void)
{
    SDA_Direction = INPUT;
    SCL_Direction = OUTPUT;
    SDA_Out_Pin = HIGH;
}


void SHT1x_start(void)
{
    SDA_Direction = INPUT;
    SCL_Pin = HIGH;
    delay_us(1);
    SDA_Direction = HIGH;
    SDA_Out_Pin = LOW;
    delay_us(1);
    SCL_Pin = LOW;
    delay_us(1);
    SCL_Pin = HIGH;
    delay_us(1);
    SDA_Direction = INPUT;
    delay_us(1);
    SCL_Pin = LOW;
}


unsigned char SHT1x_read_byte(unsigned char acknowledgement)
{
    unsigned char s = 0x80;
    unsigned char temp_val = 0x00;

    SDA_Direction = INPUT;
    SDA_Out_Pin = HIGH;
    SCL_Pin = LOW;

    while(s > 0)
    {
        SCL_Pin = HIGH;
        delay_us(1);

        if(SDA_In_Pin == HIGH)
        {
            temp_val = (temp_val | s);
        }

        SCL_Pin = LOW;
        delay_us(1);
        s >>= 1;
    }

    SDA_Direction = OUTPUT;

    if(acknowledgement == ACK)
    {
        SDA_Out_Pin = LOW;
    }
    else
    {
        SDA_Out_Pin = HIGH;
    }

    SCL_Pin = HIGH;
    delay_us(3);
    SCL_Pin = LOW;
    delay_us(1);

    SDA_Direction = INPUT;
    SDA_Out_Pin = HIGH;

    return temp_val;
}


unsigned char SHT1x_write_byte(unsigned char value)
{
    unsigned char s = 0x80;
    unsigned char error = 0x00;

    SDA_Direction = OUTPUT;

    while(s > 0)
    {
        if(s & value)
        {
            SDA_Out_Pin = HIGH;
        }
        else
        {
            SDA_Out_Pin = LOW;
        }

        SCL_Pin = HIGH;
        delay_us(3);
        SCL_Pin = LOW;
        delay_us(3);
        s >>= 1;
    }

    SDA_Direction = INPUT;
    SDA_Out_Pin = HIGH;

    SCL_Pin = HIGH;
    delay_us(3);
    if(SDA_In_Pin == HIGH)
    {
        error = 1;
    }
    delay_us(1);
    SCL_Pin = LOW;

    return error;
}


unsigned char SHT1x_measure(unsigned int *p_value, unsigned char mode)
{
    unsigned char s = 0x00;
    unsigned char hb = 0x00;
    unsigned char lb = 0x00;
    unsigned char CRC = 0x00;

    *p_value = 0;
    SHT1x_start();

    if(mode)
    {
        mode = measure_RH_cmd;
    }
    else
    {
        mode = measure_T_cmd;
    }

    if (SHT1x_write_byte(mode))
    {
        return 1;
    }

    SDA_Direction = 0;

    while(s < 240)
    {
        delay_ms(3);
        if(SDA_In_Pin == LOW)
        {
            s = 0;
            break;
        }
        s++;
    }

    if(s) 
    {
        return 2;
    }

    hb = SHT1x_read_byte(ACK);
    lb = SHT1x_read_byte(ACK);
    CRC = SHT1x_read_byte(NACK);

    *p_value = ((hb << 8) | lb);

    return 0;
}


float SHT1x_calc_temperature(unsigned int t)
{
    float temp_val = 0.0;

    temp_val = ((t * 0.01) - 39.6);

    return temp_val;
}


float SHT1x_calc_humidity(unsigned int h, unsigned int t)
{
    float rh_lin = 0.0;
    float rh_true = 0.0;
    float t_C = 0.0;

    t_C = ((t * 0.01) - 39.6);
    rh_lin = ((C3 * h * h) + (C2 * h) + C1);
    rh_true = ((t_C - 25) * (T1 + T2 * h) + rh_lin);

    if(rh_true > 100)
    {
        rh_true = 100;
    }
    if(rh_true < 0.1)
    {
        rh_true = 0.1;
    }
    return rh_true;
}


float SHT1x_get_dew_point(float s_t, float s_rh)
{
    float dew_point = 0.0;
    
    dew_point = ((log(s_rh / 100.0)) + ((17.62 * s_t) / (243.12 + s_t)));
    dew_point = ((243.12 * dew_point) / (17.62 - dew_point));
    
    return dew_point;
}


void Read_SHT1x(float *fT, float *fRH)
{
    unsigned int t = 0x0000;
    unsigned int h = 0x0000;
    float value = 0.0;

    SHT1x_Error = 0;

    SHT1x_Error = SHT1x_measure(&t, 0);
    SHT1x_T = (signed int)(SHT1x_calc_temperature(t) * 10);

    SHT1x_Error = SHT1x_measure(&h, 1);
    SHT1x_H = (signed int)(SHT1x_calc_humidity(h, t) * 10);

    value = ((float)SHT1x_T);
    *fT = (value / 10.0);
    value = ((float)SHT1x_H);
    *fRH = (value / 10.0);
}


signed char SHT1x_read_status_reg(unsigned char *p_value)
{
    unsigned char CRC = 0x00;

    SHT1x_start();
    
    if(SHT1x_write_byte(read_status_reg_cmd))
    {
        return 1;
    }

    *p_value = SHT1x_read_byte(ACK);
    CRC = SHT1x_read_byte(NACK);

    return 0;
}


signed char SHT1x_write_status_reg(unsigned char value)
{
    SHT1x_start();

    if(SHT1x_write_byte(write_status_reg_cmd))
    {
        return 1;
    }
    if(SHT1x_write_byte(value))
    {
        return 1;
    }

    return 0;
}


void SHT1x_connection_reset(void)
{
    unsigned char s = 0x09;

    SDA_Direction = 0;
    SDA_Out_Pin = 1;
    SCL_Pin = 0;

    while(s > 0)
    {
        SCL_Pin = 1;
        delay_us(3);
        SCL_Pin = 0;
        delay_us(3);
        s--;
    }

    SHT1x_start();
}


unsigned char SHT1x_soft_reset(void)
{
    SHT1x_connection_reset();
    return (SHT1x_write_byte(soft_reset_cmd));
}