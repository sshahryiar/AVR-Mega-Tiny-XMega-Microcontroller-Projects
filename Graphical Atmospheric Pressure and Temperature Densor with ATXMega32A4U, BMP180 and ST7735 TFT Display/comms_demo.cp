#line 1 "C:/Users/SShahryiar/Desktop/BMP180  + ST7735S/comms_demo.c"
#line 1 "c:/users/sshahryiar/desktop/bmp180  + st7735s/io.h"
#line 1 "c:/users/sshahryiar/desktop/bmp180  + st7735s/clock.h"
#line 1 "c:/users/sshahryiar/desktop/bmp180  + st7735s/st7735.c"
#line 1 "c:/users/sshahryiar/desktop/bmp180  + st7735s/st7735.h"
#line 1 "c:/users/sshahryiar/desktop/bmp180  + st7735s/font.c"
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
#line 116 "c:/users/sshahryiar/desktop/bmp180  + st7735s/st7735.h"
unsigned char w =  128 ;
unsigned char l =  160 ;


void swap(signed int *a, signed int *b);
void setup_TFT_peripherals();
void TFT_Write(unsigned char value, unsigned char mode);
void ST7735_Reset();
void ST7735_init();
void TFT_write_word(unsigned int value);
void TFT_set_display_window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye);
void Invert_Display(unsigned char i);
unsigned int Swap_Colour(unsigned int colour);
unsigned int Color565(unsigned char r, unsigned char g, unsigned char b);
void Set_Rotation(unsigned char m);
void TFT_fill(unsigned int colour);
void TFT_fill_area(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour);
void Draw_Point(unsigned int x_pos, unsigned int y_pos, unsigned char pen_width, unsigned int colour);
void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour);
void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour);
void Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour);
void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour);
void Draw_H_Bar(signed int x1, signed int x2, signed int y1, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour);
void Draw_Font_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour, unsigned char pixel_size);
void print_char(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch);
void print_str(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch);
void print_C(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_I(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_D(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points);
void print_F(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points);
void Draw_BMP(signed int x_pos1, signed int y_pos1, signed int x_pos2, signed int y_pos2, unsigned char *bitmap);
#line 4 "c:/users/sshahryiar/desktop/bmp180  + st7735s/st7735.c"
void swap(signed int *a, signed int *b)
{
 signed int temp = 0x0000;

 temp = *b;
 *b = *a;
 *a = temp;
}


void setup_TFT_peripherals()
{
 PORTC_DIR = 0xBE;
 VPORT2_DIR = 0xBE;
 delay_ms(100);

 SPIC_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV2, _SPI_CLK_HI_LEADING);
 SPI_Set_Active(&SPIC_Read, &SPIC_Write);
 delay_ms(10);
}


void TFT_Write(unsigned char value, unsigned char mode)
{
  PORTC_OUT.B4  =  0 ;
  PORTC_OUT.B3  = mode;
 SPIC_Write(value);
  PORTC_OUT.B4  =  1 ;
}


void ST7735_Reset()
{
  PORTC_OUT.B2  =  0 ;
 delay_ms(2);
  PORTC_OUT.B2  =  1 ;
 delay_ms(2);
}


void ST7735_init()
{
 setup_TFT_peripherals();

 ST7735_Reset();

 TFT_Write( 0x01 ,  0 );
 delay_us(150);
 TFT_Write( 0x11 ,  0 );
 delay_us(150);

 TFT_Write( 0xB1 ,  0 );
 TFT_Write(0x01,  1 );
 TFT_Write(0x2C,  1 );
 TFT_Write(0x2D,  1 );

 TFT_Write( 0xB2 ,  0 );
 TFT_Write(0x01,  1 );
 TFT_Write(0x2C,  1 );
 TFT_Write(0x2D,  1 );

 TFT_Write( 0xB3 ,  0 );
 TFT_Write(0x01,  1 );
 TFT_Write(0x2C,  1 );
 TFT_Write(0x2D,  1 );
 TFT_Write(0x01,  1 );
 TFT_Write(0x2C,  1 );
 TFT_Write(0x2D,  1 );

 TFT_Write( 0xB4 ,  0 );
 TFT_Write(0x07,  1 );

 TFT_Write( 0xC0 ,  0 );
 TFT_Write(0xA2,  1 );
 TFT_Write(0x02,  1 );
 TFT_Write(0x84,  1 );

 TFT_Write( 0xC0 ,  0 );
 TFT_Write(0xC5,  1 );

 TFT_Write( 0xC1 ,  0 );
 TFT_Write(0x0A,  1 );
 TFT_Write(0x00,  1 );

 TFT_Write( 0xC2 ,  0 );
 TFT_Write(0x8A,  1 );
 TFT_Write(0x2A,  1 );

 TFT_Write( 0xC3 ,  0 );
 TFT_Write(0x8A,  1 );
 TFT_Write(0xEE,  1 );

 TFT_Write( 0xC4 ,  0 );
 TFT_Write(0x0E,  1 );

 TFT_Write( 0xC5 ,  0 );
 TFT_Write(0x00,  1 );

 TFT_Write( 0x3A ,  0 );
 TFT_Write(0x05,  1 );

 TFT_Write( 0x36 ,  0 );
 TFT_Write(0xC8,  1 );

 TFT_set_display_window(0x00, 0x00, 0x7F, 0x9F);

 TFT_Write( 0xE0 ,  0 );
 TFT_Write(0x02,  1 );
 TFT_Write(0x1C,  1 );
 TFT_Write(0x07,  1 );
 TFT_Write(0x12,  1 );
 TFT_Write(0x37,  1 );
 TFT_Write(0x32,  1 );
 TFT_Write(0x29,  1 );
 TFT_Write(0x2D,  1 );
 TFT_Write(0x29,  1 );
 TFT_Write(0x25,  1 );
 TFT_Write(0x2B,  1 );
 TFT_Write(0x39,  1 );
 TFT_Write(0x00,  1 );
 TFT_Write(0x01,  1 );
 TFT_Write(0x03,  1 );
 TFT_Write(0x10,  1 );

 TFT_Write( 0xE1 ,  0 );
 TFT_Write(0x03,  1 );
 TFT_Write(0x1D,  1 );
 TFT_Write(0x07,  1 );
 TFT_Write(0x06,  1 );
 TFT_Write(0x2E,  1 );
 TFT_Write(0x2C,  1 );
 TFT_Write(0x29,  1 );
 TFT_Write(0x2D,  1 );
 TFT_Write(0x2E,  1 );
 TFT_Write(0x2E,  1 );
 TFT_Write(0x37,  1 );
 TFT_Write(0x3F,  1 );
 TFT_Write(0x00,  1 );
 TFT_Write(0x00,  1 );
 TFT_Write(0x02,  1 );
 TFT_Write(0x10,  1 );

 TFT_Write( 0x13 ,  0 );
 delay_ms(10);

 TFT_Write( 0x29 ,  0 );
 delay_ms(100);

 TFT_Write( 0x2C ,  0 );
 delay_ms(100);
}


void TFT_write_word(unsigned int value)
{
 TFT_Write((value >> 0x08),  1 );
 TFT_Write((value & 0x00FF),  1 );
}


void TFT_set_display_window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye)
{
 TFT_Write( 0x2A ,  0 );
 TFT_Write(0x00,  1 );
 TFT_Write(xs,  1 );
 TFT_Write(0x00,  1 );
 TFT_Write(xe,  1 );

 TFT_Write( 0x2B ,  0 );
 TFT_Write(0x00,  1 );
 TFT_Write(ys,  1 );
 TFT_Write(0x00,  1 );
 TFT_Write(ye,  1 );

 TFT_Write( 0x2C ,  0 );
}


void Invert_Display(unsigned char i)
{
 if(i ==  0x21 )
 {
 TFT_Write( 0x21 ,  0 );
 }
 else
 {
 TFT_Write( 0x20 ,  0 );
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

 TFT_Write( 0x36 ,  0 );
 rotation = (m % 4);

 switch(rotation)
 {
 case 0:
 {
 TFT_Write(( 0x40  |  0x80  |  0x08 ),  1 );
 break;
 }
 case 1:
 {
 TFT_Write(( 0x80  |  0x20  |  0x08 ),  1 );
 break;
 }
 case 2:
 {
 TFT_Write(( 0x08 ),  1 );
 break;
 }
 case 3:
 {
 TFT_Write(( 0x40  |  0x20  |  0x08 ),  1 );
 break;
 }
 }

 if((rotation == 0) || (rotation == 2))
 {
 w =  128 ;
 l =  160 ;
 }
 if((rotation == 1) || (rotation == 3))
 {
 w =  160 ;
 l =  128 ;
 }
}


void TFT_fill(unsigned int colour)
{
 unsigned int index =  ( 128  * 160 ) ;

 TFT_set_display_window(0, 0, (w - 1), (l - 1));

 while(index > 0)
 {
 TFT_write_word(colour);
 index--;
 }
}


void TFT_fill_area(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour)
{
 unsigned int index = 0x0000;

 if(x1 > x2)
 {
 swap(&x1, &x2);
 }
 if(y1 > y2)
 {
 swap(&y1, &y2);
 }

 index = (x2 - x1);
 index *= (y2 - y1);

 TFT_set_display_window(x1, y1, (x2 - 1), (y2 - 1));

 while(index)
 {
 TFT_write_word(colour);
 index--;
 };
}


void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour)
{
 unsigned int col = Swap_Colour(colour);
 TFT_set_display_window(x_pos, y_pos, (1 + x_pos), (1 + y_pos));
 TFT_write_word(col);
}


void Draw_Point(unsigned int x_pos, unsigned int y_pos, unsigned char pen_width, unsigned int colour)
{
 Draw_Circle(x_pos, y_pos, pen_width,  1 , colour);
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

 if(dy < 0)
 {
 dy = -dy;
 stepy = -1;
 }
 else
 {
 stepy = 1;
 }

 if(dx < 0)
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

 if(dx > dy)
 {
 fraction = (dy - (dx >> 1));
 while(x1 != x2)
 {
 if(fraction >= 0)
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

 while(y1 != y2)
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


void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour)
{
 signed int pos = 0;
 signed int temp = 0;

 if(y1 > y2)
 {
 swap(&y1, &y2);
 }

 while(y2 > (y1 - 1))
 {
 Draw_Pixel(x1, y2, colour);
 y2--;
 }
}


void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour)
{
 signed int pos = 0;
 signed int temp = 0;

 if(x1 > x2)
 {
 swap(&x1, &x2);
 }

 while(x2 > (x1 - 1))
 {
 Draw_Pixel(x2, y1, colour);
 x2--;
 }
}


void Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour)
{
 signed int a = 0;
 signed int b = 0;
 signed int sa = 0;
 signed int sb = 0;
 signed int yp = 0;
 signed int last = 0;
 signed int dx12 = 0;
 signed int dx23 = 0;
 signed int dx13 = 0;
 signed int dy12 = 0;
 signed int dy23 = 0;
 signed int dy13 = 0;

 switch(fill)
 {
 case  1 :
 {
 if(y1 > y2)
 {
 swap(&y1, &y2);
 swap(&x1, &x2);
 }
 if(y2 > y3)
 {
 swap(&y3, &y2);
 swap(&x3, &x2);
 }
 if(y1 > y2)
 {
 swap(&y1, &y2);
 swap(&x1, &x2);
 }

 if(y1 == y3)
 {
 a = b = x1;

 if(x2 < a)
 {
 a = x2;
 }
 else if(x2 > b)
 {
 b = x2;
 }
 if(x2 < a)
 {
 a = x3;
 }
 else if(x3 > b)
 {
 b = x3;
 }

 Draw_H_Line(a, (a + (b - (a + 1))), y1, colour);
 return;
 }

 dx12 = (x2 - x1);
 dy12 = (y2 - y1);
 dx13 = (x3 - x1);
 dy13 = (y3 - y1);
 dx23 = (x3 - x2);
 dy23 = (y3 - y2);
 sa = 0,
 sb = 0;

 if(y2 == y3)
 {
 last = y2;
 }
 else
 {
 last = (y2 - 1);
 }

 for(yp = y1; yp <= last; yp++)
 {
 a = (x1 + (sa / dy12));
 b = (x1 + (sb / dy13));
 sa += dx12;
 sb += dx13;
 if(a > b)
 {
 swap(&a, &b);
 }
 Draw_H_Line(a, (a + (b - (a + 1))), yp, colour);
 }

 sa = (dx23 * (yp - y2));
 sb = (dx13 * (yp - y1));
 for(; yp <= y3; yp++)
 {
 a = (x2 + (sa / dy23));
 b = (x1 + (sb / dy13));
 sa += dx23;
 sb += dx13;

 if(a > b)
 {
 swap(&a, &b);
 }
 Draw_H_Line(a, (a + (b - (a + 1))), yp, colour);
 }


 break;
 }
 default:
 {
 Draw_Line(x1, y1, x2, y2, colour);
 Draw_Line(x2, y2, x3, y3, colour);
 Draw_Line(x3, y3, x1, y1, colour);
 break;
 }
 }
}


void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour)
{
 signed int i = 0x0000;
 signed int xmin = 0x0000;
 signed int xmax = 0x0000;
 signed int ymin = 0x0000;
 signed int ymax = 0x0000;

 switch(fill)
 {
 case  1 :
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

 break;
 }
 default:
 {
 Draw_V_Line(x1, y1, y2, colour);
 Draw_V_Line(x2, y1, y2, colour);
 Draw_H_Line(x1, x2, y1, colour);
 Draw_H_Line(x1, x2, y2, colour);
 break;
 }
 }

 if(type !=  0 )
 {
 Draw_Pixel(x1, y1, back_colour);
 Draw_Pixel(x1, y2, back_colour);
 Draw_Pixel(x2, y1, back_colour);
 Draw_Pixel(x2, y2, back_colour);
 }
}


void Draw_H_Bar(signed int x1, signed int x2, signed int y1, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border)
{
 switch(border)
 {
 case  1 :
 {
 Draw_Rectangle((x1 + 1), (y1 + 1), (x1 + bar_value), (y1 + bar_width - 1),  1 ,  0 , bar_colour, back_colour);
 Draw_Rectangle((x2 - 1), (y1 + 1), (x1 + bar_value + 1), (y1 + bar_width - 1),  1 ,  0 , back_colour, back_colour);
 Draw_Rectangle(x1, y1, x2, (y1 + bar_width),  0 ,  0 , border_colour, back_colour);
 break;
 }
 default:
 {
 Draw_Rectangle(x1, y1, (x1 + bar_value), (y1 + bar_width),  1 ,  0 , bar_colour, back_colour);
 Draw_Rectangle(x2, y1, (x1 + bar_value), (y1 + bar_width),  1 ,  0 , back_colour, back_colour);
 break;
 }
 }
}


void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border)
{
 switch(border)
 {
 case  1 :
 {
 Draw_Rectangle((x1 + 1), (y2 - 1), (x1 + bar_width - 1), (y2 - bar_value),  1 ,  0 , bar_colour, back_colour);
 Draw_Rectangle((x1 + 1), (y2 - bar_value - 1), (x1 + bar_width - 1), (y1 + 1),  1 ,  0 , back_colour, back_colour);
 Draw_Rectangle(x1, y1, (x1 + bar_width), y2,  0 ,  0 , border_colour, back_colour);
 break;
 }
 default:
 {
 Draw_Rectangle(x1, y2, (x1 + bar_width), (y2 - bar_value),  1 ,  0 , bar_colour, back_colour);
 Draw_Rectangle(x1, (y2 - bar_value), (x1 + bar_width), y1,  1 ,  0 , back_colour, back_colour);
 break;
 }
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
 switch(fill)
 {
 case  1 :
 {
 Draw_Line((xc - a), (yc + b), (xc + a), (yc + b), colour);
 Draw_Line((xc - a), (yc - b), (xc + a), (yc - b), colour);
 Draw_Line((xc - b), (yc + a), (xc + b), (yc + a), colour);
 Draw_Line((xc - b), (yc - a), (xc + b), (yc - a), colour);
 break;
 }
 default:
 {
 Draw_Pixel((xc + a), (yc + b), colour);
 Draw_Pixel((xc + b), (yc + a), colour);
 Draw_Pixel((xc - a), (yc + b), colour);
 Draw_Pixel((xc - b), (yc + a), colour);
 Draw_Pixel((xc + b), (yc - a), colour);
 Draw_Pixel((xc + a), (yc - b), colour);
 Draw_Pixel((xc - a), (yc - b), colour);
 Draw_Pixel((xc - b), (yc - a), colour);
 break;
 }
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
 unsigned char i = (pixel_size * pixel_size);
 unsigned int col = Swap_Colour(colour);

 TFT_set_display_window(x_pos, y_pos, (x_pos + pixel_size - 1), (y_pos + pixel_size - 1));

 while(i > 0)
 {
 TFT_write_word(col);
 i--;
 };
}


void print_char(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch)
{
 unsigned char i = 0x00;
 unsigned char j = 0x00;
 unsigned char value = 0x00;

 if(font_size <= 0)
 {
 font_size = 1;
 }

 if(x_pos < font_size)
 {
 x_pos = font_size;
 }

 for(i = 0x00; i < 0x05; i++)
 {
 for(j = 0x00; j < 0x08; j++)
 {
 value = 0x0000;
 value = ((font[((unsigned char)ch) - 0x20][i]));

 if(((value >> j) & 0x01) != 0x00)
 {
 Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
 }
 else
 {
 Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
 }

 y_pos += font_size;
 }

 y_pos -= (font_size << 0x03);
 x_pos += font_size;
 }
}


void print_str(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch)
{
 do
 {
 print_char(x_pos, y_pos, font_size, colour, back_colour, *ch++);
 x_pos += (font_size * 0x06);
 }while((*ch >= 0x20) && (*ch <= 0x7F));

 print_char(x_pos, y_pos, font_size, colour, back_colour, 0x20);
}


void print_C(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
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


void print_I(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
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


void print_D(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points)
{
 unsigned char ch[4] = {0x2E, 0x20, 0x20, 0x20};

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


void print_F(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points)
{
 signed long tmp = 0x0000;

 tmp = value;
 print_I(x_pos, y_pos, font_size, colour, back_colour, tmp);
 tmp = ((value - tmp) * 10000);

 if(tmp < 0)
 {
 tmp = -tmp;
 }

 if((value >= 10000) && (value < 100000))
 {
 print_D((x_pos + 36), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if((value >= 1000) && (value < 10000))
 {
 print_D((x_pos + 30), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if((value >= 100) && (value < 1000))
 {
 print_D((x_pos + 24), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if((value >= 10) && (value < 100))
 {
 print_D((x_pos + 18), y_pos, font_size, colour, back_colour, tmp, points);
 }
 else if(value < 10)
 {
 print_D((x_pos + 12), y_pos, font_size, colour, back_colour, tmp, points);

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


void Draw_BMP(signed int x_pos1, signed int y_pos1, signed int x_pos2, signed int y_pos2, unsigned char *bitmap)
{
 unsigned int size = 0x0000;
 unsigned int index = 0x0000;

 if(x_pos1 > x_pos2)
 {
 swap(&x_pos1, &x_pos2);
 }

 if(y_pos1 > y_pos2)
 {
 swap(&y_pos1, &y_pos2);
 }

 size = (y_pos2 - y_pos1);
 size *= (x_pos2 - x_pos1);
 size <<= 1;

 TFT_set_display_window(x_pos1, y_pos1, (x_pos2 - 1), (y_pos2 - 1));

 for(index = 0; index < size; index++)
 {
 TFT_write(*bitmap++,  1 );
 }
}
#line 1 "c:/users/sshahryiar/desktop/bmp180  + st7735s/bmp180.c"
#line 1 "c:/users/sshahryiar/desktop/bmp180  + st7735s/bmp180.h"
#line 21 "c:/users/sshahryiar/desktop/bmp180  + st7735s/bmp180.h"
signed int _b1 = 0;
signed int _b2 = 0;
signed int mb = 0;
signed int mc = 0;
signed int md = 0;
signed int ac1 = 0;
signed int ac2 = 0;
signed int ac3 = 0;

unsigned int ac4 = 0;
unsigned int ac5 = 0;
unsigned int ac6 = 0;

signed long _b5 = 0;


void BMP180_init();
signed char BMP180_read_byte(unsigned char address);
signed int BMP180_read_word(unsigned char address);
void BMP180_write(unsigned char address, unsigned char value);
void BMP180_Calibration();
unsigned int read_uncompensated_temperature();
unsigned long read_uncompensated_pressure(unsigned char OSS);
float get_temperature(unsigned int UT);
signed long get_pressure(unsigned long UP, unsigned char OSS);
#line 4 "c:/users/sshahryiar/desktop/bmp180  + st7735s/bmp180.c"
void BMP180_init()
{
 TWIC_Init(100000);
 delay_ms(100);

 BMP180_Calibration();
}


signed char BMP180_read_byte(unsigned char address)
{
 unsigned char temp = 0;

 TWIC_Start();
 TWIC_Write( 0xEE );
 TWIC_Write(address);
 TWIC_Start();
 TWIC_Write( 0xEE  | 1);
 temp = TWIC_Read(0);
 TWIC_Stop();

 return temp;
}


signed int BMP180_read_word(unsigned char address)
{
 unsigned char hb = 0;
 unsigned char lb = 0;

 signed int temp = 0;

 TWIC_Start();
 TWIC_Write( 0xEE );
 TWIC_Write(address);
 TWIC_Start();
 TWIC_Write( 0xEE  | 1);
 hb = TWIC_Read(1);
 lb = TWIC_Read(0);
 TWIC_Stop();
 temp = ((hb << 8) | lb);

 return temp;
}


void BMP180_write(unsigned char address, unsigned char value)
{
 TWIC_Start();
 TWIC_Write( 0xEE );
 TWIC_Write(address);
 TWIC_Write(value);
 TWIC_Stop();
}


void BMP180_Calibration()
{
 _b1 = BMP180_read_word( 0xB6 );
 _b2 = BMP180_read_word( 0xB8 );
 mb = BMP180_read_word( 0xBA );
 mc = BMP180_read_word( 0xBC );
 md = BMP180_read_word( 0xBE );
 ac1 = BMP180_read_word( 0xAA );
 ac2 = BMP180_read_word( 0xAC );
 ac3 = BMP180_read_word( 0xAE );
 ac4 = BMP180_read_word( 0xB0 );
 ac5 = BMP180_read_word( 0xB2 );
 ac6 = BMP180_read_word( 0xB4 );
}


unsigned int read_uncompensated_temperature()
{
 unsigned int ut = 0;

 BMP180_write( 0xF4 ,  0x2E );
 delay_ms(5);
 ut = BMP180_read_word( 0xF6 );

 return ut;
}


unsigned long read_uncompensated_pressure(unsigned char OSS)
{
 unsigned char msb_value = 0;
 unsigned char lsb_value = 0;
 unsigned char xlsb_value = 0;

 unsigned long up = 0;

 BMP180_write( 0xF4 , (0x34 + (OSS << 6)));
 switch(OSS)
 {
 case 1:
 {
 delay_ms(8);
 break;
 }
 case 2:
 {
 delay_ms(14);
 break;
 }
 case 3:
 {
 delay_ms(26);
 break;
 }
 default:
 {
 delay_ms(5);
 break;
 }
 }

 msb_value = BMP180_read_byte( 0xF6 );
 lsb_value = BMP180_read_byte( 0xF7 );
 xlsb_value = BMP180_read_byte( 0xF8 );

 up = ((((unsigned long)msb_value << 16) | ((unsigned long)lsb_value << 8) | (unsigned long)xlsb_value) >> (8 - OSS));

 return up;
}


float get_temperature(unsigned int UT)
{
 float tmp = 0;

 signed long x1 = 0;
 signed long x2 = 0;

 x1 = ((((signed long)UT - (signed long)ac6) * (signed long)ac5) >> 15);
 x2 = (((signed long)mc << 11) / (x1 + md));
 _b5 = (x1 + x2);
 tmp = ((_b5 + 8) >> 4);
 tmp *= 0.1;

 return tmp;
}


signed long get_pressure(unsigned long UP, unsigned char OSS)
{
 signed long p = 0;
 signed long x1 = 0;
 signed long x2 = 0;
 signed long x3 = 0;
 signed long _b3 = 0;
 signed long _b6 = 0;

 unsigned long _b4 = 0;
 unsigned long _b7 = 0;

 _b6 = (_b5 - 4000);

 x1 = ((_b2 * (_b6 * _b6) >> 12) >> 11);
 x2 = ((ac2 * _b6) >> 11);
 x3 = (x1 + x2);
 _b3 = (((((((signed long)ac1) << 2) + x3) << OSS) + 2) >> 2);
 x1 = ((ac3 * _b6) >> 13);
 x2 = ((_b1 * ((_b6 * _b6) >> 12)) >> 16);
 x3 = (((x1 + x2) + 2) >> 2);
 _b4 = ((ac4 * (unsigned long)(x3 + 32768)) >> 15);
 _b7 = ((unsigned long)(UP - _b3) * (50000 >> OSS));

 if(_b7 < 0x80000000)
 {
 p = ((_b7 << 1) / _b4);
 }
 else
 {
 p = ((_b7 / _b4) << 1);
 }

 x1 = ((p >> 8) * (p >> 8));
 x1 = ((x1 * 3038) >> 16);
 x2 = ((-7357 * p) >> 16);
 p += ((x1 + x2 + 3791) >> 4);

 return (signed long)p;
}
#line 7 "C:/Users/SShahryiar/Desktop/BMP180  + ST7735S/comms_demo.c"
const unsigned char symbol[][5] = {0x00, 0x0C, 0x12, 0x12, 0x0C};


void setup();
void clock_setup();
void GPIO_setup();
void draw_background();
float map(float value, float x_min, float x_max, float y_min, float y_max);
float constrain(float value, float value_min, float value_max);
void print_symbol(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch);


void main()
{
 unsigned char sample = 0;
 unsigned char tp = 0;
 unsigned char pp = 0;

 float T = 0.0;
 float P = 0.0;

 setup();
 draw_background();

 while(1)
 {
 T = read_uncompensated_temperature();
 T = get_temperature(T);
 P = read_uncompensated_pressure( 0x03 );
 P = get_pressure(P,  0x03 );
 P *= 0.001;

 print_str(1, 120, 1,  0xF800 ,  0x0000 , "T/ C:");
 print_symbol(13, 120, 1,  0xF800 ,  0x0000 , 0);
 print_F(36, 120, 1,  0xF800 ,  0x0000 , T, 2);

 print_str(80, 120, 1,  0x07E0 ,  0x0000 , "P/kPa:");
 print_F(116, 120, 1,  0x07E0 ,  0x0000 , P, 2);

 tp = map(T, 0, 100, 10, 110);
 tp = constrain(tp, 10, 110);
 pp = map(P, 50, 150, 10, 110);
 pp = constrain(pp, 10, 110);

 Draw_V_Line((58 + sample), 10, 110,  0x0000 );

 Draw_Pixel((sample + 58), (120 - tp),  0xF800 );
 Draw_Pixel((sample + 58), (120 - pp),  0x07E0 );
 sample++;

 if(sample > 99)
 {
 sample = 0;
 }

 PORTE_OUT.B2 ^= 1;
 delay_ms(400);
 };
}


void setup()
{
 clock_setup();
 GPIO_setup();
 BMP180_init();
 ST7735_init();
 Set_Rotation(0x03);
 TFT_fill(Swap_Colour( 0x0000 ));
}


void clock_setup()
{
 OSC_CTRL |=  0x04 ;
 while(!(OSC_STATUS &  0x04 ));
 OSC_CTRL |=  0x02 ;
 CPU_CCP =  0xD8 ;
 CLK_PSCTRL = ((CLK_PSCTRL & (~( 0x7C  |  0x02 
 |  0x01 ))) |  0x00  |  0x03 );
 OSC_DFLLCTRL = ((OSC_DFLLCTRL & (~( 0x06  |  0x01 ))) |
  0x00 );
 DFLLRC32M_CTRL |=  0x01 ;
 while(!(OSC_STATUS &  0x02 ));
 CPU_CCP =  0xD8 ;
 CLK_CTRL = ((CLK_CTRL & (~ 0x07 )) |  0x01 );
 OSC_CTRL &= (~( 0x01  |  0x08  |  0x10 ));
 PORTCFG_CLKEVOUT = 0x00;
}


void GPIO_setup()
{
 PORTA_OUT = 0x00;
 PORTA_DIR = 0x00;
 PORTCFG_MPCMASK = 0xFF;
 PORTA_PIN0CTRL = ( 0x00  |  0x00 );
 PORTA_INTCTRL = ((PORTA_INTCTRL & (~( 0x0C  |  0x03 ))) |
  0x00  |  0x00 );
 PORTA_INT0MASK = 0x00;
 PORTA_INT1MASK = 0x00;

 PORTB_OUT = 0x00;
 PORTB_DIR = 0x00;
 PORTCFG_MPCMASK = 0x0F;
 PORTB_PIN0CTRL = ( 0x00  |  0x00 );
 PORTB_INTCTRL = ((PORTB_INTCTRL & (~( 0x0C  |  0x03 ))) |
  0x00  |  0x00 );
 PORTB_INT0MASK = 0x00;
 PORTB_INT1MASK = 0x00;


 PORTC_OUT = 0x00;
 PORTC_DIR = 0xBE;
 PORTCFG_MPCMASK = 0xFF;
 PORTC_PIN0CTRL = ( 0x00  |  0x00 );
 PORTC_REMAP = ((0 <<  0x05 ) | (0 <<  0x04 ) | (0 <<  0x03 ) | (0 <<  0x02 ) | (0 <<  0x01 ) | (0 <<  0x00 ));
 PORTC_INTCTRL = ((PORTC_INTCTRL & (~( 0x0C  |  0x03 ))) |
  0x00  |  0x00 );
 PORTC_INT0MASK = 0x00;
 PORTC_INT1MASK = 0x00;

 PORTD_OUT = 0x00;
 PORTD_DIR = 0x00;
 PORTCFG_MPCMASK = 0xFF;
 PORTD_PIN0CTRL = ( 0x18  |  0x00 );
 PORTD_INTCTRL = ((PORTD_INTCTRL & (~( 0x0C  |  0x03 ))) |
  0x00  |  0x00 );
 PORTD_INT0MASK = 0x00;
 PORTD_INT1MASK = 0x00;

 PORTE_OUT = 0x0C;
 PORTE_DIR = 0x0C;
 PORTCFG_MPCMASK = 0x0F;
 PORTE_PIN0CTRL = ( 0x00  |  0x00 );
 PORTE_INTCTRL = ((PORTE_INTCTRL & (~( 0x0C  |  0x03 ))) |
  0x00  |  0x00 );
 PORTE_INT0MASK = 0x00;
 PORTE_INT1MASK = 0x00;

 PORTR_OUT = 0x00;
 PORTR_DIR = 0x00;
 PORTCFG_MPCMASK = 0x03;
 PORTR_PIN0CTRL = ( 0x00  |  0x00 );
 PORTR_INTCTRL = ((PORTR_INTCTRL & (~( 0x0C  |  0x03 ))) |
  0x00  |  0x00 );
 PORTR_INT0MASK = 0x00;
 PORTR_INT1MASK = 0x00;

 PORTCFG_VPCTRLA = ( 0x10  |  0x00 );
 PORTCFG_VPCTRLB = ( 0x30  |  0x02 );
}


void draw_background()
{
 unsigned char points = 0x00;

 print_str(60, 1, 1,  0x051F ,  0x0000 , "BMP180 + XMega");

 Draw_Rectangle(57, 9, 158, 111,  0 ,  0 ,  0xFFFF ,  0x0000 );

 Draw_V_Line(50, 110, 10,  0xF800 );
 Draw_V_Line(25, 110, 10,  0x07E0 );

 for(points = 0; points <= 100; points += 10)
 {
 Draw_H_Line(23, 27, (10 + points),  0x07E0 );
 Draw_H_Line(48, 52, (10 + points),  0xF800 );
 }

 for(points = 0; points <= 95; points += 10)
 {
 Draw_H_Line(24, 26, (15 + points),  0x07E0 );
 Draw_H_Line(49, 51, (15 + points),  0xF800 );
 }

 print_str(0, 1, 1,  0x07E0 ,  0x0000 , "kPa");
 print_symbol(40, 1, 1,  0xF800 ,  0x0000 , 0);
 print_str(46, 1, 1,  0xF800 ,  0x0000 , "C");

 print_str(0, 10, 1,  0x07E0 ,  0x0000 , "150");
 print_str(31, 20, 1,  0xF800 ,  0x0000 , "90");

 print_str(0, 60, 1,  0x07E0 ,  0x0000 , "100");
 print_str(31, 60, 1,  0xF800 ,  0x0000 , "50");

 print_str(0, 106, 1,  0x07E0 ,  0x0000 , "50");
 print_str(31, 106, 1,  0xF800 ,  0x0000 , "0");
}


float map(float value, float x_min, float x_max, float y_min, float y_max)
{
 return (y_min + (((y_max - y_min) / ((x_max - x_min)) * (value - x_min))));
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


void print_symbol(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch)
{
 unsigned char i = 0x00;
 unsigned char j = 0x00;
 unsigned char value = 0x00;

 if(font_size <= 0)
 {
 font_size = 1;
 }

 if(x_pos < font_size)
 {
 x_pos = font_size;
 }

 for(i = 0x00; i < 0x05; i++)
 {
 for(j = 0x00; j < 0x08; j++)
 {
 value = 0x0000;
 value = ((symbol[((unsigned char)ch)][i]));

 if(((value >> j) & 0x01) != 0x00)
 {
 Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
 }
 else
 {
 Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
 }

 y_pos += font_size;
 }

 y_pos -= (font_size << 0x03);
 x_pos += font_size;
 }
}
