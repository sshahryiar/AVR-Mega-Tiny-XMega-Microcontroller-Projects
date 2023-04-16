#include "AiP650.c"


void setup(void);
unsigned int adc_avg(void);


void main(void)
{
     float t = 0.0;
     setup();
     
     while(1)
     {
         t = ((adc_avg() * 5000.0) / 1023.0);
         t = ((t - 500.0) * 0.01);
         AiP650_print_float(t);
         delay_ms(600);
     };
}


void setup(void)
{
     AiP650_init();
     ADC_Init();
}


unsigned int adc_avg(void)
{
    signed char samples = 64;
    unsigned long avg = 0;
    
    while(samples > 0)
    {
        avg += ADC_Get_Sample(0);
        samples--;
    };
    
    return (avg >> 6);
}