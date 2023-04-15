#include "background_arts.h"


#define input               0
#define supply              1

#define v_const             0.048876


char GLCD_DataPort at PORTD;
char GLCD_DataPort_Direction at DDRD;


sbit GLCD_CS1 at PORTB1_bit;
sbit GLCD_CS2 at PORTB0_bit;
sbit GLCD_RST at PORTB2_bit;
sbit GLCD_RS  at PORTB5_bit;
sbit GLCD_RW  at PORTB6_bit;
sbit GLCD_EN  at PORTB7_bit;

sbit GLCD_CS1_Direction at DDB1_bit;
sbit GLCD_CS2_Direction at DDB0_bit;
sbit GLCD_RS_Direction  at DDB5_bit;
sbit GLCD_RW_Direction  at DDB6_bit;
sbit GLCD_EN_Direction  at DDB7_bit;
sbit GLCD_RST_Direction at DDB2_bit;


float Vs=0.0;
float VHmax=0.0;
float VHmin=0.0;
float VLmax=0.0;
float VLmin=0.0;
float Vin=0.0;
unsigned int present_adc=0;
unsigned int previous_adc=0;

unsigned char Vs_ptr[15];
unsigned char VHmax_ptr[15];
unsigned char VHmin_ptr[15];
unsigned char VLmax_ptr[15];
unsigned char VLmin_ptr[15];
unsigned char Vin_ptr[15];


void setup();
unsigned int adc_avg(unsigned short channel);
unsigned short read_supply_voltage();
void load_strategy_and_measure(unsigned short s);
void CMOS_logic();
void TTL_logic();
void check_logic();


void main() 
{
     bit strategy;
     setup();
     strategy=read_supply_voltage();
     while(1)
     {
          load_strategy_and_measure(strategy);
     };
}


void setup()
{
     Glcd_Init();
     Glcd_Fill(0);
     adc_init();
     delay_ms(20);
}


unsigned int adc_avg(unsigned short channel)
{
         register unsigned int avg=0;
         unsigned short samples=0;
         while(samples<64)
         {
             avg+=adc_read(channel);
             delay_us(20);
             samples++;
         }
         avg>>=6;
         return avg;
}


unsigned short read_supply_voltage()
{
         Vs+=(v_const*adc_avg(supply));
         delay_ms(50);
         if((vs>=5.6) && (vs<=16.0))
         {
                 GLCD_image(CMOS);
                 CMOS_logic();
                 return 1;
         }
         else if((vs<5.6) && (vs>4.5))
         {
                 GLCD_image(TTL);
                 TTL_logic();
                 return 0;
         }
         else
         {
                while(1)
                {
                    Glcd_Write_Text("Abnormal", 40, 3, 1);
                    Glcd_Write_Text("Voltage Level!", 24, 4, 1);
                    Glcd_Write_Text("Reboot System.", 24, 5, 1);
                }
         }
}


void load_strategy_and_measure(unsigned short s)
{
     check_logic();
     switch(s)
     {
              case 1:
              {
                   floatToStr(Vin, Vin_ptr);
                   Glcd_Write_Text(Vin_ptr, 99, 6, 0);
                   break;
              }
              default:
              {
                   floatToStr(Vin, Vin_ptr);
                   Glcd_Write_Text(Vin_ptr, 80, 4, 0);
                   break;
              }
     }
}


void CMOS_logic()
{
     VHmax=Vs;
     VHmin=((Vs*2.0)/3.0);
     VLmax=((Vs*1.0)/3.0);
     VLmin=0.0;
     floatToStr(Vs, Vs_ptr);
     Glcd_Write_Text(VS_ptr, 99, 1, 0);
     floatToStr(VHmin, VHmin_ptr);
     Glcd_Write_Text(VHmin_ptr, 99, 2, 0);
     floatToStr(VHmax, VHmax_ptr);
     Glcd_Write_Text(VHmax_ptr, 99, 3, 0);
     floatToStr(VLmin, VLmin_ptr);
     Glcd_Write_Text(VLmin_ptr, 99, 4, 0);
     floatToStr(VLmax, VLmax_ptr);
     Glcd_Write_Text(VLmax_ptr, 99, 5, 0);
}


void TTL_logic()
{
     VHmax=Vs;
     VHmin=2.5;
     VLmax=0.8;
     VLmin=0.0;
}


void check_logic()
{
     present_adc=adc_avg(input);
     Vin=(v_const*present_adc);
     if(Vin>Vs)
     {
               Vin=Vs;
     }
     if(present_adc!=previous_adc)
     {
         Glcd_box(6,6,16,56,1);
         Glcd_box(6,(62-(56*(Vin/Vs))),16,56,0);
         if(Vin>=VLmin && Vin<=VLmax)
         {
             Glcd_rectangle(50,10,59,24,1);
             Glcd_rectangle(50,46,59,60,0);
             Glcd_rectangle(50,28,59,42,1);
         }
         if(Vin>=VHmin && Vin<=VHmax)
         {
             Glcd_rectangle(50,46,59,60,1);
             Glcd_rectangle(50,10,59,24,0);
             Glcd_rectangle(50,28,59,42,1);
         }
         if(Vin>VLmax && Vin<VHmin)
         {
             Glcd_rectangle(50,46,59,60,1);
             Glcd_rectangle(50,28,59,42,0);
             Glcd_rectangle(50,10,59,24,1);
         }
     }
     previous_adc=present_adc;
}