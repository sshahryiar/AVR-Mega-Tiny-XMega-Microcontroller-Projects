#include "ST7735.c"


void setup();


void main() 
{
     float f = -0.09;
     signed int i = -9;
     signed char c = 127;
     
     setup();

     Set_Rotation(0x01);
     
     TFT_fill(Swap_Colour(GREEN));
     Draw_Circle(79, 63, 20, YES, Swap_Colour(RED));
     delay_ms(4000);
     
     TFT_fill(Swap_Colour(WHITE));

     Draw_Circle(6, 6, 4, YES, RED);
     Draw_Circle(153, 6, 4, YES, RED);
     Draw_Circle(6, 121, 4, YES, RED);
     Draw_Circle(153, 121, 4, YES, RED);

     delay_ms(1000);

     Draw_Line(14, 0, 14, 127, CYAN);
     Draw_Line(145, 0, 145, 127, CYAN);
     Draw_Line(0, 14, 159, 14, CYAN);
     Draw_Line(0, 113, 159, 113, CYAN);

     delay_ms(1000);

     Draw_Rectangle(17, 17, 142, 110, YES, ROUND, BLUE, WHITE);
     delay_ms(1000);

     print_str(22, 58, 2, YELLOW, BLUE, "MicroArena");
     delay_ms(4000);

     TFT_fill(BLACK);
     print_str(20, 90, 1, YELLOW, BLACK, "www.fb.com/MicroArena");

     while(1)
     {
             print_F(60, 20, 1, BLUE, BLACK, f, 2);
             print_C(60, 40, 1, RED, BLACK, c);
             print_I(60, 60, 1, GREEN, BLACK, i);
             f += 0.01;
             c -= 1;
             i += 1;
             if(c < -128)
             {
                 c = 127;
             }
             delay_ms(60);
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x1F;
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
    
    ST7735_init();
}