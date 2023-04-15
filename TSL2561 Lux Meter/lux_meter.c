#include "TSL256x.c"


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


void setup();
void show_long_value(unsigned char x_pos, unsigned char y_pos, signed long value);


void main()
{
     unsigned int raw_ir = 0;
     unsigned int raw_vis = 0;

     signed long l = 0;

     setup();

     lcd_out(1, 1, "Vi:");
     lcd_out(1, 11, "Lux:");
     lcd_out(2, 1, "IR:");

     while(1)
     {
         l = calculate_lux(0, 1000);

         TSL256x_write(control_reg, 0x03);
         get_raw_data(&raw_vis, &raw_ir);
         TSL256x_write(control_reg, 0x00);

         show_long_value(4, 1, raw_vis);
         show_long_value(4, 2, raw_ir);
         show_long_value(11, 2, l);
         delay_ms(200);
     };
}


void setup()
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

    TSL256x_init();
    delay_ms(400);
}


void show_long_value(unsigned char x_pos, unsigned char y_pos, signed long value)
{
     unsigned char ch = 0;

     if(value < 0)
     {
          lcd_out(y_pos, x_pos, "-");
          value = -value;
     }
     else
     {
          lcd_out(y_pos, x_pos, " ");
     }

     if((value > 9999) && (value <= 99999))
     {
          ch = ((value / 10000) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 1000) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 100) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);
          lcd_chr_cp(ch);
     }
     else if((value > 999) && (value <= 9999))
     {
          ch = (((value / 1000) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 100) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);
          lcd_chr_cp(ch);
          lcd_chr_cp(0x20);
     }
     else if((value > 99) && (value <= 999))
     {
          ch = (((value / 100) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);
          lcd_chr_cp(ch);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
     }
     else if((value > 9) && (value <= 99))
     {
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);
          lcd_chr_cp(ch);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
     }
     else if((value >= 0) && (value <= 9))
     {
          ch = ((value % 10) + 0x30);
          lcd_chr_cp(ch);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
     }
}