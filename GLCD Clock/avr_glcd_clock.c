#include "background_arts.h"


#define set                 PINC0_bit
#define inc                 PINC1_bit
#define dec                 PINC2_bit


char GLCD_DataPort at PORTD;
char GLCD_DataPort_Direction at DDRD;


sbit GLCD_CS1 at PORTB1_bit;
sbit GLCD_CS2 at PORTB0_bit;
sbit GLCD_RST at PORTB2_bit;
sbit GLCD_RS  at PORTB5_bit;
sbit GLCD_RW  at PORTB6_bit;
sbit GLCD_EN  at PORTB7_bit;

sbit GLCD_CS1_Direction at DDB1_bit;
sbit GLCD_CS2_Direction at DDB0_bit;
sbit GLCD_RS_Direction  at DDB5_bit;
sbit GLCD_RW_Direction  at DDB6_bit;
sbit GLCD_EN_Direction  at DDB7_bit;
sbit GLCD_RST_Direction at DDB2_bit;


unsigned int ms=0;
unsigned char s=0;
unsigned char min=0;
unsigned char hr=0;
unsigned short dis_type=0;

unsigned char s_ptr_l[4];
unsigned char s_ptr_h[4];
unsigned char min_ptr_l[4];
unsigned char min_ptr_h[4];
unsigned char hr_ptr_l[4];
unsigned char hr_ptr_h[4];

float rad=0.0;


void setup();
unsigned short get_input();
unsigned short inc_dec(signed short value, signed short max, signed short min, unsigned char x_pos);
void settings();
void analog_clock();
void digital_clock();
void read_memory();


void timer_1_isr()
org IVT_ADDR_TIMER1_OVF
{
    TCNT1H=0xE0;
    TCNT1L=0xC0;
    ms++;
    if(ms>999)
    {
              ms=0;
              s++;
              if(s>59)
              {
                      s=0;
                      min++;
                      if(min>59)
                      {
                                min=0;
                                hr++;
                                if(hr>23)
                                {
                                         hr=0;
                                }
                      }
              }
    }
}


void main()
{
     bit chk;
     chk=0;
     setup();
     read_memory();

     do
     {
              if(get_input()==1)
              {
                                settings();
              }
              if(get_input()==2)
              {
                                dis_type++;
                                chk=1;
              }
              if(get_input()==3)
              {
                                dis_type--;
                                chk=1;
              }
              if(dis_type>3)
              {
                            dis_type=0;
              }
              if(chk)
              {
                             GLCD_fill(0x00);
                             switch(dis_type)
                             {
                                             case 1:
                                             {
                                                 Glcd_Image(clock_round);
                                                 chk=0;
                                                 break;
                                             }
                                             case 2:
                                             {
                                                  Glcd_Image(clock_round);
                                                  chk=0;
                                                  break;
                                             }
                                             case 3:
                                             {
                                                  Glcd_Image(clock_rectangular);
                                                  chk=0;
                                                  break;
                                             }
                                             default:
                                             {
                                                  Glcd_Box(0, 0, 127, 63, 0);
                                                  chk=0;
                                                  break;
                                             }
                             }
              }
              switch(dis_type)
              {
                             case 1:
                             {
                                 analog_clock();
                                 break;
                             }
                             case 2:
                             {
                                  analog_clock();
                                  break;
                             }
                             case 3:
                             {
                                  analog_clock();
                                  break;
                             }
                             default:
                             {
                                  digital_clock();
                                  break;
                             }
              }


     }while(1);
}


void setup()
{
      Glcd_Init();
      Glcd_Fill(0);
      CLKPR=0x80;
      CLKPR=0x00;
      DDRC=0x08;
      PORTC=0x00;
      TCCR0A=0x00;
      TCCR0B=0x00;
      TCNT0=0x00;
      OCR0A=0x00;
      OCR0B=0x00;
      TCCR1A=0x00;
      TCCR1B=0x01;
      TCNT1H=0xE0;
      TCNT1L=0xC0;
      ICR1H=0x00;
      ICR1L=0x00;
      OCR1AH=0x00;
      OCR1AL=0x00;
      OCR1BH=0x00;
      OCR1BL=0x00;
      ASSR=0x00;
      TCCR2A=0x00;
      TCCR2B=0x00;
      TCNT2=0x00;
      OCR2A=0x00;
      OCR2B=0x00;
      EICRA=0x00;
      EIMSK=0x00;
      PCICR=0x00;
      TIMSK0=0x00;
      TIMSK1=0x01;
      TIMSK2=0x00;
      ACSR=0x80;
      ADCSRB=0x00;
      asm sei;
      Sound_Init(&PORTC, 3);
      rad=3.141592654;
      rad*=6.0;
      rad/=180.0;
}


unsigned short get_input()
{
         if(set)
         {
                delay_ms(25);
                Sound_Play(500, 10);
                return 1;
         }
         else if(inc)
         {
                delay_ms(25);
                Sound_Play(1000, 10);
                return 2;
         }
         else if(dec)
         {
                delay_ms(25);
                Sound_Play(2000, 10);
                return 3;
         }
         else
         {
                return 0;
         }
}


unsigned short inc_dec(signed short value, signed short max, signed short min, unsigned char x_pos)
{
         unsigned char val_ptr_l[4];
         unsigned char val_ptr_h[4];
         unsigned char val_h=0;
         unsigned char val_l=0;
         while(1)
         {
                 val_h=(value/10);
                 val_l=(value%10);
                 ByteToStr(val_l, val_ptr_l);
                 Glcd_Write_Text(val_ptr_l, x_pos, 4, 1);
                 ByteToStr(val_h, val_ptr_h);
                 Glcd_Write_Text(val_ptr_h, (x_pos-6), 4, 1);
                 delay_ms(500);
                 if(get_input()==2)
                 {
                                   value++;
                 }
                 if(get_input()==3)
                 {
                                   value--;
                 }
                 
                 if(value>max)
                 {
                              value=min;
                 }
                 if(value<min)
                 {
                              value=max;
                 }
                 
                 if(get_input()==1)
                 {
                                   return value;
                 }
         }
}


void settings()
{
     Glcd_Box(0, 0, 127, 63, 0);
     TCCR1A=0x00;
     TCCR1B=0x00;
     delay_ms(50);

     s=inc_dec(s,60,0,70);
     Glcd_Write_Char(':', 70, 4, 1);
     eeprom_write(0,s);
     delay_ms(10);
     min=inc_dec(min,60,0,52);
     Glcd_Write_Char(':', 52, 4, 1);
     eeprom_write(1,min);
     delay_ms(10);
     hr=inc_dec(hr,23,0,34);
     eeprom_write(2,hr);
     delay_ms(10);
     
     TCCR1A=0x00;
     TCCR1B=0x01;
     TCNT1H=0xE0;
     TCNT1L=0xC0;
     Glcd_Box(127, 63, 0, 0, 0);
}


void analog_clock()
{
     unsigned int s_prev_1=0;
     unsigned int min_prev_1=0;
     unsigned int hr_prev_1=0;
     unsigned int s_prev_2=0;
     unsigned int min_prev_2=0;
     unsigned int hr_prev_2=0;

     unsigned int s_fut_1=0;
     unsigned int min_fut_1=0;
     unsigned int hr_fut_1=0;
     unsigned int s_fut_2=0;
     unsigned int min_fut_2=0;
     unsigned int hr_fut_2=0;

     unsigned int s_pres_1=0;
     unsigned int min_pres_1=0;
     unsigned int hr_pres_1=0;
     unsigned int s_pres_2=0;
     unsigned int min_pres_2=0;
     unsigned int hr_pres_2=0;
     
     s_prev_1=((62+(signed char)(20*sin((s-1)*rad))));
     min_prev_1=((62+(signed char)(16*sin((min-1)*rad))));
     hr_prev_1=((62+(signed char)(10*sin(((hr*5)-1)*rad))));
     s_prev_2=((32-(signed char)(20*cos((s-1)*rad))));
     min_prev_2=((32-(signed char)(16*cos((min-1)*rad))));
     hr_prev_2=((32-(signed char)(10*cos(((hr*5)-1)*rad))));
     
     s_fut_1=((62+(signed char)(20*sin((s+1)*rad))));
     min_fut_1=((62+(signed char)(16*sin((min+1)*rad))));
     hr_fut_1=((62+(signed char)(10*sin(((hr*5)+1)*rad))));
     s_fut_2=((32-(signed char)(20*cos((s+1)*rad))));
     min_fut_2=((32-(signed char)(16*cos((min+1)*rad))));
     hr_fut_2=((32-(signed char)(10*cos(((hr*5)+1)*rad))));
     
     s_pres_1=((62+(signed char)(20*sin(s*rad))));
     min_pres_1=((62+(signed char)(16*sin(min*rad))));
     hr_pres_1=((62+(signed char)(10*sin((hr*5)*rad))));
     s_pres_2=((32-(signed long)(20*cos(s*rad))));
     min_pres_2=((32-(signed long)(16*cos(min*rad))));
     hr_pres_2=((32-(signed long)(10*cos((hr*5)*rad))));
     
     if(dis_type==1)
     {
                     Glcd_Circle_Fill(s_prev_1, s_prev_2, 2, 0);
                     Glcd_Circle_Fill(s_fut_1, s_fut_2, 2, 0);
                     Glcd_Circle_Fill(min_prev_1, min_prev_2, 3, 0);
                     Glcd_Circle_Fill(min_fut_1, min_fut_2, 3, 0);
                     Glcd_Circle_Fill(hr_prev_1, hr_prev_2, 4, 0);
                     Glcd_Circle_Fill(hr_fut_1, hr_fut_2, 4, 0);
                     Glcd_Circle_Fill(62, 32, 2, 0);
                     Glcd_Circle_Fill(s_pres_1, s_pres_2, 2, 1);
                     Glcd_Circle_Fill(min_pres_1, min_pres_2, 3, 1);
                     Glcd_Circle_Fill(hr_pres_1, hr_pres_2, 4, 1);
                     Glcd_Circle_Fill(62, 32, 2, 0);
                     delay_ms(500);
     }

     else
     {
                     Glcd_Circle_Fill(62, 32, 2, 1);
                     Glcd_Line(62, 32, s_pres_1, s_pres_2, 1);
                     Glcd_Line(62, 32, min_pres_1, min_pres_2, 1);
                     Glcd_Line(62, 32, hr_pres_1, hr_pres_2, 1);
                     Glcd_Circle_Fill(62, 32, 2, 1);

                     delay_ms(500);
                     Glcd_Line(62, 32, s_fut_1, s_fut_2, 0);
                     Glcd_Line(62, 32, min_fut_1, min_fut_2, 0);
                     Glcd_Line(62, 32, hr_fut_1, hr_fut_2, 0);

                     Glcd_Line(62, 32, s_prev_1, s_prev_2, 0);
                     Glcd_Line(62, 32, min_prev_1, min_prev_2, 0);
                     Glcd_Line(62, 32, hr_prev_1, hr_prev_2, 0);
     }
}


void digital_clock()
{
    unsigned char s_l=0;
    unsigned char s_h=0;
    unsigned char min_l=0;
    unsigned char min_h=0;
    unsigned char hr_l=0;
    unsigned char hr_h=0;
    s_h=(s/10);
    s_l=(s%10);
    min_h=(min/10);
    min_l=(min%10);
    hr_h=(hr/10);
    hr_l=(hr%10);
    ByteToStr(s_l, s_ptr_l);
    Glcd_Write_Text(s_ptr_l, 70, 4, 1);
    ByteToStr(s_h, s_ptr_h);
    Glcd_Write_Text(s_ptr_h, 64, 4, 1);
    Glcd_Write_Char(':', 70, 4, 1);
    ByteToStr(min_l, min_ptr_l);
    Glcd_Write_Text(min_ptr_l, 52, 4, 1);
    ByteToStr(min_h, min_ptr_h);
    Glcd_Write_Text(min_ptr_h, 46, 4, 1);
    Glcd_Write_Char(':', 52, 4, 1);
    ByteToStr(hr_l, hr_ptr_l);
    Glcd_Write_Text(hr_ptr_l, 34, 4, 1);
    ByteToStr(hr_h, hr_ptr_h);
    Glcd_Write_Text(hr_ptr_h, 28, 4, 1);
    delay_ms(100);
}


void read_memory()
{
      s=eeprom_read(0);
      delay_ms(10);
      min=eeprom_read(1);
      delay_ms(10);
      hr=eeprom_read(2);
      delay_ms(10);
      if(s>59)
      {
          eeprom_write(0,30);
          delay_ms(10);
      }
      if(min>59)
      {
          eeprom_write(1,10);
          delay_ms(10);
      }
      if(hr>23)
      {
          eeprom_write(2,10);
          delay_ms(10);
      }
      s=eeprom_read(0);
      delay_ms(10);
      min=eeprom_read(1);
      delay_ms(10);
      hr=eeprom_read(2);
      delay_ms(10);
}