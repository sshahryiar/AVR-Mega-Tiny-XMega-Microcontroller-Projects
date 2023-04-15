#include "lcd.h"
                              

void LCD_init(void)
{                                                   
    LCD_RW_LOW;
    _delay_ms(2);    
    toggle_EN();
 
    LCD_send(0x33, CMD);
    LCD_send(0x32, CMD);   

    LCD_send((_4_pin_interface | _2_row_display | _5x7_dots), CMD);         
    LCD_send((display_on | cursor_off | blink_off), CMD);     
    LCD_send((clear_display), CMD);         
    LCD_send((cursor_direction_inc | display_no_shift), CMD);           
}   

void LCD_send(uint8_t value, uint8_t type)

{                               
    switch(type)
    {                                                        
      case DAT:                                             
      {
         LCD_RS_HIGH;
         break;
      }
      default:
      {
         LCD_RS_LOW;
         break;
      }
    }
    
    LCD_4bit_send(value);
}  
    

void LCD_4bit_send(uint8_t lcd_data)       
{
    unsigned char temp = 0x00;
	
	temp = (0x01 & (lcd_data >> 0x07));
	
	switch(temp)
	{
		case 1:
		{
			LCD_D7_HIGH;
			break;
		}
		default:
		{
			LCD_D7_LOW;
			break;
		}
	}

    temp = (0x01 & (lcd_data >> 0x06));
	
	switch(temp)
	{
		case 1:
		{
			LCD_D6_HIGH;
			break;
		}
		default:
		{
			LCD_D6_LOW;
			break;
		}
	}

    temp = (0x01 & (lcd_data >> 0x05));           

	switch(temp)
	{
		case 1:
		{
			LCD_D5_HIGH;
			break;
		}
		default:
		{
			LCD_D5_LOW;
			break;
		}
	}

   
    temp = (0x01 & (lcd_data >> 0x04));
    
	switch(temp)
	{
		case 1:
		{
			LCD_D4_HIGH;
			break;
		}
		default:
		{
			LCD_D4_LOW;
			break;
		}
	}   
                                          
    toggle_EN();
    
    temp = (0x01 & (lcd_data >> 0x03));

	switch(temp)
	{
		case 1:
		{
			LCD_D7_HIGH;
			break;
		}
		default:
		{
			LCD_D7_LOW;
			break;
		}
	}


    temp = (0x01 & (lcd_data >> 0x02));

	switch(temp)
	{
		case 1:
		{
			LCD_D6_HIGH;
			break;
		}
		default:
		{
			LCD_D6_LOW;
			break;
		}
	}

    temp = (0x01 & (lcd_data >> 0x01));

	switch(temp)
	{
		case 1:
		{
			LCD_D5_HIGH;
			break;
		}
		default:
		{
			LCD_D5_LOW;
			break;
		}
	}
   
    temp = (0x01 & lcd_data);

	switch(temp)
	{
		case 1:
		{
			LCD_D4_HIGH;
			break;
		}
		default:
		{
			LCD_D4_LOW;
			break;
		}
	}
               
    toggle_EN(); 
}  


void LCD_putstr(char *lcd_string)
{
    while (*lcd_string != '\0')   
    {
        LCD_putchar(*lcd_string++);
    };
}


void LCD_putchar(char char_data) 
{
    LCD_send(char_data, DAT);
}


void LCD_clear_home(void)
{
    LCD_send(clear_display, CMD);
    LCD_send(goto_home, CMD);
}


void LCD_goto(uint8_t x_pos, uint8_t y_pos)
{                                                   
    switch(y_pos)
    {
       case 1:
       {      
           LCD_send((0x80 | (line_2_y_pos + x_pos)), CMD);      
           break;
       }      
       
       case 2:
       {      
           LCD_send((0x80 | (line_3_y_pos + x_pos)), CMD);      
           break;
       }    
       
       case 3:                                    
       {                 
           LCD_send((0x80 | (line_4_y_pos + x_pos)), CMD);      
           break;
       }                      
       
       default:                                  
       {                  
           LCD_send((0x80 | (line_1_y_pos + x_pos)), CMD);      
           break;
       }                 
    }
}


void toggle_EN(void)
{                                                
   LCD_EN_HIGH;
   _delay_ms(2);
   LCD_EN_LOW;
   _delay_ms(2);
}
