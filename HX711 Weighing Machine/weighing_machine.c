#include "HX711.c"
#include "lcd_print.c"



sbit LCD_RS at PORTD6_bit;
sbit LCD_EN at PORTD4_bit;
sbit LCD_D4 at PORTB4_bit;
sbit LCD_D5 at PORTB5_bit;
sbit LCD_D6 at PORTB6_bit;
sbit LCD_D7 at PORTB7_bit;

sbit LCD_RS_Direction at DDD6_bit;
sbit LCD_EN_Direction at DDD4_bit;
sbit LCD_D4_Direction at DDB4_bit;
sbit LCD_D5_Direction at DDB5_bit;
sbit LCD_D6_Direction at DDB6_bit;
sbit LCD_D7_Direction at DDB7_bit;


void setup(void);


void main(void)
{
    float w = 0;

    setup();
    
    Lcd_Out(1, 4, "HX711 Demo");
    Lcd_Out(2, 3, "Zero Setting");
    delay_ms(1000);
    Lcd_Out(2, 1, "Mass/g:        ");

    while(1)
    {
        w = HX711_get_mass();
        print_F(9, 2, w, 1);

        delay_ms(200);
    };
}


void setup(void)
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0xF0;
    PORTC = 0x80;
    DDRC = 0x40;
    PORTD = 0x00;
    DDRD = 0x70;
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

    HX711_init();

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    delay_ms(100);
}