#include "other_interfaces.h"


void other_interfaces_init()
{
    DDD4_bit = 1;

    UART1_Init_Advanced(9600, _UART_NOPARITY, _UART_ONE_STOPBIT);
    delay_ms(100);
}


unsigned int ADC_Read(unsigned char channel)
{
    unsigned int temp1 = 0;
    unsigned int temp2 = 0;
    
    ADMUX = (channel | 0x40);
    delay_us(10);
    ADCSRA |= 0x40;
    while(!(ADCSRA & 0x10));
    ADCSRA |= 0x10;
    temp1 = ADCL;
    temp2 = ADCH;
    temp2 <<= 8;
    temp1 |= temp2;
    
    return temp1;
}


unsigned int adc_avg(unsigned char channel)
{
    unsigned char samples = 0x40;
    unsigned int avg = 0x0000;
    
    while(samples > 0x00)
    {
        avg += ADC_Read(channel);
        samples--;
    }
    
    avg >>= 6;

    return avg;
}


float map(float value, float xp_min, float xp_max, float yp_min, float yp_max)
{
    return (yp_min + (((yp_max - yp_min)/(xp_max - xp_min)) * (value - xp_min)));
}


float constrain(float value, float value_min, float value_max)
{
      if(value >= value_max)
      {
           return value_max;
      }
      else if(value <= value_min)
      {
           return value_min;
      }
      else
      {
           return value;
      }
}


float get_wind_speed()
{
    float temp_val = 0.0;

    temp_val = map(((float)adc_avg(wind_pin)), min_ADC_count_at_no_wind, max_ADC_count, wind_speed_min, wind_speed_max);
    temp_val = constrain(temp_val, wind_speed_min, wind_speed_max);

    return temp_val;
}


float get_bv()
{
    float temp_val = 0.0;
    
    temp_val = adc_avg(batt_pin);
    temp_val = map(((float)adc_avg(batt_pin)), 0.0, max_ADC_count, 0, nominal_VDD);
    temp_val *= batt_divider_ratio;
    
    return temp_val;
}


unsigned int get_lux()
{
    float temp_val = 0.0;
    
    temp_val = adc_avg(TEMT6000_pin);
    temp_val = map(((float)adc_avg(TEMT6000_pin)), 0.0, max_ADC_count, 0, nominal_VDD);
    temp_val = ((nominal_VDD - temp_val) / TEMT6000_fixed_resistor_value_in_k_ohms);
    temp_val *= gain;
    
    return ((unsigned int)temp_val);
}