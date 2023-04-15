#include "background_art.c"


#define up_btn      PINC0_bit
#define down_btn    PINC1_bit
#define left_btn    PINC2_bit
#define right_btn   PINC3_bit
#define enter_btn   PINC4_bit

#define no_cmd      0
#define up_cmd      1
#define down_cmd    2
#define left_cmd    3
#define right_cmd   4
#define enter_cmd   5

#define char_width  4
#define kbd_delay  16
#define position   24

#define Giga       1000000000.0
#define Mega       1000000.0
#define kilo       1000.0
#define mili       0.001
#define micro      0.000001
#define nano       0.000000001
#define pico       0.000000000001


sbit GLCD_RS  at PORTB2_bit;
sbit GLCD_RW  at PORTB3_bit;
sbit GLCD_EN  at PORTB4_bit;
sbit GLCD_CS2 at PORTB5_bit;
sbit GLCD_CS1 at PORTB6_bit;
sbit GLCD_RST at PORTB7_bit;

sbit GLCD_RS_Direction  at DDB2_bit;
sbit GLCD_RW_Direction  at DDB3_bit;
sbit GLCD_EN_Direction  at DDB4_bit;
sbit GLCD_CS2_Direction at DDB5_bit;
sbit GLCD_CS1_Direction at DDB6_bit;
sbit GLCD_RST_Direction at DDB7_bit;

unsigned char GLCD_DataPort at PORTD;
unsigned char GLCD_DataPort_Direction at DDRD;


void setup();
void clear_screen(unsigned char cmd);
void welcome_message();
unsigned short get_keypad();
unsigned char options_menu();
void glcd_show_value(unsigned char x, unsigned char y, float value);
signed short select_value(signed short value, signed short value_max, signed short value_min);
float inc_dec(unsigned char x_pos, unsigned char y_pos, float value, float value_max, float value_min);
float multiplier_inc_dec(unsigned char x_pos, unsigned char y_pos, float value, float value_max, float value_min);
void show_result(unsigned char x_pos, unsigned char y_pos, float value);


void main()
{
     unsigned short state = 0;
     unsigned short cursor_pos = 0;

     float D = 0.0;
     float T = 0.0;
     float f = 0.0;
     float R1 = 100.0;
     float R2 = 100.0;
     float C1 = 100.0;
     float res1 = 100.0;
     float res2 = 100.0;
     float cap1 = 100.0;
     float R1_mul = kilo;
     float R2_mul = kilo;
     float C1_mul = nano;
     
     setup();
     welcome_message();

     while(1)
     {
           switch(state)
           {
               case 1:
               {   
                   glcd_show_value(90, 2, 10.0);
                   while(get_keypad() != enter_cmd)
                   {
                       cursor_pos = select_value(cursor_pos, 6, 0);
                       switch(cursor_pos)
                       {
                           case 0:
                           {   C1 = inc_dec(90, 1, C1, 100.0, 0.1);
                               break;
                           }
                           case 1:
                           {   C1_mul = multiplier_inc_dec(114, 1, C1_mul, micro, nano);
                               break;
                           }
                           case 2:
                           {
                               R1 = inc_dec(90, 3, R1, 100.0, 0.1);
                               break;
                           }
                           case 3:
                           {
                               R1_mul = multiplier_inc_dec(114, 3, R1_mul, Mega, 1);
                               break;
                           }
                           case 4:
                           {
                               R2 = inc_dec(90, 4, R2, 100.0, 0.1);
                               break;
                           }
                           case 5:
                           {
                               R2_mul = multiplier_inc_dec(114, 4, R2_mul, Mega, 1);
                               break;
                           }
                           default:
                           {
                               cap1 = (C1 * C1_mul);
                               res1 = (R1 * R1_mul);
                               res2 = (R2 * R2_mul);
                               f = (0.69 * cap1 * (res1 + (2 * res2)));
                               D = (0.69 * cap1 * (res1 + res2));
                               D /= f;
                               D *= 100;
                               f = (1.0 / f);
                               break;
                           }
                       }
                       
                       show_result(90, 6, D);
                       show_result(90, 7, f);
                       
                       Glcd_Dot(65, 25, 2);
                       if((f >= mili) && (f < 1))
                       {
                          delay_ms(1000);
                       }
                       if((f >= 1) && (f < kilo))
                       {
                          delay_ms(100);
                       }
                       if((f >= kilo) && (f < Mega))
                       {
                          delay_ms(10);
                       }
                   }
                   clear_screen(1);
                   state = 0;
                   break;
               }
               case 2:
               {
                   glcd_show_value(90, 2, 10.0);
                   while(get_keypad() != enter_cmd)
                   {
                       cursor_pos = select_value(cursor_pos, 4, 0);
                       switch(cursor_pos)
                       {
                           case 0:
                           {   C1 = inc_dec(90, 1, C1, 100.0, 0.1);
                               break;
                           }
                           case 1:
                           {   C1_mul = multiplier_inc_dec(114, 1, C1_mul, micro, nano);
                               break;
                           }
                           case 2:
                           {
                               R1 = inc_dec(90, 3, R1, 100.0, 0.1);
                               break;
                           }
                           case 3:
                           {
                               R1_mul = multiplier_inc_dec(114, 3, R1_mul, Mega, 1);
                               break;
                           }
                           default:
                           {
                               cap1 = (C1 * C1_mul);
                               res1 = (R1 * R1_mul); 
                               T = (1.1 * cap1 * res1);
                               break;
                           }
                       }
                       
                       Glcd_Dot(1, 42, 2);
                       if((T >= mili) && (T < 1))
                       {
                          delay_ms(10);
                       }
                       if((T >= 1) && (T < kilo))
                       {
                          delay_ms(100);
                       }
                       if((T >= kilo) && (T < Mega))
                       {
                          delay_ms(1000);
                       }
                       Glcd_Dot(65, 25, 2);
                       show_result(90, 7, T);
                   }
                   clear_screen(1);
                   state = 0;
                   break;
               }
               default:
               {
                   D = 0.0;
                   T = 0.0;
                   f = 0.0;
                   R1 = 100.0;
                   R2 = 100.0;
                   C1 = 100.0;
                   res1 = 100.0;
                   res2 = 100.0;
                   cap1 = 100.0;
                   R1_mul = kilo;
                   R2_mul = kilo;
                   C1_mul = nano;
                   state = options_menu();
                   break;
               }
           }
     };
}


void setup()
{
    glcd_init();
    clear_screen(0);
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    TIMSK0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x02;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    TIMSK1 = 0x00;
    ASSR = 0x00;
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    TCNT2 = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    EICRA = 0x00;
    EIMSK = 0x00;
    PCICR = 0x00;
    TIMSK2 = 0x00;
    UCSR0B = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    SREG_I_bit = 0;
    Sound_Init(&PORTB, 0);
    delay_ms(200);
}


void clear_screen(unsigned char cmd)
{
     unsigned short i = 0;

     switch(cmd)
     {
         case 1:
         {
              for(i = 0; i < 64; i += 1)
              {
                  Glcd_Line((63 - i), 0, (63 - i), 63, 0);
                  Glcd_Line((63 + i), 63, (63 + i), 0, 0);
                  delay_ms(2);
              }
              break;
         }
         case 2:
         {
              for(i = 0; i < 32; i += 1)
              {
                  Glcd_Line(0, (i + 32), 127, (i + 32), 0);
                  Glcd_Line(127, (31 - i), 0, (31 - i), 0);
                  delay_ms(2);
              }
              break;
         }
         case 3:
         {
              glcd_fill(0xFF);
              break;
         }
         default:
         {
              glcd_fill(i);
              break;
         }
     }
}


void welcome_message()
{
     const unsigned char msg1[11] = {"Welcome to"};
     const unsigned char msg2[15] = {"555 Calculator"};
     const unsigned char msg3[11] = {"MicroArena"};

     Glcd_Write_Const_Text(msg1, 34, 2, 1);
     delay_ms(600);
     Glcd_Write_Const_Text(msg2, 20, 4, 1);
     delay_ms(600);
     Glcd_Write_Const_Text(msg3, 34, 6, 1);
     delay_ms(2000);
     clear_screen(1);
}


unsigned short get_keypad()
{
    if(up_btn)
    {
        Sound_Play(2200, kbd_delay);
        return up_cmd;
    }
    else if(down_btn)
    {
        Sound_Play(1800, kbd_delay);
        return down_cmd;
    }
    else if(left_btn)
    {
        Sound_Play(3200, kbd_delay);
        return left_cmd;
    }
    else if(right_btn)
    {
        Sound_Play(2800, kbd_delay);
        return right_cmd;
    }
    else if(enter_btn)
    {
        Sound_Play(1100, kbd_delay);
        return enter_cmd;
    }
    else
    {
        return no_cmd;
    }
}


void glcd_show_value(unsigned char x, unsigned char y, float value)
{
     unsigned int tmp = 0;
     unsigned char ch = 0;

     /*if(value < 0)
     {
         value *= -1;
         Glcd_Write_Const_Text("-", (x - char_width - 2), y, 1);
     }
     else
     {
         Glcd_Write_Const_Text(" ", (x - char_width - 2), y, 1);
     } */
     if((value >= 0.0) && (value < 10.0))
     {
         tmp = (value * 1000.0);
     }
     else if((value >= 10.0) && (value < 100.0))
     {
         tmp = (value * 100.0);
     }
     else if((value >= 100.0) && (value < 1000.0))
     {
         tmp = (value * 10.0);
     }

     ch = (tmp / 1000.0);
     Glcd_Write_char((48 + ch), x, y, 1);

     if((value >= 0.0) && (value < 10.0))
     {
        Glcd_Dot((x + 2 + char_width), ((8 * y) + 6), 1);
        Glcd_Dot((x + 2 + (char_width * 3)), ((8 * y) + 6), 0);
     }
     ch = ((tmp / 100) % 10);
     Glcd_Write_char((48 + ch), (x + (char_width * 2)), y, 1);

     if((value >= 10.0) && (value < 100.0))
     {
        Glcd_Dot((x + 2 + (char_width * 3)), ((8 * y) + 6), 1);
        Glcd_Dot((x + 2 + char_width), ((8 * y) + 6), 0);
     }
     ch = ((tmp / 10) % 10);
     Glcd_Write_char((48 + ch), (x + (char_width * 4)), y, 1);

     if((value >= 100.0) && (value < 1000.0))
     {
        Glcd_Dot((x + 2 + char_width), ((8 * y) + 6), 0);
        Glcd_Dot((x + 2 + (char_width * 3)), ((8 * y) + 6), 0);
     }
}


unsigned char options_menu()
{
    unsigned char mode = 1;
    Glcd_Write_Const_Text("Astable Mode", 24, 2, 1);
    Glcd_Write_Const_Text("One Shot Mode", 24, 4, 1);
    while(get_keypad() != enter_cmd)
    {
        if(get_keypad() == up_cmd)
        {
            mode += 1;
        }
        if(mode > 2)
        {
            mode = 1;
        }
        if(get_keypad() == down_cmd)
        {
            mode -= 1;
        }
        if(mode < 1)
        {
            mode = 2;
        }
        if(mode == 1)
        {
            Glcd_Write_Const_Text(">>", 10, 2, 1);
            Glcd_Write_Const_Text("  ", 10, 4, 1);
        }
        if(mode == 2)
        {
            Glcd_Write_Const_Text(">>", 10, 4, 1);
            Glcd_Write_Const_Text("  ", 10, 2, 1);
        }
    }
    
    clear_screen(2);
    
    switch(mode)
    {
        case 1:
        {
            glcd_image(astable);
            Glcd_Write_Const_Text("Astable", 72, 0, 1);
            Glcd_Write_Const_Text("C1:    ", 72, 1, 1);
            Glcd_Write_Const_Text("C2:    n", 72, 2, 1);
            Glcd_Write_Const_Text("R1:", 72, 3, 1);
            Glcd_Write_Const_Text("R2:", 72, 4, 1);
            Glcd_Write_Const_Text("D%:     ", 72, 6, 1);
            Glcd_Write_Const_Text("Hz:     ", 72, 7, 1);
            break;
        }
        case 2:
        {
            glcd_image(monostable);
            Glcd_Write_Const_Text("One Shot", 72, 0, 1);
            Glcd_Write_Const_Text("C1:     ", 72, 1, 1);
            Glcd_Write_Const_Text("C2:    n", 72, 2, 1);
            Glcd_Write_Const_Text("R1:", 72, 3, 1);
            Glcd_Write_Const_Text("T:", 72, 7, 1);
            break;
        }
    }
    
    return mode;
}


signed short select_value(signed short value, signed short value_max, signed short value_min)
{
    if(get_keypad() == right_cmd)
    {
        value += 1;
    }
    if(value >= value_max)
    {
        value = value_max;
    }
    
    if(get_keypad() == left_cmd)
    {
        value -= 1;
    }
    if(value <= value_min)
    {
        value = value_min;
    }
    return value;
}


float inc_dec(unsigned char x_pos, unsigned char y_pos, float value, float value_max, float value_min)
{
   if(get_keypad() == up_cmd)
   {
      value += 0.1;
   }
   
   if(value > value_max)
   {
       value = value_min;
   }
   
   if(get_keypad() == down_cmd)
   {
      value -= 0.1;
   }

   if(value < value_min)
   {
       value = value_max;
   }
   
   Glcd_Write_Const_Text("    ", x_pos, y_pos, 1);
   delay_ms(30);
   
   glcd_show_value(x_pos, y_pos, value);
   delay_ms(90);
   
   return value;
}


float multiplier_inc_dec(unsigned char x_pos, unsigned char y_pos, float value, float value_max, float value_min)
{
   if(get_keypad() == up_cmd)
   {
      value *= 1000.0;
   }

   if(value > value_max)
   {
       value = value_min;
   }

   if(get_keypad() == down_cmd)
   {
      value /= 1000.0;
   }

   if(value < value_min)
   {
       value = value_max;
   }

   Glcd_Write_Const_Text(" ", x_pos, y_pos, 1);
   delay_ms(30);

   if((value >= nano) && (value < micro))
   {
       Glcd_Write_Const_Text("n", x_pos, y_pos, 1);
   }
   if((value >= micro) && (value < mili))
   {
       Glcd_Write_Const_Text("u", x_pos, y_pos, 1);
   }
   if((value >= mili) && (value < 1))
   {
       Glcd_Write_Const_Text("m", x_pos, y_pos, 1);
   }
   if((value >= 1) && (value < kilo))
   {
       Glcd_Write_Const_Text(" ", x_pos, y_pos, 1);
   }
   if((value >= kilo) && (value < Mega))
   {
       Glcd_Write_Const_Text("k", x_pos, y_pos, 1);
   }
   if((value >= Mega) && (value < Giga))
   {
       Glcd_Write_Const_Text("M", x_pos, y_pos, 1);
   }
   delay_ms(90);

   return value;
}

void show_result(unsigned char x_pos, unsigned char y_pos, float value)
{
   if((value >= nano) && (value < micro))
   {
       Glcd_Write_Const_Text("n", (x_pos + position), y_pos, 1);
       glcd_show_value(x_pos, y_pos, (value * Giga));
   }
   if((value >= micro) && (value < mili))
   {
       Glcd_Write_Const_Text("u", (x_pos + position), y_pos, 1);
       glcd_show_value(x_pos, y_pos, (value * Mega));
   }
   if((value >= mili) && (value < 1))
   {
       Glcd_Write_Const_Text("m", (x_pos + position), y_pos, 1);
       glcd_show_value(x_pos, y_pos, (value * kilo));
   }
   if((value >= 1) && (value < kilo))
   {
       Glcd_Write_Const_Text(" ", (x_pos + position), y_pos, 1);
       glcd_show_value(x_pos, y_pos, value);
   }
   if((value >= kilo) && (value < Mega))
   {
       Glcd_Write_Const_Text("k", (x_pos + position), y_pos, 1);
       glcd_show_value(x_pos, y_pos, (value * mili));
   }
   if((value >= Mega) && (value < Giga))
   {
       Glcd_Write_Const_Text("M", (x_pos + position), y_pos, 1);
       glcd_show_value(x_pos, y_pos, (value * micro));
   }
}

