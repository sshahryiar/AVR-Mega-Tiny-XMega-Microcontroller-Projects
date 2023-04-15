#include "lcd_print.h"


void load_custom_symbol(void)
{
    unsigned char s = 0;

    const unsigned char custom_symbol[array_size] =
    {
        0x00, 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00
    };

    Lcd_Cmd(0x40);

    for(s = 0; s < array_size; s++)
    {
         Lcd_Chr_CP(custom_symbol[s]);
    }

    Lcd_Cmd(0x80);
}


void print_symbol(unsigned char x_pos, unsigned char y_pos, unsigned char symbol_index)
{
    Lcd_Chr(y_pos, x_pos, symbol_index);
}


void print_C(unsigned char x_pos, unsigned char y_pos, signed int value)
{
     char ch[5] = {0x20, 0x20, 0x20, 0x20, '\0'};

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

     Lcd_Out(y_pos, x_pos, ch);
}


void print_I(unsigned char x_pos, unsigned char y_pos, signed long value)
{
    char ch[7] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};

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

    Lcd_Out(y_pos, x_pos, ch);
}


void print_D(unsigned char x_pos, unsigned char y_pos, signed int value, unsigned char points)
{
    char ch[5] = {0x2E, 0x20, 0x20, '\0'};

    ch[1] = ((value / 100) + 0x30);

    if(points > 1)
    {
        ch[2] = (((value / 10) % 10) + 0x30);

        if(points > 1)
        {
            ch[3] = ((value % 10) + 0x30);
        }
    }

    Lcd_Out(y_pos, x_pos, ch);
}


void print_F(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points)
{
    signed long tmp = 0x00000000;

    tmp = value;
    print_I(x_pos, y_pos, tmp);
    tmp = ((value - tmp) * 1000);

    if(tmp < 0)
    {
       tmp = -tmp;
    }

    if(value < 0)
    {
        value = -value;
        Lcd_Chr(y_pos, x_pos, 0x2D);
    }
    else
    {
        Lcd_Chr(y_pos, x_pos, 0x20);
    }

    if((value >= 10000) && (value < 100000))
    {
        print_D((x_pos + 6), y_pos, tmp, points);
    }
    else if((value >= 1000) && (value < 10000))
    {
        print_D((x_pos + 5), y_pos, tmp, points);
    }
    else if((value >= 100) && (value < 1000))
    {
        print_D((x_pos + 4), y_pos, tmp, points);
    }
    else if((value >= 10) && (value < 100))
    {
        print_D((x_pos + 3), y_pos, tmp, points);
    }
    else if(value < 10)
    {
        print_D((x_pos + 2), y_pos, tmp, points);
    }
}