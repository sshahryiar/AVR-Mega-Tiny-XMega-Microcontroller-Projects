#define LED     PORTD0_bit


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


const unsigned char symbol[8] = {0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00};

void setup();
unsigned int read_temp();
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void lcd_show_value(unsigned char x, unsigned char y, float value);


void main() 
{
     float t = 0.0;
     setup();
     while(1)
     {
              t = read_temp();
              if(t < 292)
              {
                   t = ((1.045 * t) - 280.14);
              }
              else
              {
                  t = ((0.983 * t) - 261.98);
              }
              t /= 3.3;
              lcd_show_value(7, 2, t);
              delay_ms(100);
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x01;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
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
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    TCNT2 = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    EICRA = 0x00;
    EIMSK = 0x00;
    PCICR = 0x00;
    TIMSK0 = 0x00;
    TIMSK1 = 0x00;
    TIMSK2 = 0x00;
    UCSR0B = 0x00;
    ADCSRB = 0x00;
    ACSR = 0x80;
    DIDR1 = 0x00;
    DIDR0 = 0x00;
    ADMUX = 0xC0;
    ADCSRA = 0xA4;
    ADCSRB &= 0xF8;
    SPCR = 0x00;
    TWCR = 0x00;
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Out(1, 1, "AVR Temp. Sensor");
    Lcd_Out(2, 1, "T/ C: ");
    load_symbol(2, 3);
}


unsigned int read_temp()
{
    unsigned int adc_res = 0;
    unsigned int temp = 0;
    LED = 1;
    ADMUX = 0xC8;
    delay_us(10);
    ADCSRA |= 0x40;
    while ((ADCSRA & 0x10) == 0);
    ADCSRA |= 0x10;
    adc_res = ADCL;
    temp = ADCH;
    temp <<= 8;
    adc_res |= temp;
    LED = 0;
    return adc_res;
}


void load_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char i = 0;
    Lcd_Cmd(64);
    for (i = 0; i <= 7; i++)
    {
        Lcd_Chr_CP(symbol[i]);
    }
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}


void lcd_show_value(unsigned char x, unsigned char y, float value)
{
     unsigned int tmp = 0;
     unsigned char ch = 0;

     if(value < 0)
     {
         value *= -1;
         LCD_out(y, (x - 1), "-");
     }
     else
     {
         LCD_out(y, (x - 1), " ");
     }

     if((value >= 0) && (value < 10))
     {
         tmp = (value * 1000);
     }
     if((value >= 10) && (value < 100))
     {
         tmp = (value * 100);
     }
     if((value >= 100) && (value < 1000))
     {
         tmp = (value * 10);
     }
     if((value >= 1000) && (value < 10000))
     {
         tmp = value;
     }

     ch = (tmp / 1000);
     LCD_Chr(y, x, (48 + ch));

     if((value >= 0) && (value < 10))
     {
        LCD_Chr_CP(46);
     }
     ch = (tmp / 100) % 10;
     LCD_Chr_CP(48 + ch);

     if((value >= 10) && (value < 100))
     {
        LCD_Chr_CP(46);
     }
     ch = (tmp / 10) % 10;
     LCD_Chr_CP(48 + ch);

     if((value >= 100) && (value < 1000))
     {
        LCD_Chr_CP(46);
     }
     ch = tmp % 10;
     LCD_Chr_CP(48 + ch);

     if((value >= 1000) && (value < 10000))
     {
         LCD_Chr_CP(32);
     }
}