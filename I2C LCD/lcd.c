#include "lcd.h"


void LCD_init()
{
    PCF8574_init();

    bl_state = BL_ON;
    data_value = 0x04;
    PCF8574_write(data_value);
    
    data_value = 0x1A;
    while(data_value > 0x00)
    {
            delay_ms(dly);
            data_value--;
    };

    data_value = 0x30;
    PCF8574_write(data_value);

    data_value |= 0x04;
    PCF8574_write(data_value);
    delay_ms(dly);
    data_value &= 0xF1;
    PCF8574_write(data_value);
    delay_ms(dly);

    data_value = 0x30;
    PCF8574_write(data_value);

    data_value |= 0x04;
    PCF8574_write(data_value);
    delay_ms(dly);
    data_value &= 0xF1;
    PCF8574_write(data_value);
    delay_ms(dly);

    data_value = 0x30;
    PCF8574_write(data_value);

    data_value |= 0x04;
    PCF8574_write(data_value);
    delay_ms(dly);
    data_value &= 0xF1;
    PCF8574_write(data_value);
    delay_ms(dly);

    data_value = 0x20;
    PCF8574_write(data_value);

    data_value |= 0x04;
    PCF8574_write(data_value);
    delay_ms(dly);
    data_value &= 0xF1;
    PCF8574_write(data_value);
    delay_ms(dly);

    LCD_send((_4_pin_interface | _2_row_display | _5x7_dots), CMD);
    LCD_send((display_on | cursor_off | blink_off), CMD);
    LCD_send((clear_display), CMD);
    LCD_send((cursor_direction_inc | display_no_shift), CMD);
}


void LCD_send(unsigned char value, unsigned char control_type)
{
    switch(control_type)
    {
       case CMD:
       {
            data_value &= 0xF4;
            break;
       }
       case DAT:
       {
           data_value |= 0x01;
           break;
       }
    }
    
    switch(bl_state)
    {
       case BL_ON:
       {
          data_value |= 0x08;
          break;
       }
       case BL_OFF:
       {
          data_value &= 0xF7;
          break;
       }
    }
    
    PCF8574_write(data_value);
    LCD_4bit_send(value);
    delay_ms(10);
}


void LCD_4bit_send(unsigned char lcd_data)
{
    unsigned char temp = 0x00;

    temp = (lcd_data & 0xF0);
    data_value &= 0x0F;
    data_value |= temp;
    PCF8574_write(data_value);

    data_value |= 0x04;
    PCF8574_write(data_value);
    delay_ms(dly);
    data_value &= 0xF9;
    PCF8574_write(data_value);
    delay_ms(dly);

    temp = (lcd_data & 0x0F);
    temp <<= 0x04;
    data_value &= 0x0F;
    data_value |= temp;
    PCF8574_write(data_value);

    data_value |= 0x04;
    PCF8574_write(data_value);
    delay_ms(dly);
    data_value &= 0xF9;
    PCF8574_write(data_value);
    delay_ms(dly);
}


void LCD_putstr(char *lcd_string)
{
    while(*lcd_string != '\0')
    {
        LCD_send((*lcd_string++), DAT);
    };
}


void LCD_putchar(char char_data)
{
    LCD_send(char_data, DAT);
}


void LCD_clear_home()
{
    LCD_send(clear_display, CMD);
    LCD_send(goto_home, CMD);
}


void LCD_goto(unsigned char x_pos,unsigned char y_pos)
{
   unsigned char address = 0;

   switch(y_pos) 
   {
     case 1: 
     {
          address = 0x80;
          break;
     }
     case 2: 
     {
          address = 0xC0;
          break;
     }
     case 3: 
     {
          address = 0x94;
          break;
     }
     case 4: 
     {
          address = 0xD4;
          break;
     }
   }
   address += (x_pos - 1);
   lcd_send(address, CMD);
}