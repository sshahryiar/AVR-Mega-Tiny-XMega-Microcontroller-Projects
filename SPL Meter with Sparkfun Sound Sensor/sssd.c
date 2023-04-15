#include "SSD1306.c"


#define pi                    3.141593
#define sensitivity           1.995262
#define volts_per_count       0.004875
#define dB_ref                110.0
#define calibration_constant  30.6
#define no_of_samples         64


void setup();
void print_constants();
unsigned int adc_read(unsigned char channel);
void get_adc(unsigned int *audio, unsigned int *envelope);
float calculate_dB(unsigned int value);
float map(float value, float min_x, float max_x, float min_y, float max_y);
float constrain(float value, float min_value, float max_value);


void main() 
{
     unsigned char s = 0;
     unsigned char l = 0;
     unsigned char p = 0;
     
     unsigned int ch_1 = 0;
     unsigned int ch_2 = 0;
     
     float avg = 0.0;
     float peak = 0.0;
     
     setup();
     print_constants();
     
     Draw_Line(20, 16, 20, 63, ON);
     
     
     while(1)
     {
         for(s = 23; s < 127; s += 4)
         {
            get_adc(&ch_1, &ch_2);
            avg = calculate_dB(ch_1);
            peak = calculate_dB(ch_2);
            OLED_print_float(0, 1, avg, 1);
            OLED_print_float(92, 1, peak, 1);
            
            l = map(avg, 30, 126, 0, 47);
            l = constrain(l, 0, 47);
            p = map(peak, 30, 126, 0, 47);
            p = constrain(p, 0, 47);
            Draw_Rectangle(s, 63, (3 + s), 16, YES, OFF, SQUARE);
            Draw_Rectangle(s, 63, (3 + s), (63 - l), YES, ON, SQUARE);
            Draw_Rectangle(s, (63 - p), (3 + s), (63 - p), YES, ON, SQUARE);
         }

     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    ASSR = 0x00;
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    TCNT2 = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    EICRA = 0x00;
    EIMSK = 0x00;
    PCICR = 0x00;
    TIMSK0 = 0x00;
    TIMSK1 = 0x00;
    TIMSK2 = 0x00;
    UCSR0B = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    DIDR0 = 0x3F;
    ADMUX = 0x40;
    ADCSRA = 0xA6;
    ADCSRB &= 0xF8;
    SPCR = 0x00;
    TWCR = 0x00;
    
    OLED_init();
    OLED_fill(0x00);
}


void print_constants()
{
    OLED_print_string(0, 0, "Avg/dB");
    OLED_print_string(85, 0, "Peak/dB");
    OLED_print_string(0, 2, "dB");
    OLED_print_string(0, 3, "126");
    OLED_print_string(6, 5, "78");
    OLED_print_string(6, 7, "30");
}


unsigned int adc_read(unsigned char channel)
{
    unsigned int adc_res = 0;
    unsigned int temp = 0;
    
    ADMUX = 0x40;
    ADMUX |= (0xFF & channel);
    delay_us(10);
    ADCSRA |= 0x40;
    while(!(ADCSRA & 0x10));
    ADCSRA |= 0x10;
    adc_res = ADCL;
    temp = ADCH;
    temp <<= 8;
    adc_res |= temp;
    
    if(adc_res < 1)
    {
        return 1;
    }
    
    else
    {
        return adc_res;
    }
}


void get_adc(unsigned int *audio, unsigned int *envelope)
{
    unsigned char samples = no_of_samples;
    
    signed int tmp = 0;
    unsigned int ch_a = 0;
    unsigned int ch_b = 0;
    
    unsigned long rms = 0;
    
    while(samples > 0)
    {
        tmp = (adc_read(1) - 511.0);
        rms += (tmp * tmp);
        delay_us(10);
        
        ch_b += adc_read(0);
        delay_us(10);
        
        samples--;
    }
    
    rms >>= 6;
    ch_a = ((unsigned int)sqrt(rms));
    
    *audio = ch_a;
    *envelope = ((ch_b >> 6) * (pi / 2.0));
}


float calculate_dB(unsigned int value)
{
    float v = 0.0;
    
    v = (value * volts_per_count);
    v /= sensitivity;
    v = (dB_ref + (20.0 * log10(v)));
    v -= calibration_constant;
    
    return v;
}


float map(float value, float min_x, float max_x, float min_y, float max_y)
{
    return (min_y + (((max_y - min_y)/(max_x - min_x)) * (value - min_x)));
}


float constrain(float value, float min_value, float max_value)
{
    if(value >= max_value)
    {
         return max_value;
    }
    else if(value <= min_value)
    {
         return min_value;
    }
    else
    {
         return value;
    }
}