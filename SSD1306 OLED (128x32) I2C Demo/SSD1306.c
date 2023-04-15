#include "fonts.c"
#include "SSD1306.h"


void swap(signed int *a, signed int *b)
{
    signed int temp = 0x0000;

    temp = *b;
    *b = *a;
    *a = temp;
}


void OLED_init()
{
     TWI_Init(100000);
     delay_ms(100);

     OLED_write((Set_Display_ON_or_OFF_CMD | Display_OFF), CMD);
     OLED_write(Set_Multiplex_Ratio_CMD, CMD);
     OLED_write(0x1F, CMD);
     OLED_write(Set_Display_Offset_CMD, CMD);
     OLED_write(0x00, CMD);
     OLED_write(Set_Display_Start_Line_CMD, CMD);
     OLED_write((Set_Segment_Remap_CMD | Column_Address_0_Mapped_to_SEG127), CMD);
     OLED_write((Set_COM_Output_Scan_Direction_CMD | Scan_from_COM63_to_0), CMD);
     OLED_write(Set_Common_HW_Config_CMD, CMD);
     OLED_write(0x02, CMD);
     OLED_write(Set_Contrast_Control_CMD, CMD);
     OLED_write(0x8F, CMD);
     OLED_write(Set_Entire_Display_ON_CMD, CMD);
     OLED_write(Set_Normal_or_Inverse_Display_CMD, CMD);
     OLED_write(Set_Display_Clock_CMD, CMD);
     OLED_write(0x80, CMD);
     OLED_write(Set_Pre_charge_Period_CMD, CMD);
     OLED_write(0x25, CMD);
     OLED_write(Set_VCOMH_Level_CMD, CMD);
     OLED_write(0x20, CMD);
     OLED_write(Set_Page_Address_CMD, CMD);
     OLED_write(0x00, CMD);
     OLED_write(0x03, CMD);
     OLED_write(Set_Page_Start_Address_CMD , CMD);
     OLED_write(Set_Higher_Column_Start_Address_CMD, CMD);
     OLED_write(Set_Lower_Column_Start_Address_CMD, CMD);
     OLED_write(Set_Memory_Addressing_Mode_CMD, CMD);
     OLED_write(0x02, CMD);
     OLED_write(Set_Charge_Pump_CMD, CMD);
     OLED_write(0x14, CMD);
     OLED_write((Set_Display_ON_or_OFF_CMD | Display_ON), CMD);
}


void OLED_write(unsigned char value, unsigned char control_byte)
{
     TWI_Start();
     TWI_Write(SSD1306_I2C_Address);
     TWI_Write(control_byte);
     TWI_Write(value);
     TWI_Stop();
}


void OLED_gotoxy(unsigned char x_pos, unsigned char y_pos)
{
     OLED_write((Set_Page_Start_Address_CMD + y_pos), CMD);
     OLED_write(((x_pos & 0x0F) | Set_Lower_Column_Start_Address_CMD), CMD);
     OLED_write((((x_pos & 0xF0) >> 0x04) | Set_Higher_Column_Start_Address_CMD), CMD);
}


void OLED_fill(unsigned char bmp_data)
{
    unsigned char x_pos = 0x00;
    unsigned char page = 0x00;

    for(page = 0; page < y_max; page++)
    {
        OLED_gotoxy(x_min, page);
        
        TWI_Start();
        TWI_Write(SSD1306_I2C_Address);
        TWI_Write(DAT);
        
        for(x_pos = x_min; x_pos < x_max; x_pos++)
        {
           TWI_Write(bmp_data);
        }
        
        TWI_Stop();
    }
}


void OLED_print_Image(const unsigned char *bmp, unsigned char pixel)
{
    unsigned char x_pos = 0;
    unsigned char page = 0;
   
    if(pixel != OFF)
    {
        pixel = 0xFF;
    }
    else
    {
        pixel = 0x00;
    }
   
    for(page = 0; page < y_max; page++)
    {
         OLED_gotoxy(x_min, page);

         TWI_Start();
         TWI_Write(SSD1306_I2C_Address);
         TWI_Write(DAT);

         for(x_pos = x_min; x_pos < x_max; x_pos++)
         {
            TWI_Write((*bmp++ ^ pixel));
         }

         TWI_Stop();
     }
}


void OLED_clear_screen()
{
    OLED_fill(0x00);
}


void OLED_clear_buffer()
{
     unsigned int s = 0x0000;

     for(s = 0; s < buffer_size; s++)
     {
          buffer[s] = 0x00;
     }
}


void OLED_cursor(unsigned char x_pos, unsigned char y_pos)
{
    unsigned char s = 0x00;

    if(y_pos != 0x00)
    {
        if(x_pos == 1)
        {
            OLED_gotoxy(0x00, (y_pos + 0x02));
        }
        else
        {
            OLED_gotoxy((0x50 + ((x_pos - 0x02) * 0x06)), (y_pos + 0x02));
        }

        for(s = 0x00; s < 0x06; s++)
        {
            OLED_write(0xFF, DAT);
        }
    }
}


void OLED_draw_bitmap(unsigned char xb, unsigned char yb, unsigned char xe, unsigned char ye, unsigned char *bmp_img)
{
    unsigned int s = 0x0000;
    unsigned char x_pos = 0x00;
    unsigned char y_pos = 0x00;

    for(y_pos = yb; y_pos <= ye; y_pos++)
    {
        OLED_gotoxy(xb, y_pos);
        for(x_pos = xb; x_pos < xe; x_pos++)
        {
            OLED_write(bmp_img[s++], DAT);
        }
    }
}


void OLED_print_char(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned char ch)
{
    unsigned char chr = 0x00;
    unsigned char s = 0x00;
    
    switch(num_reg_state)
    {
        case NUM:
        {
            if((ch >= 48) && (ch <= 57))
            {
                chr = (ch - 48);
            }
            else
            {
                chr = 10;
            }
            break;
        }
        default:
        {
            chr = (ch - 0x20);
            break;
        }
    }

    if(x_pos > (x_max - 0x06))
    {
        x_pos = 0x00;
        y_pos++;
    }
    OLED_gotoxy(x_pos, y_pos);

    for(s = 0x00; s < 0x06; s++)
    {
        switch(num_reg_state)
        {
            case NUM:
            {
                OLED_write(Number_Font[chr][s], DAT);
                break;
            }
            default:
            {
                OLED_write(font_regular[chr][s], DAT);
                break;
            }
        }
    }
}


void OLED_print_string(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned char *ch)
{
    unsigned char s = 0x00;

    do
    {
        OLED_print_char(x_pos, y_pos, num_reg_state, ch[s++]);
        x_pos += 0x06;
     }while((ch[s] >= 0x20) && (ch[s] <= 0x7F));
}


void OLED_print_chr(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, signed int value)
{
    unsigned char ch = 0x00;

    if(value < 0x00)
    {
        OLED_print_char(x_pos, y_pos, CHR, '-');
        value = -value;
    }
    else
    {
        OLED_print_char(x_pos, y_pos, CHR, ' ');
    }

     if((value >= 100) && (value < 1000))
     {
         ch = (value / 100);
         OLED_print_char((x_pos + 6), y_pos, num_reg_state,  (48 + ch));
         ch = ((value % 100) / 10);
         OLED_print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));
         ch = (value % 10);
         OLED_print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));
     }
     else if((value >= 10) && (value < 100))
     {
         ch = ((value % 100) / 10);
         OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));
         ch = (value % 10);
         OLED_print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));
         OLED_print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
     }
     else if((value >= 0) && (value < 10))
     {
         ch = (value % 10);
         OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));
         OLED_print_char((x_pos + 12), y_pos, num_reg_state, 0x20);
         OLED_print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
     }
}


void OLED_print_int(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, signed long value)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        OLED_print_char(x_pos, y_pos, CHR, '-');
        value = -value;
    }
    else
    {
        OLED_print_char(x_pos, y_pos, CHR, ' ');
    }

    if((value >= 10000) && ((value < 100000)))
    {
        ch = (value / 10000);
        OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 10000)/ 1000);
        OLED_print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 1000) / 100);
        OLED_print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 100) / 10);
        OLED_print_char((x_pos + 24), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        OLED_print_char((x_pos + 30), y_pos, num_reg_state, (48 + ch));
    }

    else if((value >= 1000) && (value < 10000))
    {
        ch = ((value % 10000)/ 1000);
        OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 1000) / 100);
        OLED_print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 100) / 10);
        OLED_print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        OLED_print_char((x_pos + 24), y_pos, num_reg_state, (48 + ch));
        OLED_print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
    else if((value >= 100) && (value < 1000))
    {
        ch = ((value % 1000) / 100);
        OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 100) / 10);
        OLED_print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        OLED_print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));
        OLED_print_char((x_pos + 24), y_pos, num_reg_state, 0x20);
        OLED_print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
    else if((value >= 10) && (value < 100))
    {
        ch = ((value % 100) / 10);
        OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        OLED_print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        OLED_print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
        OLED_print_char((x_pos + 24), y_pos, num_reg_state, 0x20);
        OLED_print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
    else if((value >= 0) && (value < 10))
    {
        ch = (value % 10);
        OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));
        OLED_print_char((x_pos + 12), y_pos, num_reg_state, 0x20);
        OLED_print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
        OLED_print_char((x_pos + 24), y_pos, num_reg_state, 0x20);
        OLED_print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
}


void OLED_print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned int value, unsigned char points)
{
    unsigned char ch = 0x00;

    OLED_print_char(x_pos, y_pos, CHR, '.');

    ch = (value / 1000);
    OLED_print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

    if(points > 1)
    {
        ch = ((value % 1000) / 100);
        OLED_print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));


        if(points > 2)
        {
            ch = ((value % 100) / 10);
            OLED_print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));

            if(points > 3)
            {
                ch = (value % 10);
                OLED_print_char((x_pos + 24), y_pos, num_reg_state, (48 + ch));
            }
        }
    }
}


void OLED_print_float(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, float value, unsigned char points)
{
    signed long tmp = 0x00;

    tmp = value;
    OLED_print_int(x_pos, y_pos, num_reg_state, tmp);
    tmp = ((value - tmp) * 10000);

    if(tmp < 0)
    {
       tmp = -tmp;
    }

    if((value >= 10000) && (value < 100000))
    {
        OLED_print_decimal((x_pos + 36), y_pos, num_reg_state, tmp, points);
    }
    else if((value >= 1000) && (value < 10000))
    {
        OLED_print_decimal((x_pos + 30), y_pos, num_reg_state, tmp, points);
    }
    else if((value >= 100) && (value < 1000))
    {
        OLED_print_decimal((x_pos + 24), y_pos, num_reg_state, tmp, points);
    }
    else if((value >= 10) && (value < 100))
    {
        OLED_print_decimal((x_pos + 18), y_pos, num_reg_state, tmp, points);
    }
    else if(value < 10)
    {
        OLED_print_decimal((x_pos + 12), y_pos, num_reg_state, tmp, points);
        if((value) < 0)
        {
            OLED_print_char(x_pos, y_pos, CHR, '-');
        }
        else
        {
            OLED_print_char(x_pos, y_pos, CHR, ' ');
        }
    }
}


void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned char colour)
{
    unsigned char value = 0x00;
    unsigned char page = 0x00;
    unsigned char bit_pos = 0x00;

    page = (y_pos / y_max);
    bit_pos = (y_pos - (page * y_max));
    value = buffer[((page * x_max) + x_pos)];

    if((colour & YES) != NO)
    {
        value |= (1 << bit_pos);
    }
    else
    {
        value &= (~(1 << bit_pos));
    }

    buffer[((page * x_max) + x_pos)] = value;
    OLED_gotoxy(x_pos, page);
    OLED_write(value, DAT);
}


void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char colour)
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

    dx <<= 1;
    dy <<= 1;

    Draw_Pixel(x1, y1, colour);

    if(dx > dy)
    {
        fraction = (dy - (dx >> 1));
        while (x1 != x2)
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


void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char colour, unsigned char type)
{
     unsigned short i = 0x00;
     unsigned short xmin = 0x00;
     unsigned short xmax = 0x00;
     unsigned short ymin = 0x00;
     unsigned short ymax = 0x00;

     if(fill != NO)
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

     if(type != SQUARE)
     {
         Draw_Pixel(x1, y1, ~colour);
         Draw_Pixel(x1, y2, ~colour);
         Draw_Pixel(x2, y1, ~colour);
         Draw_Pixel(x2, y2, ~colour);
     }
}


void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned char colour)
{
   signed int a = 0x0000;
   signed int b = 0x0000;
   signed int P = 0x0000;

   b = radius;
   P = (1 - b);

   do
   {
        if(fill != NO)
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

        if(P < 0)
        {
           P += (3 + (2 * a++));
        }
        else
        {
           P += (5 + (2 * ((a++) - (b--))));
        }
    }while(a <= b);
}