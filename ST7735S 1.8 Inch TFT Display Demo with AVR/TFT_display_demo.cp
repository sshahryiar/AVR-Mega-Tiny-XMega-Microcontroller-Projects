#line 1 "C:/Users/Shawon/Desktop/ST7735S TFT LCD Demo/TFT_display_demo.c"
#line 1 "c:/users/shawon/desktop/st7735s tft lcd demo/st7735.c"
#line 1 "c:/users/shawon/desktop/st7735s tft lcd demo/st7735.h"
#line 1 "c:/users/shawon/desktop/st7735s tft lcd demo/font.c"
static const unsigned char font[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00}
 ,{0x00, 0x00, 0x5f, 0x00, 0x00}
 ,{0x00, 0x07, 0x00, 0x07, 0x00}
 ,{0x14, 0x7f, 0x14, 0x7f, 0x14}
 ,{0x24, 0x2a, 0x7f, 0x2a, 0x12}
 ,{0x23, 0x13, 0x08, 0x64, 0x62}
 ,{0x36, 0x49, 0x55, 0x22, 0x50}
 ,{0x00, 0x05, 0x03, 0x00, 0x00}
 ,{0x00, 0x1c, 0x22, 0x41, 0x00}
 ,{0x00, 0x41, 0x22, 0x1c, 0x00}
 ,{0x14, 0x08, 0x3e, 0x08, 0x14}
 ,{0x08, 0x08, 0x3e, 0x08, 0x08}
 ,{0x00, 0x50, 0x30, 0x00, 0x00}
 ,{0x08, 0x08, 0x08, 0x08, 0x08}
 ,{0x00, 0x60, 0x60, 0x00, 0x00}
 ,{0x20, 0x10, 0x08, 0x04, 0x02}
 ,{0x3e, 0x51, 0x49, 0x45, 0x3e}
 ,{0x00, 0x42, 0x7f, 0x40, 0x00}
 ,{0x42, 0x61, 0x51, 0x49, 0x46}
 ,{0x21, 0x41, 0x45, 0x4b, 0x31}
 ,{0x18, 0x14, 0x12, 0x7f, 0x10}
 ,{0x27, 0x45, 0x45, 0x45, 0x39}
 ,{0x3c, 0x4a, 0x49, 0x49, 0x30}
 ,{0x01, 0x71, 0x09, 0x05, 0x03}
 ,{0x36, 0x49, 0x49, 0x49, 0x36}
 ,{0x06, 0x49, 0x49, 0x29, 0x1e}
 ,{0x00, 0x36, 0x36, 0x00, 0x00}
 ,{0x00, 0x56, 0x36, 0x00, 0x00}
 ,{0x08, 0x14, 0x22, 0x41, 0x00}
 ,{0x14, 0x14, 0x14, 0x14, 0x14}
 ,{0x00, 0x41, 0x22, 0x14, 0x08}
 ,{0x02, 0x01, 0x51, 0x09, 0x06}
 ,{0x32, 0x49, 0x79, 0x41, 0x3e}
 ,{0x7e, 0x11, 0x11, 0x11, 0x7e}
 ,{0x7f, 0x49, 0x49, 0x49, 0x36}
 ,{0x3e, 0x41, 0x41, 0x41, 0x22}
 ,{0x7f, 0x41, 0x41, 0x22, 0x1c}
 ,{0x7f, 0x49, 0x49, 0x49, 0x41}
 ,{0x7f, 0x09, 0x09, 0x09, 0x01}
 ,{0x3e, 0x41, 0x49, 0x49, 0x7a}
 ,{0x7f, 0x08, 0x08, 0x08, 0x7f}
 ,{0x00, 0x41, 0x7f, 0x41, 0x00}
 ,{0x20, 0x40, 0x41, 0x3f, 0x01}
 ,{0x7f, 0x08, 0x14, 0x22, 0x41}
 ,{0x7f, 0x40, 0x40, 0x40, 0x40}
 ,{0x7f, 0x02, 0x0c, 0x02, 0x7f}
 ,{0x7f, 0x04, 0x08, 0x10, 0x7f}
 ,{0x3e, 0x41, 0x41, 0x41, 0x3e}
 ,{0x7f, 0x09, 0x09, 0x09, 0x06}
 ,{0x3e, 0x41, 0x51, 0x21, 0x5e}
 ,{0x7f, 0x09, 0x19, 0x29, 0x46}
 ,{0x46, 0x49, 0x49, 0x49, 0x31}
 ,{0x01, 0x01, 0x7f, 0x01, 0x01}
 ,{0x3f, 0x40, 0x40, 0x40, 0x3f}
 ,{0x1f, 0x20, 0x40, 0x20, 0x1f}
 ,{0x3f, 0x40, 0x38, 0x40, 0x3f}
 ,{0x63, 0x14, 0x08, 0x14, 0x63}
 ,{0x07, 0x08, 0x70, 0x08, 0x07}
 ,{0x61, 0x51, 0x49, 0x45, 0x43}
 ,{0x00, 0x7f, 0x41, 0x41, 0x00}
 ,{0x02, 0x04, 0x08, 0x10, 0x20}
 ,{0x00, 0x41, 0x41, 0x7f, 0x00}
 ,{0x04, 0x02, 0x01, 0x02, 0x04}
 ,{0x40, 0x40, 0x40, 0x40, 0x40}
 ,{0x00, 0x01, 0x02, 0x04, 0x00}
 ,{0x20, 0x54, 0x54, 0x54, 0x78}
 ,{0x7f, 0x48, 0x44, 0x44, 0x38}
 ,{0x38, 0x44, 0x44, 0x44, 0x20}
 ,{0x38, 0x44, 0x44, 0x48, 0x7f}
 ,{0x38, 0x54, 0x54, 0x54, 0x18}
 ,{0x08, 0x7e, 0x09, 0x01, 0x02}
 ,{0x0c, 0x52, 0x52, 0x52, 0x3e}
 ,{0x7f, 0x08, 0x04, 0x04, 0x78}
 ,{0x00, 0x44, 0x7d, 0x40, 0x00}
 ,{0x20, 0x40, 0x44, 0x3d, 0x00}
 ,{0x7f, 0x10, 0x28, 0x44, 0x00}
 ,{0x00, 0x41, 0x7f, 0x40, 0x00}
 ,{0x7c, 0x04, 0x18, 0x04, 0x78}
 ,{0x7c, 0x08, 0x04, 0x04, 0x78}
 ,{0x38, 0x44, 0x44, 0x44, 0x38}
 ,{0x7c, 0x14, 0x14, 0x14, 0x08}
 ,{0x08, 0x14, 0x14, 0x18, 0x7c}
 ,{0x7c, 0x08, 0x04, 0x04, 0x08}
 ,{0x48, 0x54, 0x54, 0x54, 0x20}
 ,{0x04, 0x3f, 0x44, 0x40, 0x20}
 ,{0x3c, 0x40, 0x40, 0x20, 0x7c}
 ,{0x1c, 0x20, 0x40, 0x20, 0x1c}
 ,{0x3c, 0x40, 0x30, 0x40, 0x3c}
 ,{0x44, 0x28, 0x10, 0x28, 0x44}
 ,{0x0c, 0x50, 0x50, 0x50, 0x3c}
 ,{0x44, 0x64, 0x54, 0x4c, 0x44}
 ,{0x00, 0x08, 0x36, 0x41, 0x00}
 ,{0x00, 0x00, 0x7f, 0x00, 0x00}
 ,{0x00, 0x41, 0x36, 0x08, 0x00}
 ,{0x10, 0x08, 0x08, 0x10, 0x08}
 ,{0x78, 0x46, 0x41, 0x46, 0x78}
};
#line 100 "c:/users/shawon/desktop/st7735s tft lcd demo/st7735.h"
unsigned char w =  128 ;
unsigned char l =  160 ;


void ST7735_Write(unsigned char value, unsigned char mode);
void ST7735_Reset();
void ST7735_init();
void ST7735_Word_Write(unsigned int value);
void ST7735_Data_Write(unsigned char DataH, unsigned char DataL);
void ST7735_Data_Write_4k(unsigned char DataH, unsigned char DataM, unsigned char DataL);
void Set_Addr_Window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye);
void RAM_Address_Set();
void Invert_Display(unsigned char i);
unsigned int Swap_Colour(unsigned int colour);
unsigned int Color565(unsigned char r, unsigned char g, unsigned char b);
void Set_Rotation(unsigned char m);
void TFT_fill(unsigned int colour);
void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour);
void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour);
void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour);
void Draw_Font_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour, unsigned char pixel_size);
void print_char(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch);
void print_str(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch);
void print_C(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_I(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_D(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points);
void print_F(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points);
#line 4 "c:/users/shawon/desktop/st7735s tft lcd demo/st7735.c"
void ST7735_Write(unsigned char value, unsigned char mode)
{
 signed char i = 0x08;

  PORTB0_bit  = 0;

 if(mode)
 {
  PORTB2_bit  = 1;
 }
 else
 {
  PORTB2_bit  = 0;
 }

 while(i > 0)
 {
  PORTB4_bit  = 0;

 if((value & 0x80) != 0)
 {
  PORTB3_bit  = 1;
 }
 else
 {
  PORTB3_bit  = 0;
 }

  PORTB4_bit  = 1;

 value <<= 1;
 i--;
 };

  PORTB0_bit  = 1;
}


void ST7735_Reset()
{
  PORTB1_bit  = 0;
 delay_ms(2);
  PORTB1_bit  = 1;
 delay_ms(2);
}


void ST7735_init()
{
 ST7735_Reset();

 ST7735_Write( 0x01 ,  0x0 );
 delay_us(150);
 ST7735_Write( 0x11 ,  0x0 );
 delay_us(150);

 ST7735_Write( 0xB1 ,  0x0 );
 ST7735_Write(0x01,  0x1 );
 ST7735_Write(0x2C,  0x1 );
 ST7735_Write(0x2D,  0x1 );

 ST7735_Write( 0xB2 ,  0x0 );
 ST7735_Write(0x01,  0x1 );
 ST7735_Write(0x2C,  0x1 );
 ST7735_Write(0x2D,  0x1 );

 ST7735_Write( 0xB3 ,  0x0 );
 ST7735_Write(0x01,  0x1 );
 ST7735_Write(0x2C,  0x1 );
 ST7735_Write(0x2D,  0x1 );
 ST7735_Write(0x01,  0x1 );
 ST7735_Write(0x2C,  0x1 );
 ST7735_Write(0x2D,  0x1 );

 ST7735_Write( 0xB4 ,  0x0 );
 ST7735_Write(0x07,  0x1 );

 ST7735_Write( 0xC0 ,  0x0 );
 ST7735_Write(0xA2,  0x1 );
 ST7735_Write(0x02,  0x1 );
 ST7735_Write(0x84,  0x1 );

 ST7735_Write( 0xC0 ,  0x0 );
 ST7735_Write(0xC5,  0x1 );

 ST7735_Write( 0xC1 ,  0x0 );
 ST7735_Write(0x0A,  0x1 );
 ST7735_Write(0x00,  0x1 );

 ST7735_Write( 0xC2 ,  0x0 );
 ST7735_Write(0x8A,  0x1 );
 ST7735_Write(0x2A,  0x1 );

 ST7735_Write( 0xC3 ,  0x0 );
 ST7735_Write(0x8A,  0x1 );
 ST7735_Write(0xEE,  0x1 );

 ST7735_Write( 0xC4 ,  0x0 );
 ST7735_Write(0x0E,  0x1 );

 ST7735_Write( 0xC5 ,  0x0 );
 ST7735_Write(0x00,  0x1 );

 ST7735_Write( 0x3A ,  0x0 );
 ST7735_Write(0x05,  0x1 );

 ST7735_Write( 0x36 ,  0x0 );
 ST7735_Write(0xC8,  0x1 );

 RAM_Address_Set();

 ST7735_Write( 0xE0 ,  0x0 );
 ST7735_Write(0x02,  0x1 );
 ST7735_Write(0x1C,  0x1 );
 ST7735_Write(0x07,  0x1 );
 ST7735_Write(0x12,  0x1 );
 ST7735_Write(0x37,  0x1 );
 ST7735_Write(0x32,  0x1 );
 ST7735_Write(0x29,  0x1 );
 ST7735_Write(0x2D,  0x1 );
 ST7735_Write(0x29,  0x1 );
 ST7735_Write(0x25,  0x1 );
 ST7735_Write(0x2B,  0x1 );
 ST7735_Write(0x39,  0x1 );
 ST7735_Write(0x00,  0x1 );
 ST7735_Write(0x01,  0x1 );
 ST7735_Write(0x03,  0x1 );
 ST7735_Write(0x10,  0x1 );

 ST7735_Write( 0xE1 ,  0x0 );
 ST7735_Write(0x03,  0x1 );
 ST7735_Write(0x1D,  0x1 );
 ST7735_Write(0x07,  0x1 );
 ST7735_Write(0x06,  0x1 );
 ST7735_Write(0x2E,  0x1 );
 ST7735_Write(0x2C,  0x1 );
 ST7735_Write(0x29,  0x1 );
 ST7735_Write(0x2D,  0x1 );
 ST7735_Write(0x2E,  0x1 );
 ST7735_Write(0x2E,  0x1 );
 ST7735_Write(0x37,  0x1 );
 ST7735_Write(0x3F,  0x1 );
 ST7735_Write(0x00,  0x1 );
 ST7735_Write(0x00,  0x1 );
 ST7735_Write(0x02,  0x1 );
 ST7735_Write(0x10,  0x1 );

 ST7735_Write( 0x13 ,  0x0 );
 delay_ms(10);

 ST7735_Write( 0x29 ,  0x0 );
 delay_ms(100);

 ST7735_Write( 0x2C ,  0x0 );
 delay_ms(100);
}


void ST7735_Word_Write(unsigned int value)
{
 ST7735_Write(((value & 0xFF00) >> 0x08),  0x1 );
 ST7735_Write((value & 0x00FF),  0x1 );
}


void ST7735_Data_Write(unsigned char DataH, unsigned char DataL)
{
 ST7735_Write(DataH,  0x1 );
 ST7735_Write(DataL,  0x1 );
}


void ST7735_Data_Write_4k(unsigned char DataH, unsigned char DataM, unsigned char DataL)
{
 ST7735_Write(DataH,  0x1 );
 ST7735_Write(DataM,  0x1 );
 ST7735_Write(DataL,  0x1 );
}


void Set_Addr_Window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye)
{
 ST7735_Write( 0x2A ,  0x0 );
 ST7735_Write(0x00,  0x1 );
 ST7735_Write(xs,  0x1 );
 ST7735_Write(0x00,  0x1 );
 ST7735_Write(xe,  0x1 );

 ST7735_Write( 0x2B ,  0x0 );
 ST7735_Write(0x00,  0x1 );
 ST7735_Write(ys,  0x1 );
 ST7735_Write(0x00,  0x1 );
 ST7735_Write(ye,  0x1 );

 ST7735_Write( 0x2C ,  0x0 );
}


void RAM_Address_Set()
{
 Set_Addr_Window(0x00, 0x00, 0x7F, 0x9F);
}


void Invert_Display(unsigned char i)
{
 if(i ==  0x21 )
 {
 ST7735_Write( 0x21 ,  0x0 );
 }
 else
 {
 ST7735_Write( 0x20 ,  0x0 );
 }
}


unsigned int Swap_Colour(unsigned int colour)
{
 return ((colour << 0x000B) | (colour & 0x07E0) | (colour >> 0x000B));
}


unsigned int Color565(unsigned char r, unsigned char g, unsigned char b)
{
 return (((r & 0xF8) << 0x08) | ((g & 0xFC) << 0x03) | (b >> 0x03));
}


void Set_Rotation(unsigned char m)
{
 unsigned char rotation = 0x00;

 ST7735_Write( 0x36 ,  0x0 );
 rotation = (m % 4);

 switch(rotation)
 {
 case 0:
 {
 ST7735_Write(( 0x40  |  0x80  |  0x08 ),  0x1 );
 w =  128 ;
 l =  160 ;
 break;
 }
 case 1:
 {
 ST7735_Write(( 0x80  |  0x20  |  0x08 ),  0x1 );
 w =  160 ;
 l =  128 ;
 break;
 }
 case 2:
 {
 ST7735_Write(( 0x08 ),  0x1 );
 w =  128 ;
 l =  160 ;
 break;
 }
 case 3:
 {
 ST7735_Write(( 0x40  |  0x20  |  0x08 ),  0x1 );
 w =  160 ;
 l =  128 ;
 break;
 }
 }
}


void TFT_fill(unsigned int colour)
{
 unsigned char i = 0x00;
 unsigned char j = 0x00;

 Set_Addr_Window(0, 0, (w - 1), (l - 1));

 for(j = l; j > 0; j--)
 {
 for(i = w; i > 0; i--)
 {
 ST7735_Word_Write(colour);
 }
 }
}


void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour)
{
 Set_Addr_Window(x_pos, y_pos, (1 + x_pos), (1 + y_pos));
 ST7735_Word_Write(colour);
}


void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour)
{
 signed int dx = 0x0000;
 signed int dy = 0x0000;
 signed int stepx = 0x0000;
 signed int stepy = 0x0000;
 signed int fraction = 0x0000;

 dy = (y2 - y1);
 dx = (x2 - x1);

 if (dy < 0)
 {
 dy = -dy;
 stepy = -1;
 }
 else
 {
 stepy = 1;
 }

 if (dx < 0)
 {
 dx = -dx;
 stepx = -1;
 }
 else
 {
 stepx = 1;
 }

 dx <<= 0x01;
 dy <<= 0x01;

 Draw_Pixel(x1, y1, colour);

 if (dx > dy)
 {
 fraction = (dy - (dx >> 1));
 while (x1 != x2)
 {
 if (fraction >= 0)
 {
 y1 += stepy;
 fraction -= dx;
 }
 x1 += stepx;
 fraction += dy;

 Draw_Pixel(x1, y1, colour);
 }
 }
 else
 {
 fraction = (dx - (dy >> 1));

 while (y1 != y2)
 {
 if (fraction >= 0)
 {
 x1 += stepx;
 fraction -= dy;
 }
 y1 += stepy;
 fraction += dx;
 Draw_Pixel(x1, y1, colour);
 }
 }
}


void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour)
{
 unsigned char i = 0x00;
 unsigned char xmin = 0x00;
 unsigned char xmax = 0x00;
 unsigned char ymin = 0x00;
 unsigned char ymax = 0x00;

 if(fill !=  0x00 )
 {
 if(x1 < x2)
 {
 xmin = x1;
 xmax = x2;
 }
 else
 {
 xmin = x2;
 xmax = x1;
 }

 if(y1 < y2)
 {
 ymin = y1;
 ymax = y2;
 }
 else
 {
 ymin = y2;
 ymax = y1;
 }

 for(; xmin <= xmax; ++xmin)
 {
 for(i = ymin; i <= ymax; ++i)
 {
 Draw_Pixel(xmin, i, colour);
 }
 }
 }

 else
 {
 Draw_Line(x1, y1, x2, y1, colour);
 Draw_Line(x1, y2, x2, y2, colour);
 Draw_Line(x1, y1, x1, y2, colour);
 Draw_Line(x2, y1, x2, y2, colour);
 }

 if(type !=  0x00 )
 {
 Draw_Pixel(x1, y1, back_colour);
 Draw_Pixel(x1, y2, back_colour);
 Draw_Pixel(x2, y1, back_colour);
 Draw_Pixel(x2, y2, back_colour);
 }
}


void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour)
{
 signed int a = 0x0000;
 signed int b = 0x0000;
 signed int p = 0x0000;

 b = radius;
 p = (1 - b);

 do
 {
 if(fill !=  0x00 )
 {
 Draw_Line((xc - a), (yc + b), (xc + a), (yc + b), colour);
 Draw_Line((xc - a), (yc - b), (xc + a), (yc - b), colour);
 Draw_Line((xc - b), (yc + a), (xc + b), (yc + a), colour);
 Draw_Line((xc - b), (yc - a), (xc + b), (yc - a), colour);
 }
 else
 {
 Draw_Pixel((xc + a), (yc + b), colour);
 Draw_Pixel((xc + b), (yc + a), colour);
 Draw_Pixel((xc - a), (yc + b), colour);
 Draw_Pixel((xc - b), (yc + a), colour);
 Draw_Pixel((xc + b), (yc - a), colour);
 Draw_Pixel((xc + a), (yc - b), colour);
 Draw_Pixel((xc - a), (yc - b), colour);
 Draw_Pixel((xc - b), (yc - a), colour);
 }

 if(p < 0)
 {
 p += (0x03 + (0x02 * a++));
 }
 else
 {
 p += (0x05 + (0x02 * ((a++) - (b--))));
 }
 }while(a <= b);
}


void Draw_Font_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour, unsigned char pixel_size)
{
 unsigned char i = 0x00;

 Set_Addr_Window(x_pos, y_pos, (x_pos + pixel_size - 1), (y_pos + pixel_size - 1));

 for(i = 0x00; i < (pixel_size * pixel_size); i++)
 {
 ST7735_Word_Write(colour);
 }
}


void print_char(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch)
{
 unsigned char i = 0x00;
 unsigned char j = 0x00;

 unsigned char value = 0x00;

 if(font_size < 0)
 {
 font_size = 1;
 }

 if(x_pos < font_size)
 {
 x_pos = font_size;
 }

 for (i = 0x00; i < 0x05; i++)
 {
 for (j = 0x00; j < 0x08; j++)
 {
 value = 0x00;
 value = ((font[((unsigned char)ch) - 0x20][i]));

 if((value >> j) & 0x01)
 {
 Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
 }
 else
 {
 Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
 }

 y_pos = y_pos + font_size;
 }
 y_pos -= (font_size << 0x03);
 x_pos += font_size;

 }
 x_pos += font_size;

 if(x_pos > w)
 {
 x_pos = (font_size + 0x01);
 y_pos += (font_size << 0x03);
 }
}


void print_str(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch)
{
 do
 {
 print_char(x_pos, y_pos, font_size, colour, back_colour, *ch++);
 x_pos += (font_size * 0x06);
 }while((*ch >= 0x20) && (*ch <= 0x7F));
}


void print_C(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
{
 unsigned char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

 if(value < 0x00)
 {

 ch[0] = 0x2D;
 value = -value;
 }
 else
 {
 ch[0] = 0x20;
 }

 if((value > 99) && (value <= 999))
 {
 ch[1] = ((value / 100) + 0x30);
 ch[2] = (((value % 100) / 10) + 0x30);
 ch[3] = ((value % 10) + 0x30);
 }
 else if((value > 9) && (value <= 99))
 {
 ch[1] = (((value % 100) / 10) + 0x30);
 ch[2] = ((value % 10) + 0x30);
 ch[3] = 0x20;
 }
 else if((value >= 0) && (value <= 9))
 {
 ch[1] = ((value % 10) + 0x30);
 ch[2] = 0x20;
 ch[3] = 0x20;
 }

 print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
}


void print_I(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
{
 unsigned char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

 if(value < 0)
 {
 ch[0] = 0x2D;
 value = -value;
 }
 else
 {
 ch[0] = 0x20;
 }

 if(value > 9999)
 {
 ch[1] = ((value / 10000) + 0x30);
 ch[2] = (((value % 10000)/ 1000) + 0x30);
 ch[3] = (((value % 1000) / 100) + 0x30);
 ch[4] = (((value % 100) / 10) + 0x30);
 ch[5] = ((value % 10) + 0x30);
 }

 else if((value > 999) && (value <= 9999))
 {
 ch[1] = (((value % 10000)/ 1000) + 0x30);
 ch[2] = (((value % 1000) / 100) + 0x30);
 ch[3] = (((value % 100) / 10) + 0x30);
 ch[4] = ((value % 10) + 0x30);
 ch[5] = 0x20;
 }
 else if((value > 99) && (value <= 999))
 {
 ch[1] = (((value % 1000) / 100) + 0x30);
 ch[2] = (((value % 100) / 10) + 0x30);
 ch[3] = ((value % 10) + 0x30);
 ch[4] = 0x20;
 ch[5] = 0x20;
 }
 else if((value > 9) && (value <= 99))
 {
 ch[1] = (((value % 100) / 10) + 0x30);
 ch[2] = ((value % 10) + 0x30);
 ch[3] = 0x20;
 ch[4] = 0x20;
 ch[5] = 0x20;
 }
 else
 {
 ch[1] = ((value % 10) + 0x30);
 ch[2] = 0x20;
 ch[3] = 0x20;
 ch[4] = 0x20;
 ch[5] = 0x20;
 }

 print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
}


void print_D(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points)
{
 unsigned char ch[6] = {0x2E, 0x20, 0x20, 0x20, 0x20, 0x20};

 ch[1] = ((value / 1000) + 0x30);

 if(points > 1)
 {
 ch[2] = (((value % 1000) / 100) + 0x30);

 if(points > 2)
 {
 ch[3] = (((value % 100) / 10) + 0x30);

 if(points > 3)
 {
 ch[4] = ((value % 10) + 0x30);
 }
 }
 }

 print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
}


void print_F(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points)
{
 signed long tmp = 0x0000;

 tmp = value;
 print_I(x_pos, y_pos, font_size, colour, back_colour, tmp);
 tmp = ((value - tmp) * 10000);

 if(tmp < 0)
 {
 tmp = -tmp;
 }

 if((value >= 9999) && (value < 99999))
 {
 print_D((x_pos + (0x24 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if((value >= 999) && (value < 9999))
 {
 print_D((x_pos + (0x1E * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if((value >= 99) && (value < 999))
 {
 print_D((x_pos + (0x18 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if((value >= 9) && (value < 99))
 {
 print_D((x_pos + (0x12 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if(value < 9)
 {
 print_D((x_pos + (0x0C * font_size)), y_pos, font_size, colour, back_colour, tmp, points);

 if((value) < 0)
 {
 print_char(x_pos, y_pos, font_size, colour, back_colour, 0x2D);
 }
 else
 {
 print_char(x_pos, y_pos, font_size, colour, back_colour, 0x20);
 }
 }
}
#line 4 "C:/Users/Shawon/Desktop/ST7735S TFT LCD Demo/TFT_display_demo.c"
void setup();


void main()
{
 float f = -0.09;
 signed int i = -9;
 signed char c = 127;

 setup();

 Set_Rotation(0x01);

 TFT_fill(Swap_Colour( 0x07E0 ));
 Draw_Circle(79, 63, 20,  0x01 , Swap_Colour( 0xF800 ));
 delay_ms(4000);

 TFT_fill(Swap_Colour( 0xFFFF ));

 Draw_Circle(6, 6, 4,  0x01 ,  0xF800 );
 Draw_Circle(153, 6, 4,  0x01 ,  0xF800 );
 Draw_Circle(6, 121, 4,  0x01 ,  0xF800 );
 Draw_Circle(153, 121, 4,  0x01 ,  0xF800 );

 delay_ms(1000);

 Draw_Line(14, 0, 14, 127,  0x07FF );
 Draw_Line(145, 0, 145, 127,  0x07FF );
 Draw_Line(0, 14, 159, 14,  0x07FF );
 Draw_Line(0, 113, 159, 113,  0x07FF );

 delay_ms(1000);

 Draw_Rectangle(17, 17, 142, 110,  0x01 ,  0x01 ,  0x001F ,  0xFFFF );
 delay_ms(1000);

 print_str(22, 58, 2,  0xFFE0 ,  0x001F , "MicroArena");
 delay_ms(4000);

 TFT_fill( 0x0000 );
 print_str(20, 90, 1,  0xFFE0 ,  0x0000 , "www.fb.com/MicroArena");

 while(1)
 {
 print_F(60, 20, 1,  0x001F ,  0x0000 , f, 2);
 print_C(60, 40, 1,  0xF800 ,  0x0000 , c);
 print_I(60, 60, 1,  0x07E0 ,  0x0000 , i);
 f += 0.01;
 c -= 1;
 i += 1;
 if(c < -128)
 {
 c = 127;
 }
 delay_ms(60);
 };
}


void setup()
{
 CLKPR = 0x80;
 CLKPR = 0x00;
 PORTB = 0x00;
 DDRB = 0x1F;
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

 ST7735_init();
}
