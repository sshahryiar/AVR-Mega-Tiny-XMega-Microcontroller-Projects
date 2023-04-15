#include "ST7735.h"


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
    CS_pin = LOW;
    RS_pin = mode;
    SPIC_Write(value);
    CS_pin = HIGH;
}


void ST7735_Reset()
{
    RST_pin = LOW;
    delay_ms(2);
    RST_pin = HIGH;
    delay_ms(2);
}


void ST7735_init()
{
    setup_TFT_peripherals();
    
    ST7735_Reset();

    TFT_Write(ST7735_SWRESET, CMD);
    delay_us(150);
    TFT_Write(ST7735_SLPOUT, CMD);
    delay_us(150);

    TFT_Write(ST7735_FRMCTR1, CMD);
    TFT_Write(0x01, DAT);
    TFT_Write(0x2C, DAT);
    TFT_Write(0x2D, DAT);
    
    TFT_Write(ST7735_FRMCTR2, CMD);
    TFT_Write(0x01, DAT);
    TFT_Write(0x2C, DAT);
    TFT_Write(0x2D, DAT);
    
    TFT_Write(ST7735_FRMCTR3, CMD);
    TFT_Write(0x01, DAT);
    TFT_Write(0x2C, DAT);
    TFT_Write(0x2D, DAT);
    TFT_Write(0x01, DAT);
    TFT_Write(0x2C, DAT);
    TFT_Write(0x2D, DAT);

    TFT_Write(ST7735_INVCTR, CMD);
    TFT_Write(0x07, DAT);

    TFT_Write(ST7735_PWCTR1, CMD);
    TFT_Write(0xA2, DAT);
    TFT_Write(0x02, DAT);
    TFT_Write(0x84, DAT);

    TFT_Write(ST7735_PWCTR1, CMD);
    TFT_Write(0xC5, DAT);

    TFT_Write(ST7735_PWCTR2, CMD);
    TFT_Write(0x0A, DAT);
    TFT_Write(0x00, DAT);

    TFT_Write(ST7735_PWCTR3, CMD);
    TFT_Write(0x8A, DAT);
    TFT_Write(0x2A, DAT);

    TFT_Write(ST7735_PWCTR4, CMD);
    TFT_Write(0x8A, DAT);
    TFT_Write(0xEE, DAT);

    TFT_Write(ST7735_PWCTR5, CMD);
    TFT_Write(0x0E, DAT);

    TFT_Write(ST7735_VMCTR1, CMD);
    TFT_Write(0x00, DAT);

    TFT_Write(ST7735_COLMOD, CMD);
    TFT_Write(0x05, DAT);

    TFT_Write(ST7735_MADCTL, CMD);
    TFT_Write(0xC8, DAT);
    
    TFT_set_display_window(0x00, 0x00, 0x7F, 0x9F);
    
    TFT_Write(ST7735_GMCTRP1, CMD);
    TFT_Write(0x02, DAT);
    TFT_Write(0x1C, DAT);
    TFT_Write(0x07, DAT);
    TFT_Write(0x12, DAT);
    TFT_Write(0x37, DAT);
    TFT_Write(0x32, DAT);
    TFT_Write(0x29, DAT);
    TFT_Write(0x2D, DAT);
    TFT_Write(0x29, DAT);
    TFT_Write(0x25, DAT);
    TFT_Write(0x2B, DAT);
    TFT_Write(0x39, DAT);
    TFT_Write(0x00, DAT);
    TFT_Write(0x01, DAT);
    TFT_Write(0x03, DAT);
    TFT_Write(0x10, DAT);
    
    TFT_Write(ST7735_GMCTRN1, CMD);
    TFT_Write(0x03, DAT);
    TFT_Write(0x1D, DAT);
    TFT_Write(0x07, DAT);
    TFT_Write(0x06, DAT);
    TFT_Write(0x2E, DAT);
    TFT_Write(0x2C, DAT);
    TFT_Write(0x29, DAT);
    TFT_Write(0x2D, DAT);
    TFT_Write(0x2E, DAT);
    TFT_Write(0x2E, DAT);
    TFT_Write(0x37, DAT);
    TFT_Write(0x3F, DAT);
    TFT_Write(0x00, DAT);
    TFT_Write(0x00, DAT);
    TFT_Write(0x02, DAT);
    TFT_Write(0x10, DAT);

    TFT_Write(ST7735_NORON, CMD);
    delay_ms(10);

    TFT_Write(ST7735_DISPON, CMD);
    delay_ms(100);
    
    TFT_Write(ST7735_RAMWR, CMD);
    delay_ms(100);
}


void TFT_write_word(unsigned int value)
{
    TFT_Write((value >> 0x08), DAT);
    TFT_Write((value & 0x00FF), DAT);
}


void TFT_set_display_window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye)
{
    TFT_Write(ST7735_CASET, CMD);
    TFT_Write(0x00, DAT);
    TFT_Write(xs, DAT);
    TFT_Write(0x00, DAT);
    TFT_Write(xe, DAT);

    TFT_Write(ST7735_RASET, CMD);
    TFT_Write(0x00, DAT);
    TFT_Write(ys, DAT);
    TFT_Write(0x00, DAT);
    TFT_Write(ye, DAT);

    TFT_Write(ST7735_RAMWR, CMD);
}


void Invert_Display(unsigned char i)
{
     if(i == ST7735_INVON)
     {
         TFT_Write(ST7735_INVON, CMD);
     }
     else
     {
         TFT_Write(ST7735_INVOFF, CMD);
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

    TFT_Write(ST7735_MADCTL, CMD);
    rotation = (m % 4);
    
    switch(rotation)
    {
        case 0:
        {
            TFT_Write((ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB), DAT);
            break;
        }
        case 1:
        {
            TFT_Write((ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB), DAT);
            break;
        }
        case 2:
        {
            TFT_Write((ST7735_MADCTL_RGB), DAT);
            break;
        }
        case 3:
        {
            TFT_Write((ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB), DAT);
            break;
        }
    }
    
    if((rotation == 0) || (rotation == 2))
    {
        w = TFT_WIDTH;
        l = TFT_LENGTH;
    }
    if((rotation == 1) || (rotation == 3))
    {
        w = TFT_LENGTH;
        l = TFT_WIDTH;
    }
}


void TFT_fill(unsigned int colour)
{
    unsigned int index = pixels;

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
    Draw_Circle(x_pos, y_pos, pen_width, YES, colour);
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
        case YES:
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
         case YES:
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

     if(type != SQUARE)
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
        case YES:
        {
            Draw_Rectangle((x1 + 1), (y1 + 1), (x1 + bar_value), (y1 + bar_width - 1), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle((x2 - 1), (y1 + 1), (x1 + bar_value + 1), (y1 + bar_width - 1), YES, SQUARE, back_colour, back_colour);
            Draw_Rectangle(x1, y1, x2, (y1 + bar_width), NO, SQUARE, border_colour, back_colour);
            break;
        }
        default:
        {
            Draw_Rectangle(x1, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle(x2, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, back_colour, back_colour);
            break;
        }
    }
}


void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border)
{
    switch(border)
    {
        case YES:
        {
            Draw_Rectangle((x1 + 1), (y2 - 1), (x1 + bar_width - 1), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle((x1 + 1), (y2 - bar_value - 1), (x1 + bar_width - 1), (y1 + 1), YES, SQUARE, back_colour, back_colour);
            Draw_Rectangle(x1, y1, (x1 + bar_width), y2, NO, SQUARE, border_colour, back_colour);
            break;
        }
        default:
        {
            Draw_Rectangle(x1, y2, (x1 + bar_width), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle(x1, (y2 - bar_value), (x1 + bar_width), y1, YES, SQUARE, back_colour, back_colour);
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
              case YES:
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
         TFT_write(*bitmap++, DAT);
     }
}