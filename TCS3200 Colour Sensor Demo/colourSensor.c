#define S0      PORTB1_bit
#define S1      PORTB2_bit
#define S2      PORTB3_bit
#define S3      PORTB4_bit
#define LED     PORTB5.bit

#define TCSin   PINB0_bit

#define Red_Filter      0
#define Blue_Filter     1
#define Pass_All        2
#define Green_Filter    3

#define Power_Down      0
#define f_2             1
#define f_20            2
#define f_100           3

#define LED_On          1
#define LED_Off         0


sbit LCD_RS at PORTD2_bit;
sbit LCD_EN at PORTD3_bit;
sbit LCD_D4 at PORTD4_bit;
sbit LCD_D5 at PORTD5_bit;
sbit LCD_D6 at PORTD6_bit;
sbit LCD_D7 at PORTD7_bit;

sbit LCD_RS_Direction at DDD2_bit;
sbit LCD_EN_Direction at DDD3_bit;
sbit LCD_D4_Direction at DDD4_bit;
sbit LCD_D5_Direction at DDD5_bit;
sbit LCD_D6_Direction at DDD6_bit;
sbit LCD_D7_Direction at DDD7_bit;


unsigned long ov_cnt = 0, clks = 0, start = 0, stop = 0;


void setup();
void TCS3200(unsigned char frequency_selection, unsigned char filter_selection, unsigned char LED_state);
float get_Frequency();
float avg(float V1, float V2);
float percentile(float V1, float V2);


void rollover()
org IVT_ADDR_TIMER1_OVF
{
    ov_cnt++;
}


void capture()
org IVT_ADDR_TIMER1_CAPT
{
    stop = ((ICR1H << 8) + ICR1L);
    clks = ((unsigned long)(ov_cnt << 16) + stop - start);
    ov_cnt = 0;
    start = stop;
    stop = 0;
}


void main() 
{
     unsigned char t1[6];
     unsigned char t2[6];
     unsigned char t3[6];
     
     float R1 = 0.0;
     float G1 = 0.0;
     float B1 = 0.0;
     float A1 = 0.0;
     float R2 = 0.0;
     float G2 = 0.0;
     float B2 = 0.0;
     float A2 = 0.0;
     
     setup();
     while(1)
     {
            TCS3200(f_2, Pass_All, LED_Off);
            A1 =  get_Frequency();
            TCS3200(f_2, Red_Filter, LED_Off);
            R1 =  get_Frequency();
            TCS3200(f_2, Green_Filter, LED_Off);
            G1 =  get_Frequency();
            TCS3200(f_2, Blue_Filter, LED_Off);
            B1 =  get_Frequency();
            TCS3200(Power_Down, Pass_All, LED_Off);
            
            TCS3200(f_2, Pass_All, LED_On);
            A2 =  get_Frequency();
            TCS3200(f_2, Red_Filter, LED_On);
            R2 =  get_Frequency();
            TCS3200(f_2, Green_Filter, LED_On);
            G2 =  get_Frequency();
            TCS3200(f_2, Blue_Filter, LED_On);
            B2 =  get_Frequency();
            TCS3200(Power_Down, Pass_All, LED_On);

            A1 = avg(A1, A2);
            R1 = avg(R1, R2);
            G1 = avg(G1, G2);
            B1 = avg(B1, B2);
            
            R1 = percentile(R1, A1);
            G1 = percentile(G1, A1);
            B1 = percentile(B1, A1);
            
            ByteToStr(R1, t1);
            Lcd_Out(2, 10, t1);
            ByteToStr(G1, t2);
            Lcd_Out(3, 10, t2);
            ByteToStr(B1, t3);
            Lcd_Out(4, 10, t3);
     };
}


void setup()
{
    DDRB = 0x3E;
    DDRC = 0x00;
    DDRD = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x41;
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
    TIMSK = 0x24;
    ACSR = 0x80;
    SFIOR = 0x00;
    asm sei;
    TCS3200(Power_Down, Pass_All, LED_Off);
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Out(1, 1, "Relative Percentage.");
    Lcd_Out(2, 1, "Red   %: ");
    Lcd_Out(3, 1, "Green %: ");
    Lcd_Out(4, 1, "Blue  %: ");
}


void TCS3200(unsigned char frequency_selection, unsigned char filter_selection, unsigned char LED_state)
{
     PORTB = (((LED_state << 4) | (filter_selection << 2) | frequency_selection)  << 1);
}


float get_Frequency()
{
      float f = 0.0;
      unsigned char samples = 0;
      for(samples = 0; samples < 4; samples++)
      {
                  f += (8000000.0 / ((float)clks));
                  delay_ms(10);
      }
      f /= 4.0;
      return f;
}


float avg(float V1, float V2)
{
     return ((V1 + V2) / 2.0);
}


float percentile(float V1, float V2)
{
      float v = 0;
      v = (V1 / V2);
      v *= 100.0;
      v -= 100;
      if(v > 100)
      {
           v = 100;
      }
      if(v < 0)
      {
           v = 0;
      }
      return v;
}



