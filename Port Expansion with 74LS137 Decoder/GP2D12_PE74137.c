#include <tiny13a.h>
#include <delay.h>


void setup()
{
        CLKPR = 0x80;
        CLKPR = 0x00;
        DDRB = 0x07;
        TCCR0A = 0x00;
        TCCR0B = 0x00;   
        TIMSK0 = 0x00;
        TCNT0 = 0x00;
        OCR0A = 0x00;
        OCR0B = 0x00;
        GIMSK = 0x00;
        MCUCR = 0x00;
        ACSR = 0x80;
        ADCSRB = 0x00;
        DIDR0 &= 0x03;
        DIDR0 |= 0x00;
        ADMUX = 0x00;
        ADCSRA = 0x86;  
        PORTB = 0x00;
}


unsigned int read_adc()
{
        ADMUX = 0x03;
        delay_us(10);
        ADCSRA |= 0x40;
        while (!(ADCSRA & 0x10));
        ADCSRA |= 0x10;
        return ADCW;
}


void main(void)
{
        unsigned int v = 0;
        unsigned int tmp = 0;
        unsigned char val = 0;
        unsigned char cnt = 0;    
        const unsigned int d[8] = {480, 270, 190, 150, 125, 100, 90, 80};
        setup();
        while (1)
        {      
            v = read_adc(); 
            cnt = 0;
            while(cnt < 8)
            {
                tmp = d[cnt];
                if(v <= tmp)
                {
                     val = cnt;
                }   
                cnt++;
            }         
            PORTB = val;
            delay_ms(500);
        }
}
