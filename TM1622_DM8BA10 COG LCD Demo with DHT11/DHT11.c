#include "DHT11.h"


void DHT11_init(void)
{
    DHT11_PIN_DIR_IN;
    delay_ms(100);
}


unsigned char DHT11_get_byte(void)
{
    signed char s = 0x08;
    unsigned char value = 0x00;

    while(s > 0)
    {
        value <<= 1;
        while(DHT11_GET_PIN == RESET);
        delay_us(29);

        if(DHT11_GET_PIN == SET)
        {
            value |= 1;
        }

        while(DHT11_GET_PIN == SET);
        s--;
    }
    return value;
}


unsigned char DHT11_get_data(void)
{
    unsigned char s = 0x00;
    unsigned char check_sum = 0x00;

    DHT11_PIN_DIR_OUT;
    
    DHT11_PIN_HIGH;
    DHT11_PIN_LOW;
    delay_ms(18);
    DHT11_PIN_HIGH;
    delay_us(30);

    DHT11_PIN_DIR_IN;

    if(DHT11_GET_PIN == SET)
    {
        return DHT11_sensor_error_state;
    }
    delay_us(80);
    
    if(DHT11_GET_PIN == RESET)
    {
        return DHT11_no_sensor_state;
    }
    
    delay_us(80);
    
    DHT11_PIN_DIR_IN;

    for(s = 0; s <= 4; s++)
    {
        values[s] = DHT11_get_byte();
    }

    for(s = 0; s < 4; s++)
    {
        check_sum += values[s];
    }
    
    DHT11_PIN_DIR_OUT;

    DHT11_PIN_HIGH;

    if(check_sum != values[4])
    {
        return DHT11_checksum_error_state;
    }
    else
    {
        return DHT11_normal_state;
    }
}