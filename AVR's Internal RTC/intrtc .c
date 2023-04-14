#define set             PINB0_bit
#define change          PINB1_bit
#define save            PINB2_bit
#define LED             PORTB7_bit


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


bit toggle;
unsigned char s = 10;
unsigned char min = 10;
unsigned char hr = 10;


void setup();
void display_time();
void settings();
void display_common(unsigned char y, unsigned char x, unsigned char convert);
void blank_display(unsigned char y, unsigned char x);
unsigned char change_value(unsigned char y, unsigned char x, unsigned char value, unsigned char max);


void timer_2_ISR()
org IVT_ADDR_TIMER2_OVF
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


void main() 
{
     setup();
     while(1)
     {
            if(set)
            {
                     delay_ms(9);
                     while(set);
                     settings();
            }
            else
            {
                     display_time();
            }
     }
}


void setup()
{
    DDRA = 0x00;
    DDRB = 0x80;
    DDRC = 0x00;
    DDRD = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
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
    ASSR = 0x08;
    TCCR2 = 0x05;
    TCNT2 = 0x00;
    OCR2 = 0x00;
    MCUCR = 0x00;
    MCUCSR = 0x00;
    TIMSK = 0x40;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    Sound_Init(&PORTB, 6);
    LCD_Init();
    LCD_Cmd(_LCD_CLEAR);
    LCD_Cmd(_LCD_CURSOR_OFF);
    delay_ms(2000);
    Lcd_Out(1,1,"AVR Internal RTC");
    asm sei;
}


void display_time()
{
    switch(toggle)
    {
        case 1:
        {
             Lcd_Chr(2, 7, ' ');
             Lcd_Chr(2, 10, ' ');
             break;
        }
        default:
        {
             Lcd_Chr(2, 7, ':');
             Lcd_Chr(2, 10, ':');
             break;
        }
    }
    display_common(2, 5, hr);
    display_common(2, 8, min);
    display_common(2, 11, s);
    LED ^= 1;
    toggle ^= 1;
    delay_ms(500);
}


void settings()
{
    while(1)
    {
            Sound_Play(3000, 100);
            Lcd_Chr(2, 7, ':');
            Lcd_Chr(2, 10, ':');
            hr = change_value(2, 5, hr, 23);
            delay_ms(100);
            min = change_value(2, 8, min, 59);
            delay_ms(100);
            s = change_value(2, 11, s, 59);
            break;
    }
}


void display_common(unsigned char y, unsigned char x, unsigned char convert)
{
    unsigned char t = 0;
    t = (convert / 10);
    Lcd_Chr(y, x, (48 + t));
    t = (convert % 10);
    Lcd_Chr(y, (++x), (48 + t));
    delay_ms(160);
}


void blank_display(unsigned char y, unsigned char x)
{
     Lcd_out(y, x, "  ");
     delay_ms(160);
}


unsigned char change_value(unsigned char y, unsigned char x, unsigned char value, unsigned char max)
{
    while(1)
    {
          if(change)
          {
                    LED = 1;
                    Sound_Play(1800, 120);
                    value++;
                    LED = 0;
          }
          else if(value > max)
          {
                    value = 0;
          }
          else if(save)
          {
                    while(save);
                    Sound_Play(2600, 10);
                    LED = 0;
                    return value;
          }
          else
          {
                    blank_display(y, x);
                    display_common(y, x, value);
          }
    }
}