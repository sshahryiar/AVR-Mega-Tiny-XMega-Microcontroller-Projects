#include "PCA9685.c"


void setup();


void main() 
{
     signed char j = 0;
     signed int i = 0;
     unsigned int v = 0;
     
     setup();

    
     while(1)
     {
         for(j = 0; j < 16; j += 2)
         {
             for(i = 0; i <= 180; i++)
             {
                 v = (MAX_count * sin(0.0174 * i));
                 PCA9685_set_PWM_duty(j, v, (j * 256));
                 delay_ms(1);
             }
         }
         
         for(j = 15; j > 0; j -= 2)
         {
             for(i = 0; i <= 180; i++)
             {
                 v = (MAX_count * sin(0.0174 * i));
                 PCA9685_set_PWM_duty(j, v, (j * 256));
                 delay_ms(1);
             }
         }
         
         
         for(j = 0; j < 16; j += 2)
         {
             for(i = 0; i <= 180; i++)
             {
                 v = (MAX_count * cos(0.0174 * i));
                 PCA9685_set_PWM_duty(j, v, (j * 256));
                 delay_ms(1);
             }
         }

         for(j = 15; j > 0; j -= 2)
         {
             for(i = 0; i < 180; i++)
             {
                 v = (MAX_count * cos(0.0174 * i));
                 PCA9685_set_PWM_duty(j, v, (j * 256));
                 delay_ms(1);
             }
         }
     }
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
    TIMSK1 = 0x01;
    TIMSK2 = 0x00;
    UCSR0B = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    
    PCA9685_init();
}