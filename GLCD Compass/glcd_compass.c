#include "background.c"
#include "HMC5883L.c"


#define scale_factor1             23
#define scale_factor2              4

#define pi               3.141592654
#define pi_by_2          1.570796327


sbit GLCD_RS  at PORTB2_bit;
sbit GLCD_RW  at PORTB3_bit;
sbit GLCD_EN  at PORTB4_bit;
sbit GLCD_CS2 at PORTB5_bit;
sbit GLCD_CS1 at PORTB6_bit;
sbit GLCD_RST at PORTB7_bit;

sbit GLCD_RS_Direction  at DDB2_bit;
sbit GLCD_RW_Direction  at DDB3_bit;
sbit GLCD_EN_Direction  at DDB4_bit;
sbit GLCD_CS2_Direction at DDB5_bit;
sbit GLCD_CS1_Direction at DDB6_bit;
sbit GLCD_RST_Direction at DDB7_bit;

unsigned char GLCD_DataPort at PORTD;
unsigned char GLCD_DataPort_Direction at DDRD;


void setup();


void main()
{

     signed char v1 = 0;
     signed char h1 = 0;
     signed char v2 = 0;
     signed char h2 = 0;
     
     unsigned char heading_text[6];
     
     float heading_new = 0;
     float heading_old = 0;

     setup();
     while(1)
     {
             heading_new = HMC5883L_heading();
             IntToStr(((unsigned int)heading_new), heading_text);
             Glcd_Write_Text(heading_text, 70, 5, 1);
             
             heading_new *= 0.0174532925;
             
             if(heading_new != heading_old)
             {
                 v1 = scale_factor1 * sin(heading_old);
                 h1 = scale_factor1 * cos(heading_old);
                 Glcd_Line(31, 31, (31 + h1), (31 + v1), 0);
                 v2 = scale_factor2 * sin(heading_old - pi_by_2);
                 h2 = scale_factor2 * cos(heading_old - pi_by_2);
                 Glcd_Line(31, 31, (31 + h2), (31 + v2), 0);
                 Glcd_Line(31, 31, (31 - h2), (31 - v2), 0);
                 
                 Glcd_Line((31 + h1), (31 + v1), (31 + h2), (31 + v2),  0);
                 Glcd_Line((31 - h1), (31 - v1), (31 + h2), (31 + v2),  0);
                 Glcd_Line((31 + h1), (31 + v1), (31 - h2), (31 - v2),  0);
                 Glcd_Line((31 - h1), (31 - v1), (31 - h2), (31 - v2),  0);

                 v1 = scale_factor1 * sin(heading_new);
                 h1 = scale_factor1 * cos(heading_new);
                 Glcd_Line(31, 31, (31 + h1), (31 + v1), 1);

                 v2 = scale_factor2 * sin(heading_new - pi_by_2);
                 h2 = scale_factor2 * cos(heading_new - pi_by_2);
                 Glcd_Line(31, 31, (31 + h2), (31 + v2), 1);
                 Glcd_Line(31, 31, (31 - h2), (31 - v2), 1);
                 
                 Glcd_Line((31 + h1), (31 + v1), (31 + h2), (31 + v2),  1);
                 Glcd_Line((31 - h1), (31 - v1), (31 + h2), (31 + v2),  1);
                 Glcd_Line((31 + h1), (31 + v1), (31 - h2), (31 - v2),  1);
                 Glcd_Line((31 - h1), (31 - v1), (31 - h2), (31 - v2),  1);
                 
                 Glcd_Circle_Fill(31, 31, 3, 1);
                 heading_old = heading_new;
             }
             
             delay_ms(400);
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
     DDRD = 0x00;
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
     ACSR = 0x80;
     ADCSRB = 0x00;
     DIDR1 = 0x00;
     ADCSRA = 0x00;
     SPCR = 0x00;
     TWCR = 0x00;
     glcd_init();
     glcd_fill(0x00);
     Glcd_Image(background);
     Glcd_Write_Text("Heading", 80, 3, 1);
     Glcd_Write_Text("'N", 105, 5, 1);
     HMC5883L_init();
}
