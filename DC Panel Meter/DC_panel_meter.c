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


unsigned long adc_avg(unsigned int channel);
void volt_display_digits(unsigned short x, unsigned short y, long value);
void current_display_digits(unsigned short x, unsigned short y, long value);


void main()
{
  float tmp=0;
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  while(1)
  {
       tmp=adc_avg(0);
       tmp = (((tmp*3.0)/1.023));
       lcd_out(1,1,"Voltage: ");
       volt_display_digits(10,1,tmp);
       lcd_out(1,16,"V");
       tmp=adc_avg(1);
       tmp = (tmp*4.88);
       lcd_out(2,1,"Current: ");
       current_display_digits(10,2,tmp);
       lcd_out(2,16,"A");
       delay_ms(99);
  }
}


 unsigned long adc_avg(unsigned int channel)
 {
   unsigned long avg = 0;
   unsigned short s = 0;
   for(s=0;s<16;s++)
   {
       avg+=adc_read(channel);
       delay_us(99);
   }
   avg = avg >> 4;
   return avg;
 }
 
 
void volt_display_digits(unsigned short x, unsigned short y, long value)
{
    unsigned char temp = 0;
    temp = ((value/1000)+48);
    Lcd_Chr(y,x,temp);
    temp = (((value/100)%10)+48);
    Lcd_Chr(y,(x+1),temp);
    Lcd_Chr(y,(x+2),46);
    temp = (((value/10)%10)+48);
    Lcd_Chr(y,(x+3),temp);
    temp = ((value%10)+48);
    Lcd_Chr(y,(x+4),temp);
}


void current_display_digits(unsigned short x, unsigned short y, long value)
 {
    unsigned char temp = 0;
    temp = ((value/1000)+48);
    Lcd_Chr(y,x,temp);
    Lcd_Chr(y,(x+1),46);
    temp = (((value/100)%10)+48);
    Lcd_Chr(y,(x+2),temp);
    temp = (((value/10)%10)+48);
    Lcd_Chr(y,(x+3),temp);
    temp = ((value%10)+48);
    Lcd_Chr(y,(x+4),temp);
}
