#include "MMA7455L.c"


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

signed char x_axis_present = 0;
signed char y_axis_present = 0;
signed char x_axis_previous = 30;
signed char y_axis_previous = 30;

unsigned char x_axis_text[6];
unsigned char y_axis_text[6];


void setup();
float map(float v, float x_min, float x_max, float y_min, float y_max);
float constrain(float value, float value_min, float value_max);


void main() 
{
     setup();
     offset_calibration();
     while(1)
     {
             read_and_compensate();
             x_axis_present = x_axis;
             y_axis_present = y_axis;
             x_axis_present = map(x_axis_present, -127, 127, 5, 59);
             y_axis_present = map(y_axis_present, -127, 127, 5, 59);
             x_axis_present = constrain(x_axis_present, 5, 59);
             y_axis_present = constrain(y_axis_present, 5, 59);
             if((x_axis_present != x_axis_previous) || (y_axis_present != y_axis_previous))
             {
                                Glcd_Circle_Fill(x_axis_previous, y_axis_previous, 3, 0);
                                Glcd_Circle_Fill(x_axis_present, y_axis_present, 3, 1);
                                
                                ShortToStr(x_axis, x_axis_text);
                                Glcd_Write_Text(x_axis_text, 70, 3, 1);
                                ShortToStr(y_axis, y_axis_text);
                                Glcd_Write_Text(y_axis_text, 70, 6, 1);
                                
                                x_axis_previous = x_axis_present;
                                y_axis_previous = y_axis_present;
             }
     };
}


void setup()
{
     Soft_I2C_Init();
     glcd_init();
     glcd_fill(0x00);
     glcd_rectangle(1, 1, 62, 62, 1);
     Glcd_Write_Text("Raw Data", 70, 0, 1);
     Glcd_Write_Text("X-Axis: ", 70, 2, 1);
     Glcd_Write_Text("Y-Axis: ", 70, 5, 1);
     memset(x_axis_text, 0x00, sizeof(x_axis_text));
     memset(y_axis_text, 0x00, sizeof(y_axis_text));
     init_MMA7455L(2);
}


float map(float v, float x_min, float x_max, float y_min, float y_max)
{
    double m = 0.0;
    m = ((y_max - y_min)/(x_max - x_min));
    return (y_min + (m * (v - x_min)));
}


float constrain(float value, float value_min, float value_max)
{
      if(value >= value_max)
      {
           return value_max;
      }
      else if(value <= value_min)
      {
           return value_min;
      }
      else
      {
           return value;
      }
}