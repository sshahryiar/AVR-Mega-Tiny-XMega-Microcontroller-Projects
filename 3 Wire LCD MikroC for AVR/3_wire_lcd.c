#include "lcd.c"


void setup();


void main() 
{
     unsigned char msg[] = {"MicroArena"};
     unsigned char txt[6];

     unsigned char i = 0;

     setup();

     LCD_goto(3, 0);
     LCD_putstr(msg);

     while(1)
     {
             LCD_goto(6, 1);
             ByteToStr(i, txt);
             LCD_putstr(txt);
             i++;
             delay_ms(100);
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x1C;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    PLLCSR = 0x00;
    TCCR1 = 0x00;
    GTCCR = 0x00;
    TCNT1 = 0x00;
    OCR1A = 0x00;
    OCR1B = 0x00;
    OCR1C = 0x00;
    GIMSK = 0x00;
    MCUCR = 0x00;
    TIMSK = 0x00;
    USICR = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR0 = 0x00;
    ADCSRA = 0x00;
    
    LCD_init();
}