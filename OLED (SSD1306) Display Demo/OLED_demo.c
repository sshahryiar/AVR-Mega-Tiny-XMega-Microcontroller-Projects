#include "SSD1306.c"


void setup();


void main() 
{
     unsigned int m = 0;
     unsigned char n = 0;
     unsigned char o = 0;
     unsigned char p = 0;
     
     signed int i = -9;
     
     float f = -10.0;

     setup();
     
     while(1)
     {
         i = -9;
         f = -10.0;
         
         OLED_fill(0x00);
         OLED_fill(0xAA);
         delay_ms(600);
         
         OLED_fill(0x55);
         delay_ms(600);
         
         OLED_fill(0x00);
         OLED_clear_buffer();
         for(m = 18; m < 114; m += 10)
         {
             for(n = 12;  n < 57; n += 8)
             {
                 Draw_Circle(m, n, 4, ON, ON);
                 delay_ms(99);
             }
         }
         delay_ms(1600);
         
         OLED_fill(0x00);
         OLED_clear_buffer();
         for(m = 0; m < 132; m += 10)
         {
             for(n = 0; n < 64; n += 8)
             {
                Draw_Line(m, n, 131, 63, ON);
                delay_ms(99);
             }
         }
         delay_ms(1600);
         
         OLED_fill(0x00);
         OLED_clear_buffer();
         for(m = 0; m < 132; m += 10)
         {
             for(n = 0; n < 64; n += 8)
             {
                Draw_Rectangle(m, 0, 131, n, OFF, ON, ROUND);
             }
         }
         delay_ms(1600);
         
         
         OLED_fill(0x00);
         OLED_print_string(36, 2, "MicroArena");
         for(p = 0; p < 250; p++)
         {
             f += 0.1;
             i += 1;

             OLED_print_float(1, 5, f, 1);
             OLED_print_int(1, 6, i);
             OLED_print_chr(1, 7, p);
             
             delay_ms(99);
         }
         
         OLED_fill(0xFF);
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0xFF;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x1F;
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
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    PORTB = 0x20;
    OLED_init();
}