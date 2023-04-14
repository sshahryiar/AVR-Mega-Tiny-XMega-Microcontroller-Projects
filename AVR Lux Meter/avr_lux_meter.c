#define no_of_samples    512


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


static void setup();
unsigned int filter_adc();


void main() 
{
      unsigned int disp_avg[4];
      unsigned int avg=0;
      unsigned long lux_value=0;
      
      setup();
      
      do
      {
              
              avg=filter_adc();
              
              if(avg>=0 && avg<=286)
              {
                        lux_value=0;
              }
              else if(avg>286 && avg<410)
              {
                        lux_value=1600;
              }
              else if(avg>=410 && avg<470)
              {
                        lux_value=3200;
              }
              else if(avg>=470 && avg<500)
              {
                        lux_value=4800;
              }
              else if(avg>=500 && avg<510)
              {
                        lux_value=6400;
              }
              else if(avg>=510 && avg<520)
              {
                        lux_value=8000;
              }
              else if(avg>=520 && avg<530)
              {
                        lux_value=9600;
              }
              else if(avg>=530 && avg<535)
              {
                        lux_value=11200;
              }
              else if(avg>=535 && avg<540)
              {
                        lux_value=12800;
              }
              else if(avg>=540 && avg<545)
              {
                        lux_value=14400;
              }
              else if(avg>=545 && avg<550)
              {
                        lux_value=16000;
              }
              else
              {
                    Lcd_Out(2,6,"Max Limit!  ");
              }
              
              LongToStr(lux_value,disp_avg);
              Lcd_Out(2,6,disp_avg);
              
      }while(1);
      
}


static void setup()
{
      PORTB=0x00;
      DDRB=0x00;
      PORTC=0x00;
      DDRC=0x00;
      PORTD=0x00;
      DDRD=0x00;
      TCCR0=0x00;
      TCNT0=0x00;
      TCCR1A=0x00;
      TCCR1B=0x00;
      TCNT1H=0x00;
      TCNT1L=0x00;
      ICR1H=0x00;
      ICR1L=0x00;
      OCR1AH=0x00;
      OCR1AL=0x00;
      OCR1BH=0x00;
      OCR1BL=0x00;
      ASSR=0x00;
      TCCR2=0x00;
      TCNT2=0x00;
      OCR2=0x00;
      TIMSK=0x00;
      UCSRB=0x00;
      ACSR=0x80;
      SFIOR=0x00;
      ADCSRA=0x00;
      SPCR=0x00;
      TWCR=0x00;
      Lcd_Init();
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Cmd(_LCD_CURSOR_OFF);
      ADC_Init();
      delay_ms(100);
      LCD_Out(1, 1, "AVR Lux Meter");
      LCD_Out(2, 1, "Lux: ");
}


unsigned int filter_adc()
{
         register float adc_value=0;
         register unsigned long tmp_value=0;
         unsigned int sample=0;
         
         while(sample<no_of_samples)
         {
                         adc_value=(adc_read(0));
                         tmp_value=(tmp_value+((unsigned long)(adc_value*adc_value)));
                         delay_us(20);
                         sample++;
         }
         
         adc_value=(tmp_value/no_of_samples);
         tmp_value=(sqrt(adc_value));
         return tmp_value;
}