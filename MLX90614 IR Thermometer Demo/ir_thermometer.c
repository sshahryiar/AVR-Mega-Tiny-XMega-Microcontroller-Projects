#include "MLX90614.c"


#define button                               !PIND5_bit

#define samples                              50


sbit LCD_RS at PORTC6_bit;
sbit LCD_EN at PORTC7_bit;
sbit LCD_D4 at PORTA4_bit;
sbit LCD_D5 at PORTA5_bit;
sbit LCD_D6 at PORTA6_bit;
sbit LCD_D7 at PORTA7_bit;

sbit LCD_RS_Direction at DDC6_bit;
sbit LCD_EN_Direction at DDC7_bit;
sbit LCD_D4_Direction at DDA4_bit;
sbit LCD_D5_Direction at DDA5_bit;
sbit LCD_D6_Direction at DDA6_bit;
sbit LCD_D7_Direction at DDA7_bit;


const unsigned char symbol[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00};


void setup();
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void lcd_print_c(unsigned char x_pos, unsigned char y_pos, signed int value);
void lcd_print_i(unsigned char x_pos, unsigned char y_pos, signed long value);
void lcd_print_f(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points);
void lcd_print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points);


void main() 
{
     unsigned char temp_unit = 0;
     unsigned char avg = samples;
     
     float To = 0.0;
     float Ta = 0.0;
     
     setup();
     
     lcd_out(1, 1, "T.obj/  :");
     lcd_out(2, 1, "T.amb/  :");

     while(1)
     {
         if(button)
         {
             while(button);
             temp_unit++;
             
             lcd_out(1, 10, "       ");
             lcd_out(2, 10, "       ");
             
             if(temp_unit > unit_Fahrenheit)
             {
                 temp_unit = unit_Kelvin;
             }
         }
         
         avg = samples;
         while(avg > 0)
         {
             To += MLX90614_read(MLX90614_I2C_ADDR, MLX90614_TOBJ1);
             Ta += MLX90614_read(MLX90614_I2C_ADDR, MLX90614_TA);
             avg--;
         }
         
         To /= samples;
         Ta /= samples;

         switch(temp_unit)
         {
             case unit_Celcius:
             {
                 load_symbol(1, 7);
                 load_symbol(2, 7);
                 lcd_out(1, 8, "C");
                 lcd_out(2, 8, "C");
                 To = MLX90614_get_temperature(To, unit_Celcius);
                 Ta = MLX90614_get_temperature(Ta, unit_Celcius);
                 break;
             }
             case unit_Fahrenheit:
             {
                 load_symbol(1, 7);
                 load_symbol(2, 7);
                 lcd_out(1, 8, "F");
                 lcd_out(2, 8, "F");
                 To = MLX90614_get_temperature(To, unit_Fahrenheit);
                 Ta = MLX90614_get_temperature(Ta, unit_Fahrenheit);
                 break;
             }
             default:
             {
                 lcd_out(1, 7, " K");
                 lcd_out(2, 7, " K");
                 To = MLX90614_get_temperature(To, unit_Kelvin);
                 Ta = MLX90614_get_temperature(Ta, unit_Kelvin);
                 break;
             }
         }
         
         lcd_print_f(10, 1, To, 2);
         lcd_print_f(10, 2, Ta, 2);
         
         delay_ms(400);
     };
}


void setup()
{
    PORTA = 0x00;
    DDRA = 0xF0;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0xE0;
    PORTD = 0x00;
    DDRD = 0x00;
    PORTE = 0x00;
    DDRE = 0x00;
    TCCR0=0x00;
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
    MCUCR = 0x00;
    EMCUCR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SPCR = 0x00;
    
    MLX90614_init();
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Delay_ms(400);
}


void load_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char i = 0x00;

    Lcd_Cmd(64);

    for (i = 0; i < 8; i++)
    {
        Lcd_Chr_CP(symbol[i]);
    }

    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
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
            lcd_chr(y_pos, (x_pos + 1), 0x30);
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