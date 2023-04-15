#include "font.h"
#include "TM1640.c"
#include "MPL115A1.c"


void setup(void);
void display_data(unsigned char segment, signed long value);


void main() 
{


     
     float p = 0.0;
     float t = 0.0;
     
     setup();

     
     while(1)
     {
         TM1640_send_data(4, 0x00);
         TM1640_send_data(5, 0xFF);
         TM1640_send_data(6, 0x00);
         TM1640_send_data(7, 0xFF);
         
         MPL115A1_get_data(&p, &t);
         
         display_data(0, t);
         display_data(13, p);
         delay_ms(400);
         
         TM1640_send_data(4, 0xFF);
         TM1640_send_data(5, 0x00);
         TM1640_send_data(6, 0xFF);
         TM1640_send_data(7, 0x00);
         delay_ms(400);
     };
}


void setup(void)
{
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
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
    TCCR2 = 0x00;
    TCNT2 = 0x00;
    OCR2 = 0x00;
    MCUCR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x83;
    ADMUX = 0x40;
    SPCR = 0x00;
    TWCR = 0x00;
   
    TM1640_init(brightness_75_pc);
    MPL115A1_init();
}


void display_data(unsigned char segment, signed long value)
{
    unsigned char ch = 0;
    
    if((value > 99) && (value <= 999))
    {
      ch = (value / 100);
      TM1640_send_data(segment, font[16 + ch]);

      ch = ((value / 10) % 10);
      TM1640_send_data((1 + segment), font[16 + ch]);

      ch = (value % 10);
      TM1640_send_data((2 + segment), font[16 + ch]);
    }
    
    else if((value > 9) && (value <= 99))
    {
      TM1640_send_data(segment, 0);

      ch = (value / 10);
      TM1640_send_data((1 + segment), font[16 + ch]);

      ch = (value % 10);
      TM1640_send_data((2 + segment), font[16 + ch]);
    }
    
    else
    {
      TM1640_send_data(segment, 0);

      TM1640_send_data((1 + segment), 0);

      ch = (value % 10);
      TM1640_send_data((2 + segment), font[16 + ch]);
    }
}