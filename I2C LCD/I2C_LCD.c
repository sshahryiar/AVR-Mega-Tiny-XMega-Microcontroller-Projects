#include "lcd.c"


void setup();


void main()
{
     unsigned char txt[6];
     const unsigned char msg[18] = {"fb.com/MicroArena"};

     unsigned char i = 0;

     setup();



     while(1)
     {
             LCD_clear_home();
             LCD_goto(6, 1);
             LCD_putstr("MicroArena");
             delay_ms(600);
             
             for(i = 0; i < 17; i++)
             {
                 LCD_goto((2 + i), 2);
                 LCD_putchar(msg[i]);
                 delay_ms(120);
             }

             delay_ms(400);
             LCD_goto(6, 4);
             LCD_putstr("SShahryiar");
             
             for(i = 0; i < 250; i++)
             {
             
                   LCD_goto(9, 3);
                   ByteToStr(i, txt);
                   LCD_putstr(txt);
                   i++;
                   delay_ms(200);
             }
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x18;
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