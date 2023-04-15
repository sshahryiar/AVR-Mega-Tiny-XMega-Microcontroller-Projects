#include "background_art.c"


#define toggle             PINC0_bit
#define move_left          PINC1_bit
#define move_right         PINC2_bit
#define move_on            PINC3_bit


char GLCD_DataPort at PORTD;
char GLCD_DataPort_Direction at DDRD;

sbit GLCD_CS2 at PORTB0_bit;
sbit GLCD_CS1 at PORTB1_bit;
sbit GLCD_RST at PORTB2_bit;
sbit GLCD_RS  at PORTB5_bit;
sbit GLCD_RW  at PORTB6_bit;
sbit GLCD_EN  at PORTB7_bit;

sbit GLCD_CS2_Direction at DDB0_bit;
sbit GLCD_CS1_Direction at DDB1_bit;
sbit GLCD_RST_Direction at DDB2_bit;
sbit GLCD_RS_Direction  at DDB5_bit;
sbit GLCD_RW_Direction  at DDB6_bit;
sbit GLCD_EN_Direction  at DDB7_bit;


void setup();
unsigned short get_input();
unsigned short type_select();
void make_number();
unsigned long pow(unsigned char val);


void main() 
{
     bit num_type;
     setup();
     do
     {
                 Glcd_Image(artwork);
                 make_number();
     }while(1);
}


void setup()
{
      Glcd_Init();
      Glcd_Fill(0x00);
      CLKPR=0x80;
      CLKPR=0x00;
      DDRC=0x10;
      PORTC=0x00;
      TCCR0A=0x00;
      TCCR0B=0x00;
      TCNT0=0x00;
      OCR0A=0x00;
      OCR0B=0x00;
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
      TCCR2A=0x00;
      TCCR2B=0x00;
      TCNT2=0x00;
      OCR2A=0x00;
      OCR2B=0x00;
      EICRA=0x00;
      EIMSK=0x00;
      PCICR=0x00;
      TIMSK0=0x00;
      TIMSK1=0x00;
      TIMSK2=0x00;
      ACSR=0x80;
      ADCSRB=0x00;
      Sound_Init(&PORTC,4);
      delay_ms(100);
}


unsigned short get_input()
{
         if(toggle)
         {
                   Sound_Play(800,25);
                   return 1;
         }
         else if(move_left)
         {
                   Sound_Play(2500,25);
                   return 2;
         }
         else if(move_right)
         {
                   Sound_Play(1500,25);
                   return 3;
         }
         else if(move_on)
         {
                   Sound_Play(1000,25);
                   return 4;
         }
         else
         {
             return 0;
         }
}


void make_number()
{
     bit dir;
     unsigned char LIH_ptr[15];
     unsigned char dec_ptr[15];
     signed short pos=0;
     unsigned short ps=0;
     unsigned long num=0;
     unsigned short tmp=0;
     unsigned long b[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     dir=1;
     WordToHex(num, LIH_ptr);
     Glcd_Write_Text(LIH_ptr, 90, 3, 1);
     WordToStrWithZeros(num, dec_ptr);
     Glcd_Write_Text(dec_ptr, 85, 5, 1);
     while(1)
     {
           if(get_input()==2)
           {
                             pos++;
                             dir=1;
           }
           if(get_input()==3)
           {
                             pos--;

                             dir=0;
           }
           if(pos>15)
           {
                     pos=0;
           }
           if(pos<0)
           {
                     pos=15;
           }
           if(get_input()==1)
           {
                             b[pos]=(b[pos]&0x01);
                             b[pos]^=1;
                             Glcd_Box(tmp, 5, (tmp+3), 9, b[pos]);
                             num=0;
                             for(ps=0;ps<16;ps++)
                             {
                                 b[ps]=(b[ps]&0x01);
                                 num+=(pow(ps)*(b[ps]));
                                 tmp=(4+(7*(15-ps)));
                                 Glcd_Box(tmp, 5, (tmp+3), 9, b[ps]);
                             }
                             WordToHex(num, LIH_ptr);
                             Glcd_Write_Text(LIH_ptr, 90, 3, 1);

                             WordToStrWithZeros(num, dec_ptr);
                             Glcd_Write_Text(dec_ptr, 85, 5, 1);
                             if(dir)
                             {
                                    pos++;
                             }
                             else
                             {
                                    pos--;
                             }
           }
           
           if(get_input()==4)
           {
               break;
           }
           
           for(ps=0;ps<16;ps++)
           {
               num=0;
               b[ps]=(b[ps]&0x01);
               num+=(pow(ps)*(b[ps]));
               tmp=(4+(7*(15-ps)));
               Glcd_Box(tmp, 5, (tmp+3), 9, b[ps]);
           }

           tmp=(4+(7*(15-(unsigned char)pos)));
           Glcd_Box(tmp, 5, (tmp+3), 9, 1);
           delay_ms(100);
           Glcd_Box(tmp, 5, (tmp+3), 9, 0);
           delay_ms(100);
     }
}


unsigned long pow(unsigned char val)
{
         unsigned char cnt=0;
         unsigned long temp=1;
         for(cnt=0;cnt<val;cnt++)
         {
             temp<<=1;
         }
         return temp;
}