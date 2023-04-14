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


unsigned char msg[] = "Temperature:";
unsigned char *text1 = "00.0'C";


void setup();
float adc_rms();
void disp1(unsigned long v);
void disp2(unsigned long v);


void main()
{
     rx float t=0;
     setup();
     Lcd_Out(1,1,msg);
     while(1)
     {
             t=adc_rms();
             disp1(t);
     };
}


void setup()
{
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     ADC_Init();
     delay_ms(200);
}


float adc_rms()
{
         register unsigned long temp=0;
         unsigned int samples=0;
         register float rms=0;
         while(samples<2048)
         {
             rms=adc_read(0);
             temp+=((unsigned long)(rms*rms));
             delay_us(10);
             samples++;
         }
         temp>>=11;
         rms=((sqrt(temp)));
}


void disp1(unsigned long v)
{
     text1[0] = v/100 + 48;
     text1[1] = (v/10)%10 + 48;
     text1[3] = (v%10) + 48;
     Lcd_Out(2,1,text1);
}