#include "lcd_print.h"


void lcd_str(unsigned char x_pos, unsigned char y_pos, char *ch)
{
    do
     {
         Lcd_Chr(y_pos, x_pos++, *ch++);
     }while((*ch >= 0x20) && (*ch <= 0x7F));
}


void print_C(unsigned char x_pos, unsigned char y_pos, signed int value)
{
     unsigned char ch[4] = {0x20, 0x20, 0x20, 0x20};

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

     lcd_str(x_pos, y_pos, ch);
}


void print_I(unsigned char x_pos, unsigned char y_pos, signed long value)
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

    lcd_str(x_pos, y_pos, ch);
}


void print_L(unsigned char x_pos, unsigned char y_pos, signed long value)
{
    unsigned char ch[8] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

    if(value < 0)
    {
        ch[0] = 0x2D;
        value = -value;
    }
    else
    {
        ch[0] = 0x20;
    }

    if(value > 999999)
    {
        ch[1] = ((value / 1000000) + 0x30);
        ch[2] = (((value % 1000000)/ 100000) + 0x30);
        ch[3] = (((value % 100000) / 10000) + 0x30);
        ch[4] = (((value % 10000) / 1000) + 0x30);
        ch[5] = (((value % 1000) / 100) + 0x30);
        ch[6] = (((value % 100) / 10) + 0x30);
        ch[7] = ((value % 10) + 0x30);
    }
    
    else if((value > 99999) && (value <= 999999))
    {
        ch[1] = ((value / 100000) + 0x30);
        ch[2] = (((value % 100000) / 10000) + 0x30);
        ch[3] = (((value % 10000) / 1000) + 0x30);
        ch[4] = (((value % 1000) / 100) + 0x30);
        ch[5] = (((value % 100) / 10) + 0x30);
        ch[6] = ((value % 10) + 0x30);
        ch[7] = 0x20;
    }
    
    else if((value > 9999) && (value <= 99999))
    {
        ch[1] = ((value / 10000) + 0x30);
        ch[2] = (((value % 10000) / 1000) + 0x30);
        ch[3] = (((value % 1000) / 100) + 0x30);
        ch[4] = (((value % 100) / 10) + 0x30);
        ch[5] = ((value % 10) + 0x30);
        ch[6] = 0x20;
        ch[7] = 0x20;
    }
    
    else if((value > 999) && (value <= 9999))
    {
        ch[1] = ((value / 1000) + 0x30);
        ch[2] = (((value % 1000) / 100) + 0x30);
        ch[3] = (((value % 100) / 10) + 0x30);
        ch[4] = ((value % 10) + 0x30);
        ch[5] = 0x20;
        ch[6] = 0x20;
        ch[7] = 0x20;
    }
    
    else if((value > 99) && (value <= 999))
    {
        ch[1] = ((value / 100) + 0x30);
        ch[2] = (((value % 100) / 10) + 0x30);
        ch[3] = ((value % 10) + 0x30);
        ch[4] = 0x20;
        ch[5] = 0x20;
        ch[6] = 0x20;
        ch[7] = 0x20;
    }
    
    else if((value > 9) && (value <= 99))
    {
        ch[1] = ((value / 10) + 0x30);
        ch[2] = ((value % 10) + 0x30);
        ch[3] = 0x20;
        ch[4] = 0x20;
        ch[5] = 0x20;
        ch[6] = 0x20;
        ch[7] = 0x20;
    }

    else
    {
        ch[1] = ((value % 10) + 0x30);
        ch[2] = 0x20;
        ch[3] = 0x20;
        ch[4] = 0x20;
        ch[5] = 0x20;
    }

    lcd_str(x_pos, y_pos, ch);
}


void print_D(unsigned char x_pos, unsigned char y_pos, signed int value, unsigned char points)
{
    char ch[5] = {0x2E, 0x20, 0x20};

    ch[1] = ((value / 10) + 0x30);

    if(points > 1)
    {
        ch[2] = ((value % 10) + 0x30);
    }

    lcd_str(x_pos, y_pos, ch);
}


void print_F(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points)
{
    signed long tmp = 0x0000;

    tmp = value;
    print_I(x_pos, y_pos, tmp);
    tmp = ((value - tmp) * 100);

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