#include "SSD1306.c"
#include "logo_art.c"


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
         OLED_fill(0xFF);
         delay_ms(600);
         OLED_fill(0xAA);
         delay_ms(600);
         OLED_fill(0x55);
         delay_ms(600);

         OLED_clear_buffer();
         OLED_fill(0x00);
         OLED_print_Image(mikro_logo, ON);
         delay_ms(1600);
         
         OLED_clear_buffer();
         OLED_fill(0x00);
         OLED_print_Image(mikro_logo, OFF);
         delay_ms(1600);

         OLED_clear_buffer();
         OLED_fill(0x00);
         OLED_print_string(36, 0, "MicroArena");
         OLED_print_string(16, 1, "fb.com/MicroArena");
         Draw_Line(0, 19, 127, 19, ON);
         Draw_Line(0, 60, 127, 60, ON);
         delay_ms(900);
         Draw_Line(3, 16, 3, 63, ON);
         Draw_Line(124, 16, 124, 63, ON);
         delay_ms(900);
         Draw_Rectangle(122, 58, 5, 21, OFF, ON, SQUARE);
         delay_ms(900);
         Draw_Circle(63, 40, 7, ON, ON);
         delay_ms(2000);

         OLED_fill(0x00);
         OLED_clear_buffer();
         OLED_print_string(36, 0, "SShahyriar");
         Draw_Rectangle(27, 21, 100, 58, ON, ON, ROUND);
         delay_ms(900);
         Draw_Circle(63, 40, 9, ON, OFF);
         delay_ms(2000);

         OLED_fill(0x00);
         OLED_clear_buffer();
         for(p = 0; p < 254; p++)
         {
             f += 0.1;
             i += 1;

             OLED_print_float(42, 2, f, 1);
             OLED_print_int(42, 3, i);
             OLED_print_chr(42, 4, p);

             delay_ms(99);
         }
     };
}


void setup()
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    OCR0 = 0x00;
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
    MCUCSR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    OLED_init();
}