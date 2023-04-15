#include "SSD1306.c"


void setup();
void OLED_print(unsigned char x_pos, unsigned char y_pos, unsigned char ch);


void main()
{
     unsigned int m = 0;
     unsigned char n = 0;
     unsigned char o = 0;
     unsigned char p = 0;

     signed int i = -9;

     float f = -10.0;

     setup();
     
     OLED_clear_buffer();
     OLED_fill(0x00);

     while(1)
     {
         OLED_fill(0x00);
         OLED_fill(0xFF);
         delay_ms(600);
         OLED_fill(0xAA);
         delay_ms(600);
         OLED_fill(0x55);
         delay_ms(600);

         OLED_clear_buffer();
         OLED_fill(0x00);
         OLED_print_string(16, 0, CHR, "fb.com/MicroArena");
         Draw_Line(0, 10, 127, 10, ON);
         Draw_Line(0, 30, 127, 30, ON);
         delay_ms(900);
         Draw_Line(3, 8, 3, 32, ON);
         Draw_Line(124, 8, 124, 32, ON);
         delay_ms(900);
         Draw_Rectangle(122, 29, 5, 10, OFF, ON, SQUARE);
         delay_ms(900);
         Draw_Circle(63, 19, 7, OFF, ON);
         delay_ms(2000);
         
         OLED_clear_buffer();
         OLED_fill(0x00);
         Draw_Triangle(0, 0, 31, 31, 63, 0, NO, ON);
         Draw_Triangle(64, 31, 95, 0, 127, 31, YES, ON);
         delay_ms(2000);

         OLED_clear_buffer();
         OLED_fill(0x00);
         Draw_Rectangle(0, 31, 127, 0, ON, ON, ROUND);
         Draw_Circle(63, 15, 9, ON, OFF);
         delay_ms(2000);

         i = -9;
         f = -10.0;
         OLED_fill(0x00);
         OLED_clear_buffer();
         for(p = 0; p < 254; p++)
         {
             f += 0.1;
             i += 1;

             OLED_print_float(42, 1, CHR, f, 1);
             OLED_print_int(42, 2, CHR, i);
             OLED_print_chr(42, 3, CHR, p);

             delay_ms(99);
         }
         
         i = -9;
         f = -10.0;
         OLED_fill(0x00);
         OLED_clear_buffer();
         for(p = 0; p < 254; p++)
         {
             f += 0.1;
             i += 1;

             OLED_print_float(42, 1, NUM, f, 1);
             OLED_print_int(42, 2, NUM, i);
             OLED_print_chr(42, 3, NUM, p);

             delay_ms(99);
         }
     };
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
    TIMSK1 = 0x00;
    TIMSK2 = 0x00;
    UCSR0B = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    OLED_init();
}