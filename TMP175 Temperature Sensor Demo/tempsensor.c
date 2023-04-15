#include "TMPx75.c"


#define SEG_DAT        PORTA3_bit
#define SEG_COL        PORTA4_bit

#define OE             PORTA7_bit


const unsigned char seg[0x06] = {0x3E, 0x3D, 0x3B, 0x37, 0x2F, 0x1F};
const unsigned char num[0x0A] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};


signed char i = 0x00;
signed char j = 0x00;
unsigned long value = 0x00000000;


void setup(void);


void Timer1_ISR(void)
iv IVT_ADDR_TIMER1_OVF 
ics ICS_AUTO
{
    TCNT1H = 0xF4;
    TCNT1L = 0x48;

    SEG_DAT = 1;

    switch(i)
    {
        case 0:
        {
            j = ((unsigned long)(value / 100000));
            PORTB = num[j];
            break;
        }
        
        case 1:
        {
            j = ((unsigned long)((value % 100000) / 10000));
            PORTB = num[j];
            break;
        }
        
        case 2:
        {
            j = ((unsigned long)((value % 10000) / 1000));
            PORTB = num[j] | 0x80;
            break;
        }
        
        case 3:
        {
            j = ((unsigned long)((value % 1000) / 100));
            PORTB = num[j];
            break;
        }
        
        case 4:
        {
            j = ((unsigned long)((value % 100) / 10));
            PORTB = num[j];
            break;
        }
        
        case 5:
        {
            j = ((unsigned long)(value % 10));
            PORTB = num[j];
            break;
        }
    }
    
    SEG_DAT = 0;

    SEG_COL = 1;
    PORTB = seg[i];
    SEG_COL = 0;

    i++;
    
    if(i > 5)
    {
        i = 0x00;
    }
}


void main() 
{
     float t  = 0.0;
     
     setup();

     while(1)
     {
        t = TMPx75_get_temp();
        value = (t * 1000.0);
        delay_ms(650);
     };
}


void setup(void)
{
    DDRA = 0x9C;
    PORTA = 0x00;
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRC = 0x00;
    PORTC = 0x00;
    DDRD = 0x00;
    PORTD = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    OCR0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x02;
    TCNT1H = 0xF4;
    TCNT1L = 0x48;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    ASSR = 0x00;
    TCCR2 = 0x00;
    TCNT2 = 0x00;
    OCR2 = 0x00;
    TIMSK = 0x04;
    MCUCR = 0x00;
    MCUCSR = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    asm sei;
    TMPx75_init();
    OE = 0;
}