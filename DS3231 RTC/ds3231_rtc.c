#include "DS3231.c"


sbit LCD_RS at PORTF0_bit;
sbit LCD_EN at PORTF1_bit;
sbit LCD_D4 at PORTF2_bit;
sbit LCD_D5 at PORTF3_bit;
sbit LCD_D6 at PORTF4_bit;
sbit LCD_D7 at PORTF5_bit;

sbit LCD_RS_Direction at DDF0_bit;
sbit LCD_EN_Direction at DDF1_bit;
sbit LCD_D4_Direction at DDF2_bit;
sbit LCD_D5_Direction at DDF3_bit;
sbit LCD_D6_Direction at DDF4_bit;
sbit LCD_D7_Direction at DDF5_bit;


#define centre        !PING0_bit
#define down          !PING1_bit
#define left          !PING2_bit
#define right         !PING3_bit
#define up            !PING4_bit


bit toggle;

unsigned char s = 10;
unsigned char min = 10;
unsigned char hr = 10;
unsigned char dy = 1;
unsigned char dt = 31;
unsigned char mt = 12;
unsigned char yr = 15;
unsigned char hr_format = _12_hour_format;
unsigned char am_pm = am;
unsigned char item_no = 0;

const unsigned char symbol[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00};


void setup();
void startup_tasks();
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void display_parameter(unsigned char x_pos, unsigned char y_pos, unsigned char value);
void showDay(unsigned char day_val, unsigned char x_pos, unsigned char y_pos);
void showMonth(unsigned char month_val, unsigned char x_pos, unsigned char y_pos);
void show_hr_format(unsigned char hr_val, unsigned char hr_format, unsigned char x_pos, unsigned char y_pos);
void change_parameter(unsigned char *value, unsigned char min, unsigned char max);
void showTime();
void showDate();
void showTemp();
void settings();


void Timer_1_ISR()
org IVT_ADDR_TIMER1_OVF
{
    toggle = ~toggle;
}


void main() 
{
     bit set;

     set = 0;
     
     setup();
     startup_tasks();
     
     while(1)
     {

         showTime();
         showDate();
         showTemp();
         
         if(centre)
         {
             while(centre);
             TCCR1B = 0x00;
             TIMSK = 0x00;
             toggle = 1;
             item_no = 1;
             set = 1;
         }
         
         if((set == 1) && ((item_no < 1) || (item_no > 9)))
         {
            setTime(hr, min, s, am_pm, hr_format);
            setDate(dy, dt, mt, yr);
            set = 0;
            item_no = 0;
            toggle = 0;
            TCCR1B = 0x03;
            TIMSK = 0x04;
         }
         
         if(set)
         {
             settings();
         }
         else
         {
             getTime(&hr, &min, &s, &am_pm, hr_format);
             getDate(&dy, &dt, &mt, &yr);
         }
     };
}


void setup()
{
      toggle = 0;
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
      PORTG = 0x1F;
      DDRG = 0x00;
      ASSR = 0x00;
      TCCR0 = 0x00;
      TCNT0 = 0x00;
      OCR0 = 0x00;
      TCCR1A = 0x00;
      TCCR1B = 0x03;
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
      TCCR2 = 0x00;
      TCNT2 = 0x00;
      OCR2 = 0x00;
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
      EICRA = 0x00;
      EICRB = 0x00;
      EIMSK = 0x00;
      TIMSK = 0x04;
      ETIMSK = 0x00;
      UCSR0B = 0x00;
      UCSR1B = 0x00;
      ACSR = 0x80;
      SFIOR = 0x00;
      ADCSRA = 0x00;
      SPCR = 0x00;
      TWCR = 0x00;
      asm sei;
      DS3231_init();
      Lcd_Init();
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Cmd(_LCD_CURSOR_OFF);
}


void startup_tasks()
{
     setTime(hr, min, s, am_pm, hr_format);
     setDate(dy, dt, mt, yr);
     lcd_out(1, 6, "DS3231 RTC");
     lcd_out(2, 1, "Time: --:--:-- ---");
     lcd_out(3, 1, "Date: -- ---- -- ---");
     lcd_out(4, 1, "Temp/ C:");
     load_symbol(4, 6);
}


void load_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char i = 0;
    
    Lcd_Cmd(64);
    for (i = 0; i < 8; i++)
    {
        Lcd_Chr_CP(symbol[i]);
    }
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}


void display_parameter(unsigned char x_pos, unsigned char y_pos, unsigned char value)
{
     unsigned char tmp = 0;
     
     tmp = (value / 10);
     lcd_chr(y_pos, x_pos, (48 + tmp));
     tmp = (value % 10);
     lcd_chr_cp((48 + tmp));
}


void showDay(unsigned char day_val, unsigned char x_pos, unsigned char y_pos)
{
     switch(day_val)
     {
          case 1:
          {
             lcd_out(y_pos, x_pos, "SUN");
             break;
          }
          case 2:
          {
             lcd_out(y_pos, x_pos, "MON");
             break;
          }
          case 3:
          {
             lcd_out(y_pos, x_pos, "TUE");
             break;
          }
          case 4:
          {
             lcd_out(y_pos, x_pos, "WED");
             break;
          }
          case 5:
          {
             lcd_out(y_pos, x_pos, "THR");
             break;
          }
          case 6:
          {
             lcd_out(y_pos, x_pos, "FRI");
             break;
          }
          case 7:
          {
             lcd_out(y_pos, x_pos, "SAT");
             break;
          }
     }
}


void showMonth(unsigned char month_val, unsigned char x_pos, unsigned char y_pos)
{
     switch(month_val)
     {
          case 1:
          {
             lcd_out(y_pos, x_pos, "JAN.");
             break;
          }
          case 2:
          {
             lcd_out(y_pos, x_pos, "FEB.");
             break;
          }
          case 3:
          {
             lcd_out(y_pos, x_pos, "MAR.");
             break;
          }
          case 4:
          {
             lcd_out(y_pos, x_pos, "APR.");
             break;
          }
          case 5:
          {
             lcd_out(y_pos, x_pos, "MAY ");
             break;
          }
          case 6:
          {
             lcd_out(y_pos, x_pos, "JUN.");
             break;
          }
          case 7:
          {
             lcd_out(y_pos, x_pos, "JUL.");
             break;
          }
          case 8:
          {
             lcd_out(y_pos, x_pos, "AUG.");
             break;
          }
          case 9:
          {
             lcd_out(y_pos, x_pos, "SEP.");
             break;
          }
          case 10:
          {
             lcd_out(y_pos, x_pos, "OCT.");
             break;
          }
          case 11:
          {
             lcd_out(y_pos, x_pos, "NOV.");
             break;
          }
          case 12:
          {
             lcd_out(y_pos, x_pos, "DEC.");
             break;
          }
     }
}


void show_hr_format(unsigned char hr_val, unsigned char hr_format, unsigned char x_pos, unsigned char y_pos)
{
     switch(hr_format)
     {
         case _12_hour_format:
         {
              switch(hr_val)
              {
                 case am:
                 {
                      lcd_out(y_pos, x_pos, "A.M");
                      break;
                 }
                 case pm:
                 {
                      lcd_out(y_pos, x_pos, "P.M");
                      break;
                 }
              }
              break;
         }
         case _24_hour_format:
         {
              lcd_out(y_pos, x_pos, "   ");
              break;
         }
     }
}


void change_parameter(unsigned char *value, unsigned char min, unsigned char max)
{
     static signed char tmp;
     
     if(up)
     {
        delay_ms(40);
        tmp++;
     }
     if(down)
     {
        delay_ms(40);
        tmp--;
     }
     
     if(tmp > max)
     {
        tmp = min;
     }
     if(tmp < min)
     {
        tmp = max;
     }
     
     if(left)
     {
        while(left);
        item_no--;
     }
     if(right)
     {
        while(right);
        item_no++;
     }

     *value = (unsigned char)tmp;
}


void showTime()
{
     display_parameter(7, 2, hr);
     display_parameter(10, 2, min);
     display_parameter(13, 2, s);
     if(item_no == 0)
     {
         show_hr_format(am_pm, hr_format, 16, 2);
     }
     
     if(toggle)
     {
        lcd_out(2, 9, ":");
        lcd_out(2, 12, ":");
     }
     else
     {
        lcd_out(2, 9, " ");
        lcd_out(2, 12, " ");
     }
}


void showDate()
{
     display_parameter(7, 3, dt);
     showMonth(mt, 10, 3);
     display_parameter(15, 3, yr);
     showDay(dy, 18, 3);
}


void showTemp()
{
     float temperature = 0;
     unsigned char fraction = 0;
     
     temperature = getTemp();
     if((temperature >= 0.0) && (temperature <= 70.0))
     {
         fraction = temperature;
     
         display_parameter(10, 4, fraction);
         lcd_out(4, 12, ".");
     
         fraction = ((temperature - fraction) * 100);
         display_parameter(13, 4, fraction);
     }
     else
     {
         lcd_out(10, 4, "--.--");
     }
}


void settings()
{
     switch(item_no)
     {
         case 1:
         {
              change_parameter(&hr_format, _24_hour_format, _12_hour_format);
              if(hr_format == _12_hour_format)
              {
                  lcd_out(2, 16, "12H");
              }
              else
              {
                  lcd_out(2, 16, "24H");
              }
              break;
         }
         case 2:
         {
              if(hr_format == _12_hour_format)
              {
                  change_parameter(&am_pm, am, pm);
                  if(am_pm == am)
                  {
                      lcd_out(2, 16, "A.M");
                  }
                  else
                  {
                      lcd_out(2, 16, "P.M");
                  }
              }
              else
              {
                  lcd_out(2, 16, "   ");
                  item_no = 3;
              }
              break;
         }
         case 3:
         {
              if(hr_format == _12_hour_format)
              {
                  change_parameter(&hr, 1, 12);
              }
              else
              {
                  change_parameter(&hr, 0, 23);
              }
              break;
         }
         case 4:
         {
              change_parameter(&min, 0, 59);
              break;
         }
         case 5:
         {
              change_parameter(&s, 0, 59);
              break;
         }
         case 6:
         {
              change_parameter(&dt, 1, 31);
              break;
         }
         case 7:
         {
              change_parameter(&mt, 1, 12);
              break;
         }
         case 8:
         {
              change_parameter(&yr, 0, 99);
              break;
         }
         case 9:
         {
              change_parameter(&dy, 1, 7);
              break;
         }
     }
}