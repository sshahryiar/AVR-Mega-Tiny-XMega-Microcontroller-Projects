#include "ADXL345.c"
#include "lcd_keypad_shield.h"


void setup();
void show_float_value(unsigned char x_pos, unsigned char y_pos, signed int value);
void show_int_value(unsigned char x_pos, unsigned char y_pos, signed int value);
unsigned int get_resultant(signed int x_val, signed int y_val, signed int z_val);
float map(float v, float x_min, float x_max, float y_min, float y_max);
unsigned char get_key();
unsigned int adc_read(unsigned char adc_input);


void main() 
{
     float scalar = 1;
     
     signed char disp = 0x00;
     
     signed int x_value = 0x0000;
     signed int y_value = 0x0000;
     signed int z_value = 0x0000;
     signed int r_value = 0x0000;
     signed int x_temp = 0x0000;
     signed int y_temp = 0x0000;
     signed int z_temp = 0x0000;
     signed int r_temp = 0x0000;

     setup();
     
     lcd_out(1, 1, "X Y Z");
     
     while(1)
     {
              if(get_key() == UP)
              {
                 disp++;
                 delay_ms(400);
              }
              
              if(disp >= 0x04)
              {
                  disp = 0x00;
              }
              
              if(get_key() == DOWN)
              {
                 disp--;
                 delay_ms(400);
              }
              
              if(disp < 0x00)
              {
                  disp = 0x03;
              }
              
              switch(disp)
              {
                  case 1:
                  {
                      scalar = 1;

                      break;
                  }
                  case 2:
                  {
                      scalar = 4;
                      break;
                  }
                  case 3:
                  {
                      scalar = 0.39;
                      break;
                  }
                  default:
                  {
                      scalar = 1;
                      break;
                  }
              }
              
              if(disp == 1)
              {
                  x_temp = map(x_value, -255, 255, -9000, 9000);
                  y_temp = map(y_value, -255, 255, -9000, 9000);
                  z_temp = map(z_value, -255, 255, -9000, 9000);
              }
              else
              {
                  x_temp = x_value;
                  y_temp = y_value;
                  z_temp = z_value;
              }
              
              if(disp == 0)
              {
                  lcd_out(1, 9, "R:");
                  show_int_value(1, 2, x_temp);
                  show_int_value(7, 2, y_temp);
                  show_int_value(12, 2, z_temp);
                  show_int_value(12, 1, r_value);
              }
              else
              {
                  show_float_value(1, 2, x_temp);
                  show_float_value(7, 2, y_temp);
                  show_float_value(12, 2, z_temp);
                  if(disp == 1)
                  {
                      lcd_out(1, 9, "        ");
                  }
                  else
                  {
                      lcd_out(1, 9, "R:");
                      show_float_value(12, 1, r_value);
                  }
              }
             
             get_values(&x_value, &y_value, &z_value, scalar);
             r_value = get_resultant(x_temp, y_temp, z_temp);
             delay_ms(100);
     };
}


void setup()
{
    PORTB=0x00;
    DDRB=0x03;
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
    SFIOR = 0x00;
    ADCSRA = 0x83;
    ADMUX = 0x40;
    SPCR = 0x00;
    TWCR = 0x00;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    ADXL345_init();
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


unsigned int get_resultant(signed int x_val, signed int y_val, signed int z_val)
{
    signed long temp_x = 0x00000000;
    signed long temp_y = 0x00000000;
    signed long temp_z = 0x00000000;

    unsigned long t = 0x00000000;
    unsigned long b = 0x00000000;
    unsigned long c = 0x00000000;
    unsigned long r = 0x00000000;
    
    temp_x = x_val;
    temp_y = y_val;
    temp_z = z_val;
    
    temp_x *= temp_x;
    temp_y *= temp_y;
    temp_z *= temp_z;
    
    r = (temp_x + temp_y + temp_z);

    for(b = 0x10000000; b != 0; b >>= 2)
    {
      t = c + b;
      c >>= 1;
      if (t <= r)
      {
         r -= t;
         c += b;
      }
   }

   return c;
}


float map(float v, float x_min, float x_max, float y_min, float y_max)
{
    register float m = 0.0;
    m = ((y_max - y_min)/(x_max - x_min));
    return (y_min + (m * (v - x_min)));
}


unsigned char get_key()
{
    unsigned int adc_value = 0;

    adc_value = adc_read(KEYPAD_pin);

    if((adc_value >= 0) && (adc_value < 60))
    {
        return RIGHT;
    }
    else if(((adc_value >= 80) && (adc_value < 160)))
    {
        return UP;
    }
    else if((adc_value >= 220) && (adc_value < 340))
    {
        return DOWN;
    }
    else if(((adc_value >= 360) && (adc_value < 530)))
    {
        return LEFT;
    }
    else if(((adc_value >= 600) && (adc_value < 800)))
    {
        return SELECT;
    }
    else
    {
        return 0xFF;
    }
}


unsigned int adc_read(unsigned char adc_input)
{
    unsigned int hb = 0;
    unsigned char lb = 0;

    ADMUX = (adc_input | 0x40);
    delay_us(10);
    ADCSRA |= 0x40;
    while(!(ADCSRA & 0x10));
    ADCSRA |= 0x10;
    lb = ADCL;
    hb = ADCH;
    hb <<= 8;
    hb |= lb;

    return hb;
}