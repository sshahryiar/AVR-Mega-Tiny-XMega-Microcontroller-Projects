#define buffer_size     5

#define in              0
#define out             1
#define low             0
#define high            1
#define DHT22_dir       DDD7_bit
#define DHT22_out       PORTD7_bit
#define DHT22_in        PIND7_bit


sbit LCD_RS at PORTB0_bit;
sbit LCD_EN at PORTB1_bit;
sbit LCD_D4 at PORTB2_bit;
sbit LCD_D5 at PORTB3_bit;
sbit LCD_D6 at PORTB4_bit;
sbit LCD_D7 at PORTB5_bit;

sbit LCD_RS_Direction at DDB0_bit;
sbit LCD_EN_Direction at DDB1_bit;
sbit LCD_D4_Direction at DDB2_bit;
sbit LCD_D5_Direction at DDB3_bit;
sbit LCD_D6_Direction at DDB4_bit;
sbit LCD_D7_Direction at DDB5_bit;


unsigned char buffer[buffer_size];
const unsigned char symbol[8] = {0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00};


void setup();
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void lcd_show_value(unsigned char x, unsigned char y, float value);
unsigned char get_DHT22();
unsigned char read_DHT22();


void main() 
{
     unsigned char state = 0;
     
     float tmp = 0;
     
     setup();
     
     while(1)
     {
          state = get_DHT22();
          
          Lcd_Cmd(_LCD_CLEAR);
          
          switch(state)
          {
                case 1:
                {
                   lcd_out(1, 1, "No Sensor Found!");
                   break;
                }
                case 2:
                {
                   lcd_out(1, 1, "Checksum Error!");
                   break;
                }
                default:
                {
                   tmp =  ((buffer[0] * 256.0 + buffer[1]) * 0.1);
                   
                   lcd_out(1, 1, "R.H/%:");
                   lcd_show_value(8, 1, tmp);
                   
                   tmp =  ((buffer[2] * 256.0 + buffer[3]) * 0.1);
                   
                   lcd_out(2, 1, "T/ C :");
                   load_symbol(2, 3);
                   lcd_show_value(8, 2, tmp);
                   
                   break;
                }
          }
          delay_ms(1000);
     };
}



void setup()
{
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
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
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Delay_ms(600);
}


void load_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char s = 0;
    Lcd_Cmd(64);
    for (s = 0; s < 8; s++)
    {
        Lcd_Chr_CP(symbol[s]);
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


unsigned char get_DHT22()
{
    unsigned char s = 0;
    unsigned char checksum = 0;

    DHT22_dir = out;
    DHT22_out = high;
    DHT22_out = low;
    delay_ms(1);
    DHT22_out = high;
    delay_us(32);
    DHT22_out = low;
    DHT22_dir = in;

    delay_us(2);
    if(DHT22_in)
    {
        return 1;
    }
    delay_us(80);
    
    if(!DHT22_in)
    {
        return 1;
    }
    delay_us(80);
    
    for(s = 0; s <= 4; s += 1)
    {
        buffer[s] = read_DHT22();
    }
    
    DHT22_dir = out;
    DHT22_out = high;
    
    for(s = 0; s < 4; s += 1)
    {
        checksum += buffer[s];
    }
    
    if(checksum != buffer[4])
   {
      return 2;
   }
   else
   {
      return 0;
   }
}


unsigned char read_DHT22()
{
   unsigned char s = 0;
   unsigned char val = 0;
   
   DHT22_dir = in;
   
   for(s = 0; s < 8; s += 1)
   {
      val <<= 1;
      
      while(!DHT22_in);
      delay_us(32);
      if(DHT22_in)
      {
          val |= 1;
      }
      while(DHT22_in);
   }
   return val;
}