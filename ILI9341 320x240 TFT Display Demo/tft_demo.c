#include "bmp.c"
#include "XPT2046.c"
#include "ILI9341.c"


void setup();
void test_RGB();
void test_colours();
void test_2D_graphics();
void draw_flag();
void print_test_data();
void print_image();


void main()
{
    setup();

    test_RGB();
    print_test_data();
    test_colours();
    test_2D_graphics();
    draw_flag();
    print_image();
    print_str(4, 0, 1, White, Black, "Draw Check");

    while(1)
    {
        if(TP_INT_pin == low)
        {
            TP_read_coordinates(&tpx, &tpy);
            Draw_Pixel(tpx, tpy, White);
        }
    };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
    PORTE = 0x00;
    DDRE = 0x00;
    PORTF = 0x00;
    DDRF = 0x00;
    PORTG = 0x00;
    DDRG = 0x00;
    PORTH = 0x00;
    DDRH = 0x00;
    PORTJ = 0x00;
    DDRJ = 0x00;
    PORTK = 0x00;
    DDRK = 0x00;
    PORTL = 0x00;
    DDRL = 0x00;
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
    OCR1CH = 0x00;
    OCR1CL = 0x00;
    ASSR = 0x00;
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    TCNT2 = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    TCCR3A = 0x00;
    TCCR3B = 0x00;
    TCNT3H = 0x00;
    TCNT3L = 0x00;
    ICR3H = 0x00;
    ICR3L = 0x00;
    OCR3AH = 0x00;
    OCR3AL = 0x00;
    OCR3BH = 0x00;
    OCR3BL = 0x00;
    OCR3CH = 0x00;
    OCR3CL = 0x00;
    TCCR4A = 0x00;
    TCCR4B = 0x00;
    TCNT4H = 0x00;
    TCNT4L = 0x00;
    ICR4H = 0x00;
    ICR4L = 0x00;
    OCR4AH = 0x00;
    OCR4AL = 0x00;
    OCR4BH = 0x00;
    OCR4BL = 0x00;
    OCR4CH = 0x00;
    OCR4CL = 0x00;
    TCCR5A = 0x00;
    TCCR5B = 0x00;
    TCNT5H = 0x00;
    TCNT5L = 0x00;
    ICR5H = 0x00;
    ICR5L = 0x00;
    OCR5AH = 0x00;
    OCR5AL = 0x00;
    OCR5BH = 0x00;
    OCR5BL = 0x00;
    OCR5CH = 0x00;
    OCR5CL = 0x00;
    EICRA = 0x00;
    EICRB = 0x00;
    EIMSK = 0x00;
    PCMSK0 = 0x00;
    PCMSK1 = 0x00;
    PCMSK2 = 0x00;
    PCICR = 0x00;
    TIMSK0 = 0x00;
    TIMSK1 = 0x00;
    TIMSK2 = 0x00;
    TIMSK3 = 0x00;
    TIMSK4 = 0x00;
    TIMSK5 = 0x00;
    UCSR0B = 0x00;
    UCSR1B = 0x00;
    UCSR2B = 0x00;
    UCSR3B = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    
    tp_init();
    TFT_init();
    
    TFT_set_rotation(LANDSCAPE_2);
    TFT_fill(Black);
}


void test_RGB()
{
    TFT_fill(Red);
    delay_ms(600);
    TFT_fill(Green);
    delay_ms(600);
    TFT_fill(Blue);
    delay_ms(600);
    TFT_fill(Black);
}


void test_colours()
{
    Draw_Rectangle(0, 0, 319, 23, YES, SQUARE, Grey, Grey);
    Draw_Rectangle(0, 23, 319, 47, YES, SQUARE, White, White);
    Draw_Rectangle(0, 47, 319, 71, YES, SQUARE, Cyan, Cyan);
    Draw_Rectangle(0, 71, 319, 95, YES, SQUARE, Light_Blue, Light_Blue);
    Draw_Rectangle(0, 95, 319, 119, YES, SQUARE, Blue, Blue);
    Draw_Rectangle(0, 119, 319, 143, YES, SQUARE, Green, Green);
    Draw_Rectangle(0, 143, 319, 167, YES, SQUARE, Yellow, Yellow);
    Draw_Rectangle(0, 167, 319, 191, YES, SQUARE, Magenta, Magenta);
    Draw_Rectangle(0, 191, 319, 215, YES, SQUARE, Red, Red);
    Draw_Rectangle(0, 215, 319, 239, YES, SQUARE, Black, Black);
    delay_ms(2600);
    TFT_fill(Black);
}


void test_2D_graphics()
{
    signed int i = 0;

    TFT_fill(Black);
    
    for(i = 0; i <= 320; i += 10)
    {
        Draw_V_Line(i, 0, 240, White);
    }
    for(i = 0; i <= 240; i += 10)
    {
        Draw_H_Line(0, 320, i, White);
    }
    
    delay_ms(3000);
    
    TFT_fill(Black);
    for(i = 0; i < 240; i += 5)
    {
        Draw_Line(0, 0, 319, i, Light_Blue);
    }
    
    for(i = 239; i > -1; i -= 5)
    {
        Draw_Line(319, 240, 0, i, Blue);
    }
    
    delay_ms(3000);

    TFT_fill(Black);
    
    Draw_Rectangle(9, 19, 309, 199, NO, ROUND, Magenta, Black);
    Draw_Rectangle(19, 29, 299, 189, YES, SQUARE, Cyan, Black);

    delay_ms(4000);

    TFT_fill(Black);
    
    Draw_Circle(159, 119, 80, NO, Red);
    Draw_Circle(159, 119, 40, YES, Yellow);
    

    delay_ms(3000);

    TFT_fill(Black);
    
    Draw_Triangle(10, 200, 309, 200, 149, 19, NO, Green);
    delay_ms(400);
    Draw_Triangle(10, 200, 309, 200, 149, 19, YES, Grey);

    delay_ms(3000);

    TFT_fill(Black);
}


void draw_flag()
{
    Draw_Rectangle(20, 20, 299, 219, YES, SQUARE, Green, Green);
    Draw_Circle(160, 120, 60, YES, Red);
    delay_ms(6000);
    TFT_fill(Black);
}


void print_test_data()
{
    unsigned char s = 0;
    signed char c = -9;

    signed int i = -9;

    float f = -9.9;


    print_str(16, 10, 1, Red, Black, "MicroArena");
    print_str(16, 30, 2, Green, Black, "MicroArena");
    print_str(16, 60, 3, Blue, Black, "MicroArena");
    print_str(16, 90, 1, White, Black, "https://www.facebook.com/MicroArena");

    for(s = 0; s < 250; s++)
    {
        print_C(22, 150, 1, Red, Black, c);
        print_I(22, 175, 2, Green, Black, i);
        print_F(22, 210, 3, Blue, Black, f, 1);

        c++;
        i++;
        f += 0.1;

        delay_ms(45);
    }
    TFT_fill(Black);
}


void print_image()
{
    TFT_set_rotation(LANDSCAPE_1);
    Draw_BMP(70, 57, 250, 182, image);
    delay_ms(6000);
    TFT_fill(Black);
    TFT_set_rotation(LANDSCAPE_2);
}