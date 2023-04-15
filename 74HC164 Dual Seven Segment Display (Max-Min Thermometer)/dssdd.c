#include "DS18B20.c"


#define DAT_pin                         PORTD0_bit
#define CP_pin                          PORTD1_bit

#define HIGH                                     1
#define LOW                                      0

#define TCNT1L_value                          0x00
#define TCNT1H_value                          0xE4


const unsigned char pos[0x08] =
{
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};


const unsigned char num[0x0A] =
{
    0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09
};


unsigned char i = 0x00;

signed int value_1 = 0;
signed int value_2 = 0;


void setup(void);
void Write_74HC164(unsigned char val, unsigned char seg);


void Timer1_Overflow(void) 
iv IVT_ADDR_TIMER1_OVF 
ics ICS_AUTO 
{
    TCNT1H = TCNT1H_value;
    TCNT1L = TCNT1L_value;
    
    switch(i)
    {
        case 0:
        {
            Write_74HC164(num[(value_1 / 1000)], pos[3]);
            break;
        }

        case 1:
        {
            Write_74HC164((num[((value_1 % 1000) / 100)] & 0xFE), pos[2]);
            break;
        }

        case 2:
        {
            Write_74HC164(num[((value_1 % 100) / 10)], pos[1]);
            break;
        }

        case 3:
        {
            Write_74HC164(num[(value_1 % 10)], pos[0]);
            break;
        }

        case 4:
        {
            Write_74HC164(num[(value_2 / 1000)], pos[7]);
            break;
        }

        case 5:
        {
            Write_74HC164((num[((value_2 % 1000) / 100)] & 0xFE), pos[6]);
            break;
        }

        case 6:
        {
            Write_74HC164(num[((value_2 % 100) / 10)], pos[5]);
            break;
        }

        case 7:
        {
            Write_74HC164(num[(value_2 % 10)], pos[4]);
            break;
        }
    }

    i++;

    if(i >= 8)
    {
        i = 0;
    }
}


void main(void)
{
    unsigned long s = 0;
    
    signed int t = 0;
    
    signed int t_l = 10000;
    signed int t_h = 0;
    
    setup();

    while (1)
    {
      t = get_temp();
      
      if(t < t_l)
      {
         t_l = t;
         value_1 = t_l;
      }
      
      if(t > t_h)
      {
         t_h = t;
         value_2 = t_h;
      }
      
      delay_ms(100);
      
      s++;
      if(s > 1000)
      {
         s = 0;
         t_l = 10000;
         t_h = 0;
      }
    }
}


void setup(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x03;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x02;
    TCNT1H = TCNT1H_value;
    TCNT1L = TCNT1L_value;
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
    asm sei;
}


void Write_74HC164(unsigned char val, unsigned char seg)
{
    unsigned char s = 0x10;
    unsigned int temp = 0x0000;

    temp = (unsigned int)seg;
    temp <<= 8;
    temp |= (unsigned int)val;

    while(s > 0)
    {
        if((temp & 0x0001) != 0x0000)
        {
            DAT_pin = HIGH;
        }
        else
        {
            DAT_pin = LOW;
        }

        CP_pin = HIGH;
        CP_pin = LOW;

        temp >>= 1;
        s--;
    }
}