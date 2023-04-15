#include "lcd.h"


void SPI_write_value(unsigned char value)
{
     Chip_Select = 0;
     Soft_SPI_Write(value);
     Chip_Select = 1;
}


void LCD_init()
{                                     
    unsigned char t = 0x0A;
    
    Chip_Select = 1;
    Chip_Select_Direction = 1;
    Soft_SPI_Init();
    delay_ms(10);

    data_value = 0x08;
    SPI_write_value(data_value);
    while(t > 0x00)
    {   
            delay_ms(dly);
            t--;
    };      
    
    data_value = 0x30;
    SPI_write_value(data_value);
                              
    data_value |= 0x08;
    SPI_write_value(data_value);
    delay_ms(dly);
    data_value &= 0xF7;
    SPI_write_value(data_value);
    delay_ms(dly); 
             
    data_value = 0x30;
    SPI_write_value(data_value);
                    
    data_value |= 0x08;
    SPI_write_value(data_value);
    delay_ms(dly);
    data_value &= 0xF7;
    SPI_write_value(data_value);
    delay_ms(dly);

    data_value = 0x30;
    SPI_write_value(data_value);

    data_value |= 0x08;
    SPI_write_value(data_value);
    delay_ms(dly);
    data_value &= 0xF7;
    SPI_write_value(data_value);
    delay_ms(dly);

    data_value = 0x20;
    SPI_write_value(data_value);
                    
    data_value |= 0x08;
    SPI_write_value(data_value);
    delay_ms(dly);
    data_value &= 0xF7;
    SPI_write_value(data_value);
    delay_ms(dly);

    LCD_send((_4_pin_interface | _2_row_display | _5x7_dots), CMD);
    LCD_send((display_on | cursor_off | blink_off), CMD);
    LCD_send((clear_display), CMD);
    LCD_send((cursor_direction_inc | display_no_shift), CMD);
}   


void LCD_send(unsigned char value, unsigned char type)
{                               
    switch(type)
    {
        case DAT:
        {
            data_value |= 0x04;
            break;
        }
        
        case CMD:
        {
             data_value &= 0xFB;
             break;
        }
    }

    SPI_write_value(data_value);
    LCD_4bit_send(value);
}  
    

void LCD_4bit_send(unsigned char lcd_data)       
{
    unsigned char temp = 0x00;
    
    temp = (lcd_data & 0xF0);
    data_value &= 0x0F;
    data_value |= temp;
    SPI_write_value(data_value);
                                          
    data_value |= 0x08;
    SPI_write_value(data_value);
    delay_ms(dly);
    data_value &= 0xF7;
    SPI_write_value(data_value);
    delay_ms(dly);

    temp = (lcd_data & 0x0F);
    temp <<= 0x04;
    data_value &= 0x0F;
    data_value |= temp;
    SPI_write_value(data_value);
               
    data_value |= 0x08;
    SPI_write_value(data_value);
    delay_ms(dly);
    data_value &= 0xF7;
    SPI_write_value(data_value);
    delay_ms(dly);
}  


void LCD_putstr(char *lcd_string)
{
    while (*lcd_string != '\0')   
    {
        LCD_send(*lcd_string, DAT);
        lcd_string++;
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
    if(y_pos == 0)    
    {                              
        LCD_send((0x80 | x_pos), CMD);
    }
    else 
    {                                              
        LCD_send((0x80 | 0x40 | x_pos), CMD);
    }
}