#include "DS3234.c"


sbit LCD_RS at PORTC0_bit;
sbit LCD_EN at PORTC1_bit;
sbit LCD_D4 at PORTC2_bit;
sbit LCD_D5 at PORTC3_bit;
sbit LCD_D6 at PORTC4_bit;
sbit LCD_D7 at PORTC5_bit;

sbit LCD_RS_Direction at DDC0_bit;
sbit LCD_EN_Direction at DDC1_bit;
sbit LCD_D4_Direction at DDC2_bit;
sbit LCD_D5_Direction at DDC3_bit;
sbit LCD_D6_Direction at DDC4_bit;
sbit LCD_D7_Direction at DDC5_bit;


#define SET           1
#define INC           2
#define SAVE          3

#define keypad_dly    10
#define disp_dly      90


const unsigned char symbol[] = {0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00};


void setup();
void custom_symbol(unsigned char pos_row, unsigned char pos_char);
unsigned char get_keypad();
void display_value(unsigned char y_pos, unsigned char x_pos, unsigned char convert);
void show_temperature();
void display_time();
void get_date_time_data();
unsigned char change_value(unsigned char y, unsigned char x, unsigned char value, unsigned char max_value, unsigned char min_value);
void setting();
void show_day(unsigned char value);


void main()
{
    setup();
    
    while(1)
    {
        setting();
        get_date_time_data();
        show_temperature();
        display_time();
        delay_ms(200);
    };
}


void setup()
{
    PORTB = 0x00;
    DDRB = 0x04;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0xE0;
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
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    DS3234_init();
    Lcd_Init();
    Sound_Init(&PORTD, 7);
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    delay_ms(100);
}


void custom_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char n = 0;
    
    Lcd_Cmd(64);
    for (n = 0; n < 8; n += 1) 
    {
        Lcd_Chr_CP(symbol[n]);
    }
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}


unsigned char get_keypad()
{
    if(PIND0_bit)
    {
           Sound_Play(2900, keypad_dly);
           return SET;
    }
    else if(PIND1_bit)
    {
           Sound_Play(2200, keypad_dly);
           return INC;
    }
    else if(PIND2_bit)
    {
           Sound_Play(1800, keypad_dly);
           return SAVE;
    }
    else
    {
           return 0;
    }
}


void display_value(unsigned char y_pos, unsigned char x_pos, unsigned char convert)
{
    unsigned char ch = 0;
    
    ch = (convert / 10);
    Lcd_Chr(y_pos, x_pos, (ch + 48));
    ch = (convert % 10);
    Lcd_Chr(y_pos, (++x_pos), (ch + 48));
}


void show_temperature()
{
    float t = 0;
    unsigned char temp = 0;
    
    t = get_temp();
    temp = t;
    display_value(2, 10, temp);
    lcd_out(2, 12, ".");
    temp = ((t - temp) * 100);
    display_value(2, 13, temp);
    custom_symbol(2, 15);
    lcd_out(2, 16, "C");
}

void display_time()
{
    display_value(1, 1, hr);
    lcd_out(1, 3, ":");
    display_value(1, 4, min);
    lcd_out(1, 6, ":");
    display_value(1, 7, s);
    
    switch(hr_format)
    {
        case hr12:
        {
            switch(ampm)
            {
                case pm:
                {
                    lcd_out(1, 10, "PM");
                    break;
                }
                default:
                {
                    lcd_out(1, 10, "AM");
                    break;
                }
            }
            break;
        }
        default:
        {
            lcd_out(1, 10, "  ");
            break;
        }
    }

    display_value(2, 1, dt);
    lcd_out(2, 3, "/");
    display_value(2, 4, mt);
    lcd_out(2, 6, "/");
    display_value(2, 7, yr);
    show_day(dy);
}


void get_date_time_data()
{
    get_date();
    get_time(hr_format);
}


unsigned char change_value(unsigned char y, unsigned char x, unsigned char value, unsigned char max_value, unsigned char min_value)
{
    while(1)
    {
          if(get_keypad() == INC)
          {
              value += 1;
          }
          if(value > max_value)
          {
              value = min_value;
          }

          lcd_out(y, x, "  ");
          delay_ms(disp_dly);
          display_value(y, x, value);
          delay_ms(disp_dly);
          
          if(get_keypad() == SAVE)
          {
                    while(get_keypad() == SAVE);
                    return value;
          }
    }
}


void setting()
{
     bit set_cmd;
     unsigned char tmp = 0;

     set_cmd = 0;
     if(get_keypad() == SET)
     {
         while(get_keypad() == SET);
         set_cmd = 1;
     }
     
     while(set_cmd)
     {
         while(1)
         {
             if(get_keypad() == INC)
             {
                 tmp += 1;
             }
             if(tmp > 2)
             {
                 tmp = 0;
             }
             
             lcd_out(1, 10, "  ");
             delay_ms(disp_dly);
             switch(tmp)
             {
                 case 1:
                 {
                     lcd_out(1, 10, "AM");
                     ampm = am;
                     hr_format = hr12;
                     break;
                 }
                 case 2:
                 {
                     lcd_out(1, 10, "PM");
                     ampm = pm;
                     hr_format = hr12;
                     break;
                 }
                 default:
                 {
                     lcd_out(1, 10, "24");
                     hr_format = hr24;
                     break;
                 }
             }
             delay_ms(disp_dly);
             
             if(get_keypad() == SAVE)
             {
                 break;
             }
         }
         s = change_value(1, 7, s, 59, 0);
         min = change_value(1, 4, min, 59, 0);
         
         switch(hr_format)
         {
             case hr12:
             {
                 hr = change_value(1, 1, hr, 12, 1);
                 break;
             }
             default:
             {
                 hr = change_value(1, 1, hr, 23, 0);
                 break;
             }
         }

         dt = change_value(2, 1, dt, 31, 1);
         mt = change_value(2, 4, mt, 12, 1);
         yr = change_value(2, 7, yr, 99, 0);

         tmp = dy;
         while(1)
         {
             if(get_keypad() == INC)
             {
                 tmp += 1;
             }
             if(tmp > 7)
             {
                 tmp = 1;
             }

             lcd_out(1, 14, "   ");
             delay_ms(disp_dly);
             show_day(tmp);
             delay_ms(disp_dly);

             if(get_keypad() == SAVE)
             {
                 dy = tmp;
                 break;
             }
         }
         
         set_time(hr, min, s, ampm, hr_format);
         set_date(dy, dt, mt, yr);
         set_cmd = 0;
     }
}


void show_day(unsigned char value)
{
     switch(value)
     {
        case 1:
        {
             lcd_out(1, 14, "SUN");
             break;
        }
        case 2:
        {
             lcd_out(1, 14, "MON");
             break;
        }
        case 3:
        {
             lcd_out(1, 14, "TUE");
             break;
        }
        case 4:
        {
             lcd_out(1, 14, "WED");
             break;
        }
        case 5:
        {
             lcd_out(1, 14, "THR");
             break;
        }
        case 6:
        {
             lcd_out(1, 14, "FRI");
             break;
        }
        case 7:
        {
             lcd_out(1, 14, "SAT");
             break;
        }
     }
}