#include "SHT1x.c"
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
    float T = 0.0;
    float RH = 0.0;
    float DP = 0.0;

    setup();
    
    Lcd_Out(1, 1, "SHT1x RH-Temp Sensor");
    Lcd_Out(2, 2, "Temp./ C:");
    Lcd_Out(3, 2, "R.Hum/ %:");
    Lcd_Out(4, 2, "Dew P/ C:");
    print_symbol(8, 2);
    print_symbol(8, 4);

    while(1)
    {
        Read_SHT1x(&T, &RH);
        DP = SHT1x_get_dew_point(T, RH);
        
        print_F(15, 2, T, 1);
        print_F(15, 3, RH, 1);
        print_F(15, 4, DP, 1);
        
        delay_ms(400);
    };
}


void setup(void)
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x0F;
    DDRB = 0xF0;
    PORTC = 0x00;
    DDRC = 0x0F;
    PORTD = 0x00;
    DDRD = 0x76;
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
    UCSRA = 0x00;
    UCSRB = 0x18;
    UCSRC = 0x86;
    UBRRH = 0x00;
    UBRRL = 0x0C;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    SHT1x_init();
    delay_ms(100);
}