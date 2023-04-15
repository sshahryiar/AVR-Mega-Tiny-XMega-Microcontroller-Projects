#define SET       PIND0_bit
#define INC       PIND1_bit
#define DEC       PIND2_bit

#define LED1      PORTD4_bit
#define LED2      PORTD5_bit


sbit LCD_RS at PORTB2_bit;
sbit LCD_EN at PORTB3_bit;
sbit LCD_D4 at PORTB4_bit;
sbit LCD_D5 at PORTB5_bit;
sbit LCD_D6 at PORTB6_bit;
sbit LCD_D7 at PORTB7_bit;

sbit LCD_RS_Direction at DDB2_bit;
sbit LCD_EN_Direction at DDB3_bit;
sbit LCD_D4_Direction at DDB4_bit;
sbit LCD_D5_Direction at DDB5_bit;
sbit LCD_D6_Direction at DDB6_bit;
sbit LCD_D7_Direction at DDB7_bit;


bit up_down;
bit toggler;
bit set;
bit alarm;
bit stop_timer;

signed short s = 0;
signed short min = 0;
signed short hr = 0;
signed short s_t = 0;
signed short min_t = 0;
signed short hr_t = 0;

unsigned int ms = 0;

const unsigned char character1[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
const unsigned char character2[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00};
const unsigned char character3[8] = {0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F};
const unsigned char character4[8] = {0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00};
const unsigned char character5[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


void setup();
void LCD_load();
void custom_graphics(unsigned char number, unsigned char pos);
unsigned short scan_kbd();
void display_common(unsigned char x, unsigned char y, signed char convert);
unsigned char changes(unsigned char x, unsigned char y, signed char value, signed char max, signed char min);
void settings();
void enable_timer();
void disable_timer();
void display_numbers(unsigned char data1, unsigned char data2);
void timer_tasks();
void display();
void time_out();


void timer_1_ISR()
org IVT_ADDR_TIMER1_OVF
{
    if(!stop_timer)
    {
          TCNT1H = 0xFC;
          TCNT1L = 0x16;
          ms++;
          if(ms > 999)
          {
                LED1 = ~LED1;
                toggler = ~toggler;
                ms = 0;
                if(up_down)
                {
                            s++;
                            if(s > 59)
                            {
                                 s = 0;
                                 min++;
                                 if(min > 59)
                                 {
                                        min = 0;
                                        hr++;
                                        if(hr > 23)
                                        {
                                              hr = 0;
                                        }
                                 }
                            }
                }
                else
                {
                            s--;
                            if(s < 0)
                            {
                                 s = 59;
                                 min--;
                                 if(min < 0)
                                 {
                                        min = 59;
                                        hr--;
                                        if(hr < 0)
                                        {
                                              hr = 0;
                                        }
                                 }
                            }
                }
          }
    }
}


void main()
{
     setup();
     while(1)
     {
             settings();
             timer_tasks();
             display();
     };
}


void setup()
{
      CLKPR = 0x80;
      CLKPR = 0x00;
      DDRB = 0x00;
      DDRC = 0x00;
      DDRD = 0x38;
      PORTB = 0x00;
      PORTC = 0x00;
      PORTD = 0x00;
      TCCR0A = 0x00;
      TCCR0B = 0x00;
      TCNT0 = 0x00;
      OCR0A = 0x00;
      OCR0B = 0x00;
      TCCR1A = 0x00;
      TCCR1B = 0x02;
      TCNT1H = 0xFC;
      TCNT1L = 0x16;
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
      TIMSK1 = 0x01;
      TIMSK2 = 0x00;
      UCSR0B = 0x00;
      ACSR = 0x80;
      ADCSRB = 0x00;
      DIDR1 = 0x00;
      ADCSRA = 0x00;
      SPCR = 0x00;
      TWCR = 0x00;
      Lcd_Init();
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Cmd(_LCD_CURSOR_OFF);
      Sound_Init(&PORTD,3);
      LCD_load();
      disable_timer();
      up_down = 1;
      toggler = 1;
      alarm = 0;
      asm sei;
}


void LCD_load()
{
    unsigned char i = 0;
    unsigned char dchar = 0;

    for (dchar = 0; dchar <= 4; dchar++)
    {

          LCD_Cmd(64 + (dchar  * 8));
          for (i = 0; i <= 7; i++)
          {
            switch(dchar)
            {
               case 0:
               {
                  LCD_Chr_Cp(character1[i]) ;
                  break;
               }
               case 1:
               {
                  LCD_Chr_Cp(character2[i]);
                  break;
               }
               case 2:
               {
                  LCD_Chr_Cp(character3[i]) ;
                  break;
               }
               case 3:
               {
                  LCD_Chr_Cp(character4[i]);
                  break;
               }
               case 4:
               {
                  LCD_Chr_Cp(character5[i]);
                  break;
               }
            }
          }
    }
}


void custom_graphics(unsigned char number, unsigned char pos)
{
      unsigned char x_pos = 0;
      unsigned char drw_x = 0;
      unsigned char drw_y = 0;

      switch(pos)
      {
            case 1:
            {
                x_pos = 1;
                break;
            }
            case 2:
            {
                x_pos = 6;
                break;
            }
            case 3:
            {
                x_pos = 12;
                break;
            }
            case 4:
            {
                x_pos = 17;
                break;
            }
            default:
            {
                break;
            }
      }

      switch(number)
      {
            case 0:
            {
                for(drw_y = 2; drw_y <= 3; drw_y++)
                {
                    for(drw_x = (x_pos + 1); drw_x <= (x_pos + 2); drw_x++)
                    {
                        lcd_chr(drw_y, drw_x, 4);
                    }
                }
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(1, drw_x, 1);
                    lcd_chr(4, drw_x, 2);
                }
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, x_pos, 0);
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                break;
            }
            case 1:
            {
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                    {
                        lcd_chr(drw_y, drw_x, 4);
                    }
                }
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                break;
            }
            case 2:
            {
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 3); drw_x++)
                {
                    lcd_chr(4, drw_x, 2);
                    lcd_chr(3, drw_x, 4);
                }
                for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(1, drw_x, 1);
                    lcd_chr(2, drw_x, 2);
                }
                for(drw_y = 1; drw_y <= 2; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                for(drw_y = 3; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, x_pos, 0);
                }
                break;
            }
            case 3:
            {
                for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(1, drw_x, 1);
                    lcd_chr(2, drw_x, 2);
                    lcd_chr(3, drw_x, 4);
                    lcd_chr(4, drw_x, 2);
                }
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                break;
            }
            case 4:
            {
                for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                {
                    for(drw_y = 3; drw_y < 5; drw_y++)
                    {
                        lcd_chr(drw_y, drw_x, 4);
                    }
                }
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(1, drw_x, 4);
                    lcd_chr(2, drw_x, 2);
                }
                for(drw_y = 1; drw_y <= 2; drw_y++)
                {
                    lcd_chr(drw_y, x_pos, 0);
                }
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                break;
            }
            case 5:
            {
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 3); drw_x++)
                {
                    lcd_chr(1, drw_x, 1);
                    lcd_chr(2, drw_x, 4);
                }
                for(drw_y = 1; drw_y <= 2; drw_y++)
                {
                    lcd_chr(drw_y, x_pos, 0);
                }
                for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(3, drw_x, 1);
                }
                for(drw_y = 3; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(4, drw_x, 2);
                }
                break;
            }
            case 6:
            {
                for(drw_y = 1; drw_y <= 2; drw_y++)
                {
                    for(drw_x = (x_pos + 1); drw_x <= (x_pos + 3); drw_x++)
                    {
                        lcd_chr(drw_y, drw_x, 4);
                    }
                }
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, x_pos, 0);
                }
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(3, drw_x, 1);
                    lcd_chr(4, drw_x, 2);
                }
                for(drw_y = 3; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                break;
            }
            case 7:
            {
                for(drw_y = 2; drw_y <= 4; drw_y++)
                {
                    for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                    {
                        lcd_chr(drw_y, drw_x, 4);
                    }
                }
                for(drw_x = x_pos; drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(1, drw_x, 1);
                }
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                break;
            }
            case 8:
            {
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(2, drw_x, 2);
                    lcd_chr(3, drw_x, 4);
                }
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(1, drw_x, 1);
                    lcd_chr(4, drw_x, 2);
                }
                for(drw_y = 1; drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, x_pos, 0);
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                break;
            }
            case 9:
            {
                for(drw_x= x_pos; drw_x <= (x_pos + 2); drw_x++)
                {
                    for(drw_y = 3; drw_y <= 4; drw_y++)
                    {
                        lcd_chr(drw_y, drw_x, 4);
                    }
                }
                for(drw_x = (x_pos + 1); drw_x <= (x_pos + 2); drw_x++)
                {
                    lcd_chr(1, drw_x, 1);
                    lcd_chr(2, drw_x, 2);
                }
                for(drw_y = 1;drw_y <= 4; drw_y++)
                {
                    lcd_chr(drw_y, (x_pos + 3), 0);
                }
                for(drw_y = 1; drw_y <= 2; drw_y++)
                {
                    lcd_chr(drw_y, x_pos, 0);
                }
                break;
            }
            default:
            {
                break;
            }
      }
}


unsigned short scan_kbd()
{
      if(SET)
      {
              Sound_Play(1000, 25);
              return 1;
      }
      else if(INC)
      {
              Sound_Play(2000, 25);
              return 2;
      }
      else if(DEC)
      {
              Sound_Play(600, 25);
              return 3;
      }
      else
      {
              return 0;
      }
}


void display_common(unsigned char x, unsigned char y, signed char convert)
{
    unsigned short t = 0;
    t = (convert / 10);
    Lcd_Chr(y, x, (48 + t));
    t = (convert % 10);
    Lcd_Chr(y, (++x),(48 + t));
}


unsigned char changes(unsigned char x, unsigned char y, signed char value, signed char max, signed char min)
{

    while(1)
    {
          display_common(x, y, value);
          if(scan_kbd() == 2)
          {
                    value++;
          }
          if(scan_kbd() == 3)
          {
                    value--;
          }
          if(value > max)
          {
                    value = min;
          }
          if(value < min)
          {
                    value = max;
          }
          if(scan_kbd() == 1)
          {
                    delay_ms(9);
                    while(scan_kbd() == 1);
                    return value;
          }
    }
}


void settings()
{
     if(scan_kbd()==1)
     {
                  delay_ms(40);
                  if(scan_kbd()==1)
                  {
                       disable_timer();
                       Lcd_Cmd(_LCD_CLEAR);
                       while(1)
                       {
                               lcd_out(1, 1, "Set Time:");
                               lcd_out(2, 1, "--:--:--");
                               lcd_out(3, 1, "01 = UP / 00 = DOWN");
                               lcd_out(4, 1, "Type --");
                               delay_ms(200);
                               display_common(1, 2, hr_t);
                               hr_t = changes(1, 2, hr_t, 23, 0);
                               delay_ms(200);
                               display_common(4, 2, min_t);
                               min_t = changes(4, 2, min_t, 59, 0);
                               delay_ms(200);
                               display_common(7, 2, s_t);
                               s_t = changes(7, 2, s_t, 59, 0);
                               delay_ms(200);
                               display_common(6, 4, up_down);
                               up_down = changes(6, 4, up_down, 1, 0);
                               delay_ms(200);
                               break;
                       }
                       enable_timer();
                       Lcd_Cmd(_LCD_CLEAR);
                  }
     }
}


void enable_timer()
{
     if(up_down)
     {
                 s = 0;
                 min = 0;
                 hr = 0;
     }
     else
     {
                 s = s_t;
                 min = min_t;
                 hr = hr_t;
     }
     ms = 0;
     TCCR1A = 0x00;
     TCCR1B = 0x02;
     TCNT1H = 0xFC;
     TCNT1L = 0x16;
     set = 1;
     toggler = 1;
     stop_timer = 0;
     LED1 = 1;
     LED2 = 0;
}


void disable_timer()
{
     LED1 = 0;
     TCNT1H = 0xFC;
     TCNT1L = 0x16;
     TCCR1A = 0x00;
     TCCR1B = 0x00;
     toggler = 1;
     stop_timer = 1;
     set = 0;
}


void display_numbers(unsigned char data1, unsigned char data2)
{
      unsigned char disp1 = 0;
      unsigned char disp2 = 0;
      disp1=(data1 / 10);
      disp2=(data1 % 10);
      custom_graphics(disp1, 3);
      custom_graphics(disp2, 4);
      disp1=(data2 / 10);
      disp2=(data2 % 10);
      custom_graphics(disp1, 1);
      custom_graphics(disp2, 2);
      if(toggler)
      {
                lcd_chr(2, 10, 3);
                lcd_chr(3, 10, 3);
      }
      else
      {
                lcd_chr(2, 10, 4);
                lcd_chr(3, 10, 4);
      }
}


void timer_tasks()
{
             if(set)
             {
                 if(up_down)
                 {
                            if((s == s_t) && (min == min_t) && (hr == hr_t))
                            {
                                  disable_timer();
                                  alarm = 1;
                            }
                 }
                 else
                 {
                            if((s == 0) && (min == 0) && (hr == 0))
                            {
                                  disable_timer();
                                  alarm = 1;
                            }
                 }
             }
             else
             {
                 disable_timer();
             }
}


void display()
{
             if(hr == 0)
             {
                   display_numbers(s, min);
             }
             else
             {
                   display_numbers(min, hr);
             }
             if(alarm)
             {
                      time_out();
                      alarm = 0;
             }
}


void time_out()
{
     unsigned short i = 0;
     for(i = 0; i < 9; i++)
     {
           LED2 ^= 1;
           Sound_Play(600, 45);
           delay_ms(600);
     }
     LED2 = 1;
}