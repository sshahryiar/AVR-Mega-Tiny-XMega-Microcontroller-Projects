#include "I2C.h"
#include "DS1307.c"
#include "AT24C32.c"
#include "DS18B20.c"


#define INC                !PINA0_bit
#define DEC                !PINA1_bit
#define MENU_INC           !PINA2_bit
#define MENU_DEC           !PINA3_bit
#define SET                !PINA4_bit
#define LOG_START          !PINA5_bit
#define LOG_STOP           !PINA6_bit
#define VIEW               !PINA7_bit

#define max_interval       90
#define min_interval       1


sbit LCD_RS at PORTB0_bit;
sbit LCD_EN at PORTB2_bit;
sbit LCD_D4 at PORTB3_bit;
sbit LCD_D5 at PORTB4_bit;
sbit LCD_D6 at PORTB5_bit;
sbit LCD_D7 at PORTB6_bit;

sbit LCD_RS_Direction at DDB0_bit;
sbit LCD_EN_Direction at DDB2_bit;
sbit LCD_D4_Direction at DDB3_bit;
sbit LCD_D5_Direction at DDB4_bit;
sbit LCD_D6_Direction at DDB5_bit;
sbit LCD_D7_Direction at DDB6_bit;


const unsigned char symbol[0x08] = {0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x06, 0x00};


bit page;
bit log_flag;
bit log_data_flag;

unsigned char cnt = 0;
unsigned char menu = 0;
unsigned char s_previous = 0;
unsigned char s_present = 0;
unsigned char log_interval = 60;

signed char log_time = 0;

unsigned int memloc = 0;

signed int loc = 0;
signed int t = 0;


void setup();
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void get_logging_interval();
void main_page();
void settings();
void show_parameters();
void show_day(unsigned char day);
void show_2_digit_value(unsigned char x_pos, unsigned char y_pos, unsigned char value);
void show_int_value(unsigned char x_pos, unsigned char y_pos, signed int value);
void show_temperature(unsigned char x_pos, unsigned char y_pos, signed int value);
unsigned char inc_dec(unsigned char x_pos, unsigned char y_pos, signed char value, unsigned char value_max, unsigned char value_min);
unsigned char day_inc_dec(unsigned char value);
void take_data_logs();
void read_logs();


void main() 
{
    setup();
    
    while(1)
    {
        show_parameters();
        take_data_logs();
        settings();
        read_logs();
    };
}


void setup()
{
    page = 0;
    log_flag = 0;
    log_data_flag = 0;
    
    get_logging_interval();
    
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0xFF;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x02;
    PORTE = 0x00;
    DDRE = 0x00;
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
    GICR = 0x20;
    MCUCR = 0x00;
    EMCUCR = 0x00;
    GIFR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SPCR = 0x00;
    asm sei;
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    
    delay_ms(100);
}


void load_symbol(unsigned char pos_row, unsigned char pos_char) 
{
    signed char i = 0x07;
    
    Lcd_Cmd(0x40);
    while(i > -1)
    {
        Lcd_Chr_CP(symbol[i]);
        i--;
    }
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0x00);
}


void get_logging_interval()
{
    log_interval = EEPROM_Read(0x09);
    delay_ms(20);
    if(log_interval > max_interval)
    {
      log_interval = max_interval;
      EEPROM_Write(0x09, log_interval);
      delay_ms(20);
    }
    log_time = log_interval;
    
    s_previous = 0;
    s_present = 0;
}


void main_page()
{
    if(page)
    {
       lcd_out(1, 1, "Mem. Location: ");
    }
    else
    {
        lcd_out(1, 3, "Temp. Datalogger");
    }
    lcd_out(2, 1, "T/ C:");
    load_symbol(2, 3);
    lcd_out(3, 1, "Time:");
    lcd_out(3, 10, ":");
    lcd_out(3, 13, ":");
    lcd_out(4, 1, "Date:");
    lcd_out(4, 10, "/");
    lcd_out(4, 13, "/");
}


void settings()
{
     if(SET)
     {
         while(SET);
         get_logging_interval();
         page = 0;
         menu = 1;
     }
     if(menu != 0)
     {
         switch(menu)
         {
             case 1:
             {
                 time.h = inc_dec(8, 3, time.h, 23, 0);
                 break;
             }
             case 2:
             {
                 time.m = inc_dec(11, 3, time.m, 59, 0);
                 break;
             }
             case 3:
             {
                 time.s = inc_dec(14, 3, time.s, 59, 0);
                 break;
             }
             case 4:
             {
                 time.dt = inc_dec(8, 4, time.dt, 31, 1);
                 break;
             }
             case 5:
             {
                 time.mt = inc_dec(11, 4, time.mt, 12, 1);
                 break;
             }
             case 6:
             {
                 time.yr = inc_dec(14, 4, time.yr, 31, 1);
                 break;
             }
             case 7:
             {
                 time.dy = day_inc_dec(time.dy);
                 break;
             }
             case 8:
             {
                 log_interval = inc_dec(18, 3, log_interval, max_interval, min_interval);
                 break;
             }
             case 9:
             {
                 set_time();
                 cnt = 0;
                 memloc = 0;
                 s_present = 0;
                 s_previous = 0;
                 EEPROM_Write(0x09, log_interval);
                 delay_ms(20);
                 log_time = log_interval;
                 menu = 0;
             }
             default:
             {
                 break;
             }
         }
     }
}


void show_parameters()
{
     main_page();
     
     if((menu == 0) && (page == 0))
     {
         t = get_temp();
         get_time();
         
         show_temperature(9, 2, t);

         show_2_digit_value(8, 3, time.h);
         show_2_digit_value(11, 3, time.m);
         show_2_digit_value(14, 3, time.s);
         
         show_2_digit_value(8, 4, time.dt);
         show_2_digit_value(11, 4, time.mt);
         show_2_digit_value(14, 4, time.yr);
         
         show_day(time.dy);
         
         if(log_data_flag)
         {
             lcd_out(2, 18, "LOG");
             lcd_out(3, 20, "s");
             show_2_digit_value(18, 3, log_time);
             s_present = time.s;
             if(s_present != s_previous)
             {
                 log_time--;
                 if(log_time < 0)
                 {
                    log_flag = 1;
                    log_time = log_interval;
                 }
             }
             s_previous = s_present;
         }
         else
         {
             lcd_out(2, 18, "   ");
             lcd_out(3, 18, "   ");
         }
     }
}


void show_day(unsigned char day)
{
     switch(day)
     {
         case 1:
         {
             lcd_out(4, 18, "SUN");
             break;
         }
         case 2:
         {
             lcd_out(4, 18, "MON");
             break;
         }
         case 3:
         {
             lcd_out(4, 18, "TUE");
             break;
         }
         case 4:
         {
             lcd_out(4, 18, "WED");
             break;
         }
         case 5:
         {
             lcd_out(4, 18, "THR");
             break;
         }
         case 6:
         {
             lcd_out(4, 18, "FRI");
             break;
         }
         case 7:
         {
             lcd_out(4, 18, "SAT");
             break;
         }
     }
}


void show_2_digit_value(unsigned char x_pos, unsigned char y_pos, unsigned char value)
{
     unsigned char ch = 0x00;
     
     ch = ((value / 10) + 0x30);
     lcd_chr(y_pos, x_pos, ch);
     ch = ((value % 10) + 0x30);
     lcd_chr(y_pos, (x_pos + 1), ch);
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
     
     if((value > 99) && (value <= 999))
     {
         ch = ((value / 0x64) + 0x30);
         lcd_chr_cp(ch);
         ch = (((value / 0x0A) % 0x0A) + 0x30);
         lcd_chr_cp(ch);
         ch = ((value % 0x0A) + 0x30);
         lcd_chr_cp(ch);
     }
     else if((value > 9) && (value <= 99))
     {
         ch = (((value / 0x0A) % 0x0A) + 0x30);
         lcd_chr_cp(ch);
         ch = ((value % 0x0A) + 0x30);
         lcd_chr_cp(ch);
         lcd_chr_cp(0x20);
     }
     else if((value >= 0) && (value <= 9))
     {
         ch = ((value % 0x0A) + 0x30);
         lcd_chr_cp(ch);
         lcd_chr_cp(0x20);
         lcd_chr_cp(0x20);
     }
}


void show_temperature(unsigned char x_pos, unsigned char y_pos, signed int value)
{
     unsigned char pos = 0;
     
     show_int_value(x_pos, y_pos, (value / 0x0A));
     
     if(value < 0)
     {
         value = -value;
     }
     
     if(value > 999)
     {
         pos = 4;
     }
     else if((value > 99) && (value <= 999))
     {
         pos = 3;
     }
     else
     {
        pos = 2;
     }
     
     lcd_chr(y_pos, (x_pos + pos), 46);

     lcd_chr_cp(((value % 0x0A) + 0x30));
     lcd_chr_cp(0x20);
     lcd_chr_cp(0x20);
}


unsigned char inc_dec(unsigned char x_pos, unsigned char y_pos, signed char value, unsigned char value_max, unsigned char value_min)
{
    if(INC)
    {
        value++;
    }
    
    if(value > value_max)
    {
        value = value_min;
    }
    
    if(DEC)
    {
        value--;
    }

    if(value < value_min)
    {
        value = value_max;
    }
    
    if(MENU_INC)
    {
        menu++;
    }
    
    if(MENU_DEC)
    {
        menu--;
    }

    if((menu > 9) || (menu < 1))
    {
        menu = 0;
    }
    
    lcd_out(y_pos, x_pos, "  ");
    delay_ms(120);
    show_2_digit_value(x_pos, y_pos, value);
    delay_ms(120);
    
    return value;
}


unsigned char day_inc_dec(unsigned char value)
{
    if(INC)
    {
        value++;
    }

    if(value > 7)
    {
        value = 1;
    }

    if(DEC)
    {
        value--;
    }

    if(value < 1)
    {
        value = 7;
    }

    if(MENU_INC)
    {
        menu++;
    }

    if(MENU_DEC)
    {
        menu--;
    }

    if((menu > 9) || (menu < 1))
    {
        menu = 0;
    }

    lcd_out(4, 18, "   ");
    delay_ms(120);
    show_day(value);
    delay_ms(120);

    return value;
}


void take_data_logs()
{
     if(log_flag)
     {
         buffer[cnt] = time.h;
         buffer[cnt + 1] = time.m;
         buffer[cnt + 2] = time.s;
         buffer[cnt + 3] = time.dt;
         buffer[cnt + 4] = time.mt;
         buffer[cnt + 5] = time.yr;
         buffer[cnt + 6] = get_high_byte(t);
         buffer[cnt + 7] = get_low_byte(t);
         cnt += 8;
         DDA0_bit = 1;
         PORTA0_bit = 0;
         delay_ms(20);
         DDA0_bit = 0;
         log_flag = 0;
     }
     
     if(cnt >= 32)
     {
         AT24C32_page_write(memloc);
         cnt = 0;
         DDA0_bit = 1;
         PORTA0_bit = 0;
         delay_ms(40);
         DDA0_bit = 0;
         memloc += bytes_per_page;
     }
     
     if((log_data_flag) && (memloc >= 4096) || (LOG_STOP))
     {
         memloc = 0;
         log_data_flag = 0;
     }
     
     if(LOG_START)
     {
         while(LOG_START);
         memloc = 0;
         cnt = 0;
         log_data_flag = 1;
     }
}


void read_logs()
{
     signed char mem = 0x00;
     signed int temp = 0x0000;

     if(VIEW && (menu == 0))
     {
        while(VIEW);
        Lcd_Cmd(_LCD_CLEAR);
        page = ~page;
     }
     
     if(page)
     {
         for(mem = 0; mem < 8; mem++)
         {
             buffer[mem] = AT24C32_read((loc + mem));
         }

         if(INC)
         {
            loc += 8;
            delay_ms(60);
         }
         if(loc > 4088)
         {
             loc = 0;
         }
         if(DEC)
         {
            loc -= 8;
            delay_ms(60);
         }
         if(loc < 0)
         {
             loc = 4088;
         }
         show_int_value(16, 1, (loc >> 3));
         
         temp = buffer[6];
         temp <<= 8;
         temp |= buffer[7];
         
         show_temperature(9, 2, temp);

         show_2_digit_value(8, 3, buffer[0]);
         show_2_digit_value(11, 3, buffer[1]);
         show_2_digit_value(14, 3, buffer[2]);

         show_2_digit_value(8, 4, buffer[3]);
         show_2_digit_value(11, 4, buffer[4]);
         show_2_digit_value(14, 4, buffer[5]);
     }
}