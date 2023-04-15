#include "L3G4200.c"
#include "lcd_keypad_shield.h"


const unsigned char deg_symbol[8] = {0x00, 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00};


void setup();
void custom_char(unsigned char x_pos, unsigned char y_pos);
void show_float_value(unsigned char x_pos, unsigned char y_pos, signed int value);
void show_int_value(unsigned char x_pos, unsigned char y_pos, signed int value);


void main() 
{
     bit i;

     signed char t = 0;

     signed int x_value = 0x0000;
     signed int y_value = 0x0000;
     signed int z_value = 0x0000;
     
     setup();
     
     lcd_out(1, 5, " X Y Z");
     
     i = 0;
     
     while(1)
     {
         if(PINC0_bit == 0)
         {
             while(PINC0_bit == 0);
             i ^= 1;
         }

         L3G4200_get_raw_data(&x_value, &y_value, &z_value);
         
         if(i == 0)
         {
             lcd_out(1, 1, "RAW");
         }
         else
         {
             lcd_out(1, 2, "/s");
             custom_char(1, 1);
             L3G4200_degrees_per_second(&x_value, &y_value, &z_value, FS250);
         }

         show_int_value(1, 2, x_value);
         show_int_value(7, 2, y_value);
         show_int_value(12, 2, z_value);

         t = L3G4200_get_temperature();
         show_int_value(12, 1, t);
         custom_char(15, 1);
         lcd_out(1, 16, "C");
         delay_ms(999);
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
    ADCSRA = 0x00;
    SFIOR = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    
    L3G4200_init();
}


void custom_char(unsigned char x_pos, unsigned char y_pos)
{
    unsigned char i = 0;
    Lcd_Cmd(64);
    for(i = 0; i < 8; i++)
    {
          Lcd_Chr_CP(deg_symbol[i]);
    }
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(y_pos, x_pos, 0);
}


void show_float_value(unsigned char x_pos, unsigned char y_pos, signed int value)
{
     unsigned char ch = 0x00;

     if(value < 0)
     {
          lcd_out(y_pos, x_pos, "-");
          value = -value;
     }
     else
     {
          lcd_out(y_pos, x_pos, " ");
     }

     if((value > 999) && (value <= 9999))
     {
          ch = ((value / 1000) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 100) % 10) + 0x30);
          lcd_chr_cp(ch);
          lcd_chr_cp(0x2E);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
     }
     else if((value > 99) && (value <= 999))
     {
          ch = (((value / 100) % 10) + 0x30);
          lcd_chr_cp(ch);
          lcd_chr_cp(0x2E);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);;
          lcd_chr_cp(ch);
     }
     else if((value > 9) && (value <= 99))
     {
          lcd_chr_cp(0x30);
          lcd_chr_cp(0x2E);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);;
          lcd_chr_cp(ch);
     }
     else if((value >= 0) && (value <= 9))
     {
          lcd_chr_cp(0x30);
          lcd_chr_cp(0x2E);
          lcd_chr_cp(0x30);
          ch = ((value % 10) + 0x30);;
          lcd_chr_cp(ch);
     }
}


void show_int_value(unsigned char x_pos, unsigned char y_pos, signed int value)
{
     unsigned char ch = 0x00;

     if(value < 0)
     {
          lcd_out(y_pos, x_pos, "-");
          value = -value;
     }
     else
     {
          lcd_out(y_pos, x_pos, " ");
     }

     if((value > 999) && (value <= 9999))
     {
          ch = ((value / 1000) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 100) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);;
          lcd_chr_cp(ch);
     }
     else if((value > 99) && (value <= 999))
     {
          ch = (((value / 100) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);;
          lcd_chr_cp(ch);
          lcd_chr_cp(0x20);
     }
     else if((value > 9) && (value <= 99))
     {
          ch = (((value / 10) % 10) + 0x30);
          lcd_chr_cp(ch);
          ch = ((value % 10) + 0x30);;
          lcd_chr_cp(ch);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
     }
     else if((value >= 0) && (value <= 9))
     {
          ch = ((value % 10) + 0x30);;
          lcd_chr_cp(ch);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
          lcd_chr_cp(0x20);
     }
}