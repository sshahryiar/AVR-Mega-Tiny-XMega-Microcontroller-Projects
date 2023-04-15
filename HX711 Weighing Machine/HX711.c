#include "HX711.h"


void HX711_init(void)
{
     zero_value = 0;
     
     zero_value = HX711_avg();
}


unsigned long HX711_read(void)
{
    unsigned char s = 24;
    unsigned long cnt = 0;

    HX711_SCLK = LOW;

    while(HX711_DATA == HIGH);

    while(s > 0)
    {
        HX711_SCLK = HIGH;
        cnt <<= 1;

        HX711_SCLK = LOW;

        if(HX711_DATA == HIGH)
        {
            cnt++;
        }
        
        s--;
    };

    HX711_SCLK = HIGH;

    cnt ^= 0x800000;

    HX711_SCLK = LOW;

    return cnt;
}


unsigned long HX711_avg(void)
{
    unsigned char s = 16;
    unsigned long long value = 0;
    
    while(s > 0)
    {
        value += HX711_read();
        delay_ms(10);
        s--;
    };
    
    value >>= 4;
    
    value -= zero_value;
    
    return (unsigned long)value;
}


float HX711_get_mass(void)
{
    float temp = 0.0;
    
    temp = ((float)HX711_avg() / scale_factor);
    
    if((temp < 0) || (temp > 5000))
    {
        temp = 0;
    }
    
    return temp;
}
