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


void setup();
float adc_rms();
void display_value(unsigned char x, unsigned char y, unsigned long value);


void main() 
{
     unsigned char text[15];
     unsigned char s = 0;
     unsigned char mux_state = 0x03;
     register float v = 0.0;
     memset(text, 0x00, sizeof(text));
     
     setup();
     
     Lcd_Out(1, 1, "Voltage:");
     Lcd_Out(2, 1, "Range:");
     
     while(1)
     {
             v = adc_rms();

             if(v > 585)
             {
                 mux_state += 1;
             }
             if((v < 290) && (mux_state > 0))
             {
                 mux_state -= 1;
             }
             
             if(mux_state >= 3)
             {
                 mux_state = 3;
             }
             if(mux_state < 1)
             {
                 mux_state = 0;
             }

             switch(mux_state)
             {
                 case 1:
                 {
                     PORTD = 0x01;
                     v *= 0.012931;
                     v -= 0.028542;
                     Lcd_Out(2, 8, "3.75-7.5V ");
                     break;
                 }
                 case 2:
                 {
                     PORTD = 0x02;
                     v *= 0.02586;
                     v -= 0.05052;
                     Lcd_Out(2, 8, "7.5-15.0V");
                     break;
                 }
                 case 3:
                 {
                     PORTD = 0x03;
                     v *= 0.051724;
                     v -= 0.10344;
                     Lcd_Out(2, 8, "15-30V   ");
                     break;
                 }
                 default:
                 {
                     PORTD = 0x00;
                     v *= 0.006443;
                     Lcd_Out(2, 8, "0.0-3.75V");
                     break;
                 }
             }
             if((v >= 0.0) && (v <= 30.0))
             {
                 display_value(10, 1, (v * 1000.0));
             }
             else
             {
                 Lcd_Out(1, 10, "--.---");
             }
             delay_ms(100);
     };
}


void setup()
{
     DDRB = 0x00;
     DDRC = 0x00;
     DDRD = 0x03;
     PORTB = 0x00;
     PORTC = 0x00;
     PORTD = 0x03;
     TCCR0 = 0x00;
     TCNT0 = 0x00;
     TCCR1A = 0x00;
     TCCR1B = 0x00;
     TCNT1H = 0x00;
     TCNT1L = 0x00;
     TCCR2 = 0x00;
     TCNT2 = 0x00;
     OCR1AH = 0x00;
     OCR1AL = 0x00;
     OCR1BH = 0x00;
     OCR1BL = 0x00;
     OCR2 = 0x00;
     ICR1H = 0x00;
     ICR1L = 0x00;
     ASSR = 0x00;
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
     ADC_Init();
}


float adc_rms()
{
     unsigned int samples = 512;
     register unsigned long temp = 0;
     register float rms = 0.0;
     
     while(samples > 0)
     {
         rms = adc_read(0);
         temp += ((unsigned long)(rms * rms));
         delay_us(6);
         samples -= 1;
     }
     rms = (temp >> 9);
     rms = (sqrt(rms));
     return rms;
}


void display_value(unsigned char x, unsigned char y, unsigned long value)
{
    unsigned char temp = 0;
    temp = ((value / 10000) + 48);
    Lcd_Chr(y, x, temp);
    temp = (((value / 1000) % 10) + 48);
    Lcd_Chr(y,(x + 1), temp);
    Lcd_Chr(y,(x + 2), 46);
    temp = (((value/100) % 10) + 48);
    Lcd_Chr(y, (x + 3), temp);
    temp = (((value / 10) % 10) + 48);
    Lcd_Chr(y, (x + 4), temp);
    temp = ((value % 10) + 48);
    Lcd_Chr(y, (x + 5), temp);
    Lcd_Out(y, (x + 6), "V");
}