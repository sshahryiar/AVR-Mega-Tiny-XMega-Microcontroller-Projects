#include <xc.h>
#include <util/delay.h>


#define LCD_RS_PORT              PORTC
#define LCD_RW_PORT              PORTC
#define LCD_EN_PORT              PORTC

#define LCD_D4_PORT              PORTA
#define LCD_D5_PORT              PORTA       
#define LCD_D6_PORT              PORTA   
#define LCD_D7_PORT              PORTA

#define LCD_RS_PIN               6       
#define LCD_RW_PIN               5  
#define LCD_EN_PIN               7

#define LCD_D4_PIN               4
#define LCD_D5_PIN               5       
#define LCD_D6_PIN               6       
#define LCD_D7_PIN               7      

#define LCD_RS_LOW               LCD_RS_PORT &= ~(1 << LCD_RS_PIN) 
#define LCD_RS_HIGH              LCD_RS_PORT |= (1 << LCD_RS_PIN) 
#define LCD_RW_LOW               LCD_RW_PORT &= ~(1 << LCD_RW_PIN) 
#define LCD_RW_HIGH              LCD_RW_PORT |= (1 << LCD_RW_PIN) 
#define LCD_EN_LOW               LCD_EN_PORT &= ~(1 << LCD_EN_PIN) 
#define LCD_EN_HIGH              LCD_EN_PORT |= (1 << LCD_EN_PIN) 
#define LCD_D4_LOW               LCD_D4_PORT &= ~(1 << LCD_D4_PIN) 
#define LCD_D4_HIGH              LCD_D4_PORT |= (1 << LCD_D4_PIN) 
#define LCD_D5_LOW               LCD_D5_PORT &= ~(1 << LCD_D5_PIN) 
#define LCD_D5_HIGH              LCD_D5_PORT |= (1 << LCD_D5_PIN) 
#define LCD_D6_LOW               LCD_D6_PORT &= ~(1 << LCD_D6_PIN) 
#define LCD_D6_HIGH              LCD_D6_PORT |= (1 << LCD_D6_PIN) 
#define LCD_D7_LOW               LCD_D7_PORT &= ~(1 << LCD_D7_PIN) 
#define LCD_D7_HIGH              LCD_D7_PORT |= (1 << LCD_D7_PIN) 
                                                                                               
#define clear_display            0x01                
#define goto_home                0x02                                                    
         
#define cursor_direction_inc     0x06    
#define cursor_direction_dec     0x04
#define display_shift            0x05 
#define display_no_shift         0x04

#define display_on               0x0C
#define display_off              0x0A       
#define cursor_on                0x0A               
#define cursor_off               0x08        
#define blink_on                 0x09   
#define blink_off                0x08         
                                    
#define _8_pin_interface         0x30   
#define _4_pin_interface         0x20      
#define _2_row_display           0x28 
#define _1_row_display           0x20
#define _5x10_dots               0x60                                                                                        
#define _5x7_dots                0x20 

#define line_1_y_pos             0x00
#define line_2_y_pos             0x40 
#define line_3_y_pos             0x14
#define line_4_y_pos             0x54

#define DAT                      1
#define CMD                      0
                                    
                                                                          
void LCD_init(void);  
void LCD_send(uint8_t value, uint8_t type); 
void LCD_4bit_send(uint8_t lcd_data);                                      
void LCD_putstr(char *lcd_string);               
void LCD_putchar(char char_data);             
void LCD_clear_home(void);            
void LCD_goto(uint8_t x_pos, uint8_t y_pos);
void toggle_EN(void);
