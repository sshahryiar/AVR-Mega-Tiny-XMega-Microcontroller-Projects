#include "HMC5883L.c"


signed int h = 0;

unsigned char n = 0;
unsigned char pos = 1;

const unsigned char num[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x63};


void setup();


void display()
org IVT_ADDR_TIMER0_OVF
{
    TCNT0 = 0x00;
    switch(pos)
    {
        case 1:
        {
            n = (h / 100);
            PORTB = (num[n]);
            PORTC &= 0xF0;
            PORTC |= 0x08;
            break;
        }
        case 2:
        {
            n = ((h % 100) / 10);
            PORTB = (num[n]);
            PORTC &= 0xF0;
            PORTC |= 0x04;
            break;
        }
        case 3:
        {
            n = (h % 10);
            PORTB = (num[n]);
            PORTC &= 0xF0;
            PORTC |= 0x02;
            break;
        }
        case 4:
        {
            PORTB = (num[10]);
            PORTC &= 0xF0;
            PORTC |= 0x01;
            break;
        }
    }
    
    pos += 1;
    if(pos > 4)
    {
        pos = 1;
    }
}


void main() 
{
     setup();
     while(1)
     {
             h = HMC5883L_heading();
             delay_ms(100);
     }
}


void setup()
{
      CLKPR = 0x80;
      CLKPR = 0x00;
      PORTB = 0x00;
      DDRB = 0xFF;
      PORTC = 0x00;
      DDRC = 0x0F;
      PORTD = 0x00;
      DDRD = 0x00;
      TCCR0A = 0x00;
      TCCR0B = 0x03;
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
      TIMSK0 = 0x01;
      TIMSK1 = 0x00;
      TIMSK2 = 0x00;
      UCSR0B = 0x00;
      ACSR = 0x80;
      ADCSRB = 0x00;
      DIDR1 = 0x00;
      ADCSRA = 0x00;
      SPCR = 0x00;
      TWCR = 0x00;
      SREG_I_bit = 1;
      HMC5883L_init();
}