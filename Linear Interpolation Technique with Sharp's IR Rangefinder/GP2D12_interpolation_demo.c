#define bt1       PIND0_bit
#define bt2       PIND1_bit
#define bt3       PIND2_bit
#define bt4       PIND3_bit


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


unsigned int adc_value[8];
unsigned char distance[8];

unsigned char s = 0;


void setup();
float filter();
double map(double v, float x_min, float x_max, float y_min, float y_max);
float constrain(float value, float value_min, float value_max);
unsigned char read_keys();
float f_inc_dec(unsigned char x_pos, unsigned char y_pos, float val, float max, float min, unsigned char type);
void calibration_mode();
float get_distance();
void send_to_lcd(unsigned char x, unsigned char y, float value, unsigned char type);
void display_distance();


void main()
{
    setup();
    while(1)
    {
            if(read_keys() == 4)
            {
                delay_ms(100);
                if((read_keys() == 4))
                {
                    calibration_mode();
                }
            }
            else
            {
                display_distance();
            }
    }
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0xF0;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    SPCR = 0x00;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ASSR = 0x00;
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    TCNT2 = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    ASSR = 0x00;
    MCUCR = 0x00;
    TIMSK0 = 0x00;
    TIMSK1 = 0x00;
    TIMSK2 = 0x00;
    UCSR0B=0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    adc_init();
    Sound_Init(&PORTD,7);
    lcd_init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
}


float filter()
{
         unsigned char samples = 0;
         unsigned long tmp = 0;
         float rms = 0.0;
         while(samples < 64)
         {
                       rms = adc_read(0);
                       tmp += (rms * rms);
                       samples++;
         }
         tmp >>= 6;
         rms = sqrt(tmp);
         return rms;
}


double map(double v, float x_min, float x_max, float y_min, float y_max)
{
    float m = 0.0;
    m = ((y_max - y_min)/(x_max - x_min));
    return (y_min + (m * (v - x_min)));
}


float constrain(float value, float value_min, float value_max)
{
      if(value >= value_max)
      {
           return value_max;
      }

      else if(value <= value_min)
      {
           return value_min;
      }

      else
      {
           return value;
      }
}


unsigned char read_keys()
{
         if(bt1)
         {
                Sound_Play(1000, 10);
                return 1;
         }
         else if(bt2)
         {
                Sound_Play(3000, 5);
                return 2;
         }
         else if(bt3)
         {
                Sound_Play(2000, 5);
                return 3;
         }
         else if(bt4)
         {
                Sound_Play(800, 10);
                return 4;
         }
         else
         {
                return 0;
         }
}


float f_inc_dec(unsigned char x_pos, unsigned char y_pos, float val, float max, float min, unsigned char type)
{
         send_to_lcd(x_pos, y_pos, val, 1);
         if(type == 1)
         {
                 if(read_keys() == 2)
                 {
                     val += 0.01;
                 }
                 if(read_keys() == 3)
                 {
                     val -= 0.01;
                 }
         }
         else
         {
                 if(read_keys() == 2)
                 {
                     val += 0.5;
                 }
                 if(read_keys() == 3)
                 {
                     val -= 0.5;
                 }
         }
         val = constrain(val, min, max);
         return val;
}


void calibration_mode()
{
     bit tgl;
     float v = 0.0;
     float d = 0;
     tgl = 0;
     s = 0;
     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 1, "Calibration Mode");
     delay_ms(900);
     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 3, "D:");
     lcd_out(1, 12, "S:");
     lcd_out(2, 3, "V:");
     v = f_inc_dec(5, 2, 2.50, 5, 0, 1);
     while(s < 8)
     {
            send_to_lcd(14, 1, (s + 1), 0);
            if(read_keys()==4)
            {
                   tgl ^= 1;
            }
            if(tgl)
            {
                   lcd_out(2, 1, ">");
                   lcd_out(1, 1, " ");
                   v = f_inc_dec(5, 2, v, 5, 0, 1);
            }
            else
            {
                   lcd_out(1, 1, ">");
                   lcd_out(2, 1, " ");
                   d = f_inc_dec(5, 1, d, 90, 9, 0);
            }
            delay_ms(100);
            if(read_keys() == 1)
            {
                adc_value[s] = map(v, 0, 5, 0, 1023);
                distance[s] = d;
                delay_ms(100);
                s += 1;
            }
     }
     Lcd_Cmd(_LCD_CLEAR);
}


float get_distance()
{
      float pos = 0.0;
      unsigned int x_map1 = 0;
      unsigned int x_map2 = 0;
      unsigned int y_map1 = 0;
      unsigned int y_map2 = 0;
      unsigned int adc = 0;
      unsigned int temp = 0;
      s = 0;
      adc = filter();
      while(s < 7)
      {
            temp = adc_value[s];
            if(adc <= temp)
            {
                   x_map1 = adc_value[s];
                   x_map2 = adc_value[(s + 1)];
                   y_map1 = distance[s];
                   y_map2 = distance[(s + 1)];
            }
            s += 1;
      }
      
      pos = map(adc, x_map1, x_map2, y_map1, y_map2);
      if(pos <= 10)
      {
             pos = 10;
      }
      if(pos >= 80)
      {
             pos = 80;
      }
      return pos;
}


void send_to_lcd(unsigned char x, unsigned char y, float value, unsigned char type)
{
     unsigned int tmp=0;
     unsigned char ch=0;

     if(value < 10)
     {
                 tmp = value * 1000;
     }
     if((value >= 10) && (value < 100))
     {
                  tmp = value * 100;
     }
     ch = tmp / 1000;
     Lcd_Chr(y,x,48+ch);
     if(type == 1)
     {
             if(value < 10)
             {
                         Lcd_Chr_CP(46);
             }
             ch = (tmp / 100) % 10;
             Lcd_Chr_CP(48+ch);
             if((value >= 10) && (value < 100))
             {
                          Lcd_Chr_CP(46);
             }
             ch = (tmp / 10) % 10;
             Lcd_Chr_CP(48+ch);
             ch = tmp % 10;
             Lcd_Chr_CP(48+ch);
     }
}


void display_distance()
{
     float dis = 0.0;
     dis = get_distance();
     lcd_out(1, 1, "Approx. Distance");
     send_to_lcd(5, 2, dis, 1);
     lcd_out(2, 11, "cm");
}