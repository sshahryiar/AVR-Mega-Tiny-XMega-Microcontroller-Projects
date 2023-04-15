#include "background_art.c"


#define dly              1000


char GLCD_DataPort at PORTD;
char GLCD_DataPort_Direction at DDRD;

sbit GLCD_CS1 at PORTC6_bit;
sbit GLCD_CS2 at PORTC5_bit;
sbit GLCD_RS  at PORTC0_bit;
sbit GLCD_RW  at PORTC1_bit;
sbit GLCD_EN  at PORTC2_bit;
sbit GLCD_RST at PORTC7_bit;

sbit GLCD_CS1_Direction at DDC6_bit;
sbit GLCD_CS2_Direction at DDC5_bit;
sbit GLCD_RS_Direction  at DDC0_bit;
sbit GLCD_RW_Direction  at DDC1_bit;
sbit GLCD_EN_Direction  at DDC2_bit;
sbit GLCD_RST_Direction at DDC7_bit;


void main()
{
     Glcd_Init();
     Glcd_Fill(0x00);
     for(;;)
     {
             Glcd_Fill(0x00);
             Glcd_Image(logo1);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo2);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo3);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo4);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo5);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo6);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo7);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo8);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo9);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo10);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo11);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo12);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo13);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo14);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo15);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo16);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo17);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo18);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo19);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo20);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo21);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo22);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo23);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo24);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo25);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo26);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo27);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo28);
             delay_ms(dly);
             Glcd_Fill(0x00);
             Glcd_Image(logo29);
             delay_ms(dly);
     };
}