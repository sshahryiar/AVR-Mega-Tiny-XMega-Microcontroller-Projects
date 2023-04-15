#include "lcd_keypad_shield.h"
#include "LIDAR.c"


void setup();
void lcd_print_c(unsigned char x_pos, unsigned char y_pos, signed int value);
void lcd_print_i(unsigned char x_pos, unsigned char y_pos, signed long value);
void lcd_print_f(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points);
void lcd_print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points);


void main() 
{
     unsigned int distance = 0;
     
     setup();
     
     while(1)
     {
          distance = LIDAR_get_distance();
          lcd_print_i(11, 2, distance);
          delay_ms(300);
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x30;
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
    
    TWI_Init(100000);

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    
    delay_ms(2000);
    
    Lcd_Out(1, 4, "LIDAR Demo");
    Lcd_Out(2, 1, "Range/cm:");
}


void lcd_print_c(unsigned char x_pos, unsigned char y_pos, signed int value)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        value = -value;
        lcd_out(y_pos, x_pos, "-");
    }
    else
    {
        lcd_out(y_pos, x_pos, " ");
    }

    if((value > 99) && (value <= 999))
    {
        ch = ((value / 100) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        ch = (((value / 10) % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 2), ch);
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 3), ch);
    }
    else if((value > 9) && (value <= 99))
    {
        ch = ((value / 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 2), ch);
        lcd_chr(y_pos, (x_pos + 3), 0x20);
    }
    else if((value >= 0) && (value <= 9))
    {
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        lcd_chr(y_pos, (x_pos + 2), 0x20);
        lcd_chr(y_pos, (x_pos + 3), 0x20);
    }
}


void lcd_print_i(unsigned char x_pos, unsigned char y_pos, signed long value)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        value = -value;
        lcd_out(y_pos, x_pos, "-");
    }
    else
    {
        lcd_out(y_pos, x_pos, " ");
    }

    if((value > 9999) && (value <= 99999))
    {
        ch = ((value / 10000) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        ch = (((value / 1000) % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 2), ch);
        ch = (((value / 100) % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 3), ch);
        ch = (((value / 10) % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 4), ch);
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 5), ch);
    }
    else if((value > 999) && (value <= 9999))
    {
        ch = ((value / 1000) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        ch = (((value / 100) % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 2), ch);
        ch = (((value / 10) % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 3), ch);
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 4), ch);
        lcd_chr(y_pos, (x_pos + 5), 0x20);
    }
    else if((value > 99) && (value <= 999))
    {
        ch = ((value / 100) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        ch = (((value / 10) % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 2), ch);
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 3), ch);
        lcd_chr(y_pos, (x_pos + 4), 0x20);
        lcd_chr(y_pos, (x_pos + 5), 0x20);
    }
    else if((value > 9) && (value <= 99))
    {
        ch = ((value / 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 2), ch);
        lcd_chr(y_pos, (x_pos + 3), 0x20);
        lcd_chr(y_pos, (x_pos + 4), 0x20);
        lcd_chr(y_pos, (x_pos + 5), 0x20);
    }
    else if((value > 0) && (value <= 9))
    {
        ch = ((value % 10) + 0x30);
        lcd_chr(y_pos, (x_pos + 1), ch);
        lcd_chr(y_pos, (x_pos + 2), 0x20);
        lcd_chr(y_pos, (x_pos + 3), 0x20);
        lcd_chr(y_pos, (x_pos + 4), 0x20);
        lcd_chr(y_pos, (x_pos + 5), 0x20);
    }
}


void lcd_print_f(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points)
{
    signed long tmp = 0;

    tmp = ((signed long)value);
    lcd_print_i(x_pos, y_pos, tmp);
    tmp = (10000 * (value - tmp));

    if(tmp < 0)
    {
       tmp = -tmp;
    }

    if((value >= 10000) && (value < 100000))
    {
        lcd_print_decimal((x_pos + 6), y_pos, tmp, points);
    }
    else if((value >= 1000) && (value < 10000))
    {
        lcd_print_decimal((x_pos + 5), y_pos, tmp, points);
    }
    else if((value >= 100) && (value < 1000))
    {
        lcd_print_decimal((x_pos + 4), y_pos, tmp, points);
    }
    else if((value >= 10) && (value < 100))
    {
        lcd_print_decimal((x_pos + 3), y_pos, tmp, points);
    }
    else if(value < 10)
    {
        lcd_print_decimal((x_pos + 2), y_pos, tmp, points);

        if(value < 0)
        {
            lcd_out(y_pos, x_pos, "-");
            lcd_chr(y_pos, (x_pos + 1), 0x30);
        }
        else
        {
            lcd_out(y_pos, x_pos, " ");
            if(value < 1)
            {
               lcd_chr(y_pos, (x_pos + 1), 0x30);
            }
        }
    }
}


void lcd_print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points)
{
    unsigned char ch = 0x00;

    lcd_chr(y_pos, x_pos, 0x2E);

    ch = ((value / 1000) + 0x30);
    lcd_chr(y_pos, (x_pos + 1), ch);

    if(points > 1)
    {
        ch = (((value % 1000) / 100) + 0x30);
        lcd_chr(y_pos, (x_pos + 2), ch);

        if(points > 2)
        {
            ch = (((value % 100) / 10) + 0x30);
            lcd_chr(y_pos, (x_pos + 3), ch);

            if(points > 3)
            {
                ch = ((value % 10) + 0x30);
                lcd_chr(y_pos, (x_pos + 4), ch);
            }
        }
    }
}