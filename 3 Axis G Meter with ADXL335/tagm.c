#define cal       PIND0_bit
#define disp      PIND1_bit

#define dly       4000


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
void lcd_show_value(unsigned char x, unsigned char y, float value);
unsigned int adc_avg(unsigned char channel);
void get_raw_data(unsigned int *x_axis, unsigned int *y_axis, unsigned int *z_axis);
float map(float v, float x_min, float x_max, float y_min, float y_max);


void main() 
{
     unsigned char s = 0;
     
     unsigned int raw_x = 0;
     unsigned int raw_y = 0;
     unsigned int raw_z = 0;
     
     unsigned int raw_x_max = 590;
     unsigned int raw_x_min = 370;
     unsigned int raw_y_max = 590;
     unsigned int raw_y_min = 370;
     unsigned int raw_z_max = 590;
     unsigned int raw_z_min = 370;
     
     float x_value = 0.0;
     float y_value = 0.0;
     float z_value = 0.0;
     float r_value = 0.0;
     
     setup();
     
     while(1)
     {
         if(cal)
         {
             delay_ms(40);
             while(cal);
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 5, "Calibration");
             LCD_Out(3, 9, "Mode");
             delay_ms(dly);
             
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 4, "Leave on Rest");
             delay_ms(dly);
             get_raw_data(&raw_x, &raw_y, &raw_z);
             raw_z_max = raw_z;
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(3, 6, "Z Max:");
             lcd_show_value(13, 3, raw_z_max);
             delay_ms(dly);

             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 3, "Tilt Upside Down");
             delay_ms(dly);
             get_raw_data(&raw_x, &raw_y, &raw_z);
             raw_z_min = raw_z;
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(3, 6, "Z Min:");
             lcd_show_value(13, 3, raw_z_min);
             delay_ms(dly);
             
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 6, "Tilt Back");
             delay_ms(dly);
             get_raw_data(&raw_x, &raw_y, &raw_z);
             raw_y_max = raw_y;
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(3, 6, "Y Max:");
             lcd_show_value(13, 3, raw_y_max);
             delay_ms(dly);

             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 6, "Tilt Front");
             delay_ms(dly);
             get_raw_data(&raw_x, &raw_y, &raw_z);
             raw_y_min = raw_y;
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(3, 6, "Y Min:");
             lcd_show_value(13, 3, raw_y_min);
             delay_ms(dly);
             
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 6, "Tilt Right");
             delay_ms(dly);
             get_raw_data(&raw_x, &raw_y, &raw_z);
             raw_x_max = raw_x;
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(3, 6, "X Max:");
             lcd_show_value(13, 3, raw_x_max);
             delay_ms(dly);
             
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 6, "Tilt Left");
             delay_ms(dly);
             get_raw_data(&raw_x, &raw_y, &raw_z);
             raw_x_min = raw_x;
             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(3, 6, "X Min:");
             lcd_show_value(13, 3, raw_x_min);
             delay_ms(dly);

             LCD_Cmd(_LCD_CLEAR);
             LCD_Out(2, 5, "Calibration");
             LCD_Out(3, 7, "Complete");
             delay_ms(dly);
             LCD_Cmd(_LCD_CLEAR);
         }
         else
         {
             if(disp)
             {
                 delay_ms(40);
                 while(disp);
                 LCD_Cmd(_LCD_CLEAR);
                 s += 1;
             }
             if(s > 3)
             {
                 s = 0;
             }
             
             get_raw_data(&raw_x, &raw_y, &raw_z);

             LCD_Out(1, 1, "AVR ADXL-335 G Meter");
             LCD_Out(2, 1, "X:");
             LCD_Out(3, 1, "Y:");
             LCD_Out(4, 1, "Z:");

             x_value = map(raw_x, raw_x_min, raw_x_max, -9.9, 9.9);
             y_value = map(raw_y, raw_y_min, raw_y_max, -9.9, 9.9);
             z_value = map(raw_z, raw_z_min, raw_z_max, -9.9, 9.9);

             r_value = ((x_value * x_value) + (y_value  * y_value) + (z_value * z_value));
             r_value = sqrt(r_value);
             
             switch(s)
             {
                 case 1:
                 {
                     lcd_show_value(5, 2, x_value);
                     lcd_show_value(5, 3, y_value);
                     lcd_show_value(5, 4, z_value);
                     lcd_show_value(15, 3, r_value);
                     
                     LCD_Out(2, 15, "RES:");
                     LCD_Out(4, 15, "m/s2");
                     break;
                 }
                 case 2:
                 {
                     x_value = map(x_value, -9.9, 9.9, -1.0, 1.0);
                     y_value = map(y_value, -9.9, 9.9, -1.0, 1.0);
                     z_value = map(z_value, -9.9, 9.9, -1.0, 1.0);
                     r_value = map(r_value, -9.9, 9.9, -1.0, 1.0);
                      
                     lcd_show_value(5, 2, x_value);
                     lcd_show_value(5, 3, y_value);
                     lcd_show_value(5, 4, z_value);
                     lcd_show_value(15, 3, r_value);
                     
                     LCD_Out(2, 15, "RES:");
                     LCD_Out(3, 20, "g");
                     break;
                 }
                 case 3:
                 {
                     x_value = map(x_value, -9.9, 9.9, -90.0, 90.0);
                     y_value = map(y_value, -9.9, 9.9, -90.0, 90.0);
                     z_value = map(z_value, -9.9, 9.9, -90.0, 90.0);
                     r_value = map(r_value, -9.9, 9.9, -90.0, 90.0);

                     lcd_show_value(5, 2, x_value);
                     lcd_show_value(5, 3, y_value);
                     lcd_show_value(5, 4, z_value);
                     lcd_show_value(15, 3, r_value);
                     
                     LCD_Out(2, 15, "RES:");
                     LCD_Out(4, 15, "Degree");
                     break;
                 }
                 default:
                 {
                     lcd_show_value(5, 2, raw_x);
                     lcd_show_value(5, 3, raw_y);
                     lcd_show_value(5, 4, raw_z);
                     break;
                 }
                 
             }
             delay_ms(100);
         }
     }
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
    ADC_Init();
    LCD_init();
    LCD_Cmd(_LCD_CLEAR);
    LCD_Cmd(_LCD_CURSOR_OFF);
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


unsigned int adc_avg(unsigned char channel)
{
    unsigned char samples = 0;
    register unsigned int avg = 0;
    while(samples < 64)
    {
        avg += adc_read(channel);
        delay_us(10);
        samples += 1;
    }
    avg >>= 6;
    return avg;
}


void get_raw_data(unsigned int *x_axis, unsigned int *y_axis, unsigned int *z_axis)
{
    *x_axis = adc_avg(0);
    *y_axis = adc_avg(1);
    *z_axis = adc_avg(2);
}


float map(float v, float x_min, float x_max, float y_min, float y_max)
{
    register float m = 0.0;
    m = ((y_max - y_min)/(x_max - x_min));
    return (y_min + (m * (v - x_min)));
}