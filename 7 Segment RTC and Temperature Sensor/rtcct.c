#define bt1        !PIND6_bit
#define bt2        !PIND7_bit
#define bt3        !PINE6_bit
#define bt4        !PINE7_bit

#define disp_time  0
#define disp_ampm  1
#define disp_date  2
#define disp_day   3
#define disp_year  4
#define disp_t     5


bit set;
bit tgl;
bit dn_flag;
bit leap_year;
bit changed_date;

unsigned char n = 0;
unsigned char pos = 1;
unsigned char disp_type = 0;

unsigned char s = 50;
unsigned char hr = 11;
unsigned char yr1 = 20;
unsigned char yr2 = 1;
unsigned char min = 59;
unsigned char date = 31;
unsigned char month = 12;
unsigned char dn_counter = 1;
unsigned char day_counter = 1;

unsigned int year = 2015;

unsigned int temperature = 0;

const unsigned char num[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; //0 1 2 3 4 5 6 7 8 9
const unsigned char chr[15] = {0x08, 0x46, 0x21, 0x06, 0x0E, 0x0B, 0x4F, 0x48, 0x2B, 0x23, 0x0C, 0x2F, 0x12, 0x07, 0x41};
//a(0) c(1) d(2) e(3) f(4) h(5) i(6) m(7) n(8) o(9) p(10) r(11) s(12) t(13) u(14)


void setup();
unsigned char inc_dec(signed char value, unsigned char max, unsigned char min);
unsigned int get_temp();


void timer0_ISR()
org IVT_ADDR_TIMER0_OVF
{
    tgl = ~tgl;
    s += 1;
    if(s > 59)
    {
        s = 0;
        min += 1;
        if(min > 59)
        {
            min = 0;
            hr += 1;
            if(hr > 11)
            {
                if(dn_flag)
                {
                    dn_counter += 1;
                    if(dn_counter > 1)
                    {
                        dn_counter = 0;
                        changed_date = 1;
                    }
                    dn_flag = 0;

                    if((dn_counter == 0) && (changed_date))
                    {
                        date += 1;
                        day_counter += 1;

                        if(day_counter > 6)
                        {
                           day_counter = 0;
                        }

                        if((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
                        {
                            if(date > 31)
                            {
                                date = 1;
                                month += 1;
                            }
                        }
                        else if((month == 4) || (month == 6) || (month == 9) || (month == 11))
                        {
                            if(date > 30)
                            {
                                date = 1;
                                month += 1;
                            }
                        }
                        else
                        {
                            if((year % 4) == 0)
                            {
                                if((year % 100) == 0)
                                {
                                    if((year % 400) == 0)
                                    {
                                        leap_year = 1;
                                    }
                                    else
                                    {
                                        leap_year = 0;
                                    }
                                }
                                else
                                {
                                    leap_year = 1;
                                }
                            }
                            else
                            {
                                leap_year = 0;
                            }

                            if((leap_year) && (date > 29))
                            {
                                 date = 1;
                                 month += 1;
                            }
                            else if((!leap_year) && (date > 28))
                            {
                                 date = 1;
                                 month += 1;
                            }
                        }

                        if(month > 12)
                        {
                            month = 1;
                            year += 1;
                        }
                        changed_date = 0;
                    }
                }

                if(hr > 12)
                {
                    hr  = 1;
                    dn_flag = 1;
                }
            }
        }
    }
}


void timer1_ISR()
org IVT_ADDR_TIMER1_OVF
{
     TCNT1H = 0xFC;
     TCNT1L = 0x18;

     switch(pos)
     {
         case 1:
         {
              if(disp_type == disp_time)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                    n = (hr / 10);
                    PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_date)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (date / 10);
                     PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_year)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (yr1 / 10);
                     PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_day)
              {
                  if(set && tgl)
                  {
                     PORTC = 0xFF;
                  }
                 else
                 {
                    switch(day_counter)
                    {
                        case 0:
                        {
                            n = 12;
                            break;
                        }
                        case 1:
                        {
                            n = 12;
                            break;
                        }
                        case 2:
                        {
                            n = 7;
                            break;
                        }
                        case 3:
                        {
                            n = 13;
                            break;
                        }
                        case 4:
                        {
                            n = 14;
                            break;
                        }
                        case 5:
                        {
                            n = 13;
                            break;
                        }
                        case 6:
                        {
                            n = 4;
                            break;
                        }
                    }
                    PORTC = (chr[n]);
                 }
              }
              else if(disp_type == disp_t)
              {
                  n = (temperature / 100);
                  PORTC = (num[n]);
              }
              else if(disp_type == disp_ampm)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                    if(dn_counter)
                    {
                        n = 10;
                    }
                    else
                    {
                        n = 0;
                    }
                    PORTC = (chr[n]);
                 }
              }
              
              if((disp_type == disp_time) && (tgl != 0))
              {
                  PORTA = 0x01;
              }
              else
              {
                  PORTA = 0x11;
              }
              break;
         }
         case 2:
         {
              if(disp_type == disp_time)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (hr % 10);
                     PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_date)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (date % 10);
                     PORTC = (num[n] & 0x7F);
                 }
              }
              else if(disp_type == disp_year)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (yr1 % 10);
                     PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_day)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                      switch(day_counter)
                      {
                          case 0:
                          {
                              n = 0;
                              break;
                          }
                          case 1:
                          {
                              n = 14;
                              break;
                          }
                          case 2:
                          {
                              n = 7;
                              break;
                          }
                          case 3:
                          {
                              n = 14;
                              break;
                          }
                          case 4:
                          {
                              n = 14;
                              break;
                          }
                          case 5:
                          {
                              n = 5;
                              break;
                          }
                          case 6:
                          {
                              n = 11;
                              break;
                          }
                      }
                      PORTC = (chr[n]);
                 }
              }
              else if(disp_type == disp_t)
              {
                  n = ((temperature / 10) % 10);
                  PORTC = (num[n] & 0x7F);
              }
              else if(disp_type == disp_ampm)
              {
                  PORTC = 0xFF;
              }

              if((set == 0) && (disp_type == disp_time) && (tgl != 0))
              {
                  PORTA = 0x02;
              }
              else
              {
                  PORTA = 0x12;
              }
              break;
         }
         case 3:
         {
              if(disp_type == disp_time)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (min / 10);
                     PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_date)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (month / 10);
                     PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_year)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                    n = (yr2 / 10);
                    PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_day)
              {
                  if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                      switch(day_counter)
                      {
                          case 0:
                          {
                              n = 13;
                              break;
                          }
                          case 1:
                          {
                              n = 8;
                              break;
                          }
                          case 2:
                          {
                              n = 8;
                              break;
                          }
                          case 3:
                          {
                              n = 3;
                              break;
                          }
                          case 4:
                          {
                              n = 2;
                              break;
                          }
                          case 5:
                          {
                              n = 11;
                              break;
                          }
                          case 6:
                          {
                              n = 6;
                              break;
                          }
                      }
                      PORTC = (chr[n]);
                 }
              }
              else if(disp_type == disp_t)
              {
                  n = (temperature % 10);
                  PORTC = (num[n]);
              }
              else if(disp_type == disp_ampm)
              {
                  PORTC = 0xFF;
              }

              if((set == 0) && (disp_type == disp_time) && (tgl != 0))
              {
                  PORTA = 0x04;
              }
              else
              {
                  PORTA = 0x14;
              }
              break;
         }
         case 4:
         {
              if(disp_type == disp_time)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                     n = (min % 10);
                     PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_date)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                    n = (month % 10);
                    PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_year)
              {
                 if(set && tgl)
                 {
                     PORTC = 0xFF;
                 }
                 else
                 {
                    n = (yr2 % 10);
                    PORTC = (num[n]);
                 }
              }
              else if(disp_type == disp_day)
              {
                  PORTC = 0xFF;
              }
              else if(disp_type == disp_t)
              {
                  PORTC = chr[1];
              }
              else if(disp_type == disp_ampm)
              {
                  PORTC = 0xFF;
              }

              if((set == 0) && (disp_type == disp_time) && (tgl != 0))
              {
                  PORTA = 0x08;
              }
              else
              {
                  PORTA = 0x18;
              }
              break;
         }
     }
     
     pos++;
     if(pos > 4)
     {
         pos = 1;
     }
}


void main() 
{
     bit configure;
     unsigned char menu = 0;
     unsigned char date_max = 0;
     unsigned int t_present = 0;
     unsigned int t_previous = 0;
     
     set = 0;
     configure = 0;
     
     setup();
     
     t_previous = get_temp();
     
     while(1)
     {
             t_present = get_temp();
             
             if((t_present - t_previous) >= 250)
             {
                temperature = t_previous;
             }
             else if((t_present - t_previous) <= 250)
             {
                temperature = t_present;
             }
             else
             {
                temperature = t_present;
                t_previous = t_present;
             }
             
             if(temperature >= 999)
             {
                temperature = 999;
             }
             if(temperature <= 0)
             {
                temperature = 0;
             }
             
             yr1 = (year / 100);
             yr2 = (year - (yr1 * 100));
             
             if(bt1)
             {
                 while(bt1);
                 configure = 1;
                 menu = 1;
                 set = 1;
             }
             
             if(bt4)
             {
                 while(bt4);
                 disp_type++;
             }
             if(disp_type >= 6)
             {
                disp_type = 0;
             }
             
             
             if(configure)
             {
                 disp_type = disp_time;
                 while(menu == 1)
                 {
                     hr = inc_dec(hr, 12, 1);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }
                 
                 while(menu == 2)
                 {
                     min = inc_dec(min, 59, 0);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }

                 disp_type = disp_ampm;
                 while(menu == 3)
                 {
                     dn_counter = inc_dec(dn_counter, 1, 0);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }
                 
                 disp_type = disp_year;
                 yr1 = (year / 100);
                 yr2 = (year % 100);
                 while(menu == 4)
                 {
                     yr1 = inc_dec(yr1, 99, 0);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }
                 
                 while(menu == 5)
                 {
                     yr2 = inc_dec(yr2, 99, 0);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }
                 year = ((yr1 * 100) + yr2);

                 disp_type = disp_date;
                 while(menu == 6)
                 {
                     month = inc_dec(month, 12, 1);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }
                 
                 if(((month == 4) || (month == 6) || (month == 9) || (month == 11)) && (date > 30))
                 {
                     date_max = 30;
                 }

                 else if(month == 2)
                 {
                    if((year % 4) == 0)
                    {
                        if((year % 100) == 0)
                        {
                            if((year % 400) == 0)
                            {
                                leap_year = 1;
                            }
                            else
                            {
                                leap_year = 0;
                            }
                        }
                        else
                        {
                            leap_year = 1;
                        }
                    }
                    else
                    {
                        leap_year = 0;
                    }

                    if((leap_year) && (date > 29))
                    {
                        date_max = 29;
                    }
                    else if((!leap_year) && (date > 28))
                    {
                        date_max = 28;
                    }
                 }
                 else
                 {
                     date_max = 31;
                 }
                 
                 while(menu == 7)
                 {
                     date = inc_dec(date, date_max, 1);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }
                 
                 disp_type = disp_day;
                 while(menu == 8)
                 {
                     day_counter = inc_dec(day_counter, 6, 0);
                     if(bt4)
                     {
                         while(bt4);
                         delay_ms(200);
                         menu++;
                     }
                 }
                 
                 if(menu >= 9)
                 {
                     disp_type = disp_time;
                     configure = 0;
                     menu = 0;
                     set = 0;
                 }
             }
     };
}


void setup()
{
      dn_flag = 1;
      changed_date = 0;
      PORTA = 0x00;
      DDRA = 0xFF;
      PORTB = 0x00;
      DDRB = 0x00;
      PORTC = 0x00;
      DDRC = 0xFF;
      PORTD = 0xC0;
      DDRD = 0x00;
      PORTE = 0xC0;
      DDRE = 0x00;
      PORTF = 0x00;
      DDRF = 0x00;
      PORTG = 0x00;
      DDRG = 0x00;
      ASSR = 0x08;
      TCCR0 = 0x05;
      TCNT0 = 0x00;
      OCR0 = 0x00;
      TCCR1A = 0x00;
      TCCR1B = 0x02;
      TCNT1H = 0xFC;
      TCNT1L = 0x18;
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
      TIMSK = 0x05;
      ETIMSK = 0x00;
      UCSR0B = 0x00;
      UCSR1B = 0x00;
      ACSR = 0x80;
      SFIOR = 0x00;
      ADCSRA = 0x00;
      SPCR = 0x00;
      TWCR = 0x00;
      SREG_I_bit = 1;
}


unsigned char inc_dec(signed char value, unsigned char max, unsigned char min)
{
      if(bt2)
      {
          delay_ms(200);
          value++;
      }
      
      if(value > max)
      {
          value = min;
      }
      
      if(bt3)
      {
          delay_ms(200);
          value--;
      }

      if(value < min)
      {
          value = max;
      }
      
      return value;
}


unsigned int get_temp()
{
      bit busy;
      unsigned int temp = 0;

      busy = 0;

      Ow_Reset(&PORTG, 2);
      Ow_Write(&PORTG, 2, 0xCC);
      Ow_Write(&PORTG, 2, 0x44);
      while (busy == 0)
      {
          busy = Ow_Read(&PORTG, 2);
      }
      Ow_Reset(&PORTG, 2);
      Ow_Write(&PORTG, 2, 0xCC);
      Ow_Write(&PORTG, 2, 0xBE);
      Delay_ms(600);

      temp =  Ow_Read(&PORTG, 2);
      temp += (Ow_Read(&PORTG, 2) << 8);
      temp >>= 1;
      temp += 40;
      return temp;
}