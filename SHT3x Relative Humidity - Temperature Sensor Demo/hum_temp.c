#include "SHT3x.c"
#include "lcd_print.c"


sbit LCD_RS at PORTB0_bit;
sbit LCD_EN at PORTB1_bit;
sbit LCD_D4 at PORTD4_bit;
sbit LCD_D5 at PORTD5_bit;
sbit LCD_D6 at PORTD6_bit;
sbit LCD_D7 at PORTD7_bit;

sbit LCD_RS_Direction at DDB0_bit;
sbit LCD_EN_Direction at DDB1_bit;
sbit LCD_D4_Direction at DDD4_bit;
sbit LCD_D5_Direction at DDD5_bit;
sbit LCD_D6_Direction at DDD6_bit;
sbit LCD_D7_Direction at DDD7_bit;


void setup(void);


void main(void)
{
     unsigned char state = 0x00;
     float SHT3x_t = 0.0;
     float SHT3x_rh = 0.0;
     
     setup();

     Lcd_Out(1, 1, "Temp/ C:");
     Lcd_Out(2, 1, "R.H./ %:");
     print_symbol(6, 1);

     while(1)
     {
         state = SHT3x_read_temp_humidity(&SHT3x_t, &SHT3x_rh);

         switch(state)
         {
             case SHT3x_NO_ERROR:
             {
                 print_F(12, 1, SHT3x_t, 1);
                 print_F(12, 2, SHT3x_rh, 1);
                 break;
             }
             
             default:
             {
                 lcd_out(13, 1, "--.--");
                 lcd_out(13, 2, "--.--");
                 break;
             }
         }
         
         delay_ms(1000);
     };
}


void setup(void)
{
    PORTB = 0x00;
    DDRB = 0x03;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0xF0;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
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
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x83;
    ADMUX = 0x40;
    SPCR = 0x00;
    TWCR = 0x00;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    SHT3x_init();
}