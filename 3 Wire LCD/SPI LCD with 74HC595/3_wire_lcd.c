#include "lcd.c"


void setup();


void main() 
{
     unsigned char txt[6];
     const unsigned char msg[11] = {"MicroArena"};

     unsigned char s = 0;

     setup();



     while(1)
     {
             LCD_clear_home();

             LCD_goto(3, 0);
             LCD_putstr("SShahryiar");
             delay_ms(900);
             
             LCD_goto(3, 0);
             LCD_putstr("MicroArena");
             
             for(s = 0; s < 250; s++)
             {

                   LCD_goto(6, 1);
                   ByteToStr(s, txt);
                   LCD_putstr(txt);
                   delay_ms(200);
             }
             
             LCD_clear_home();
             LCD_goto(1, 0);
             LCD_putstr("facebook.com/");
             for(s = 0; s <= 9; s++)
             {
                 LCD_goto((s + 3), 1);
                 LCD_putchar(msg[s]);
                 delay_ms(220);
             }
             delay_ms(2000);

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