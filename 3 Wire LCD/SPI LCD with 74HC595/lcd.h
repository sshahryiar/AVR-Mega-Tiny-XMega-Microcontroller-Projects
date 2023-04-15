#define SCK                                     PORTB2_bit
#define SER                                     PORTB3_bit
#define RCK                                     PORTB4_bit

#define clear_display                           0x01
#define goto_home                               0x02
         
#define cursor_direction_inc                    (0x04 | 0x02)
#define cursor_direction_dec                    (0x04 | 0x00)
#define display_shift                           (0x04 | 0x01)
#define display_no_shift                        (0x04 | 0x00)

#define display_on                              (0x08 | 0x04)
#define display_off                             (0x08 | 0x02)
#define cursor_on                               (0x08 | 0x02)
#define cursor_off                              (0x08 | 0x00)
#define blink_on                                (0x08 | 0x01)
#define blink_off                               (0x08 | 0x00)
                                    
#define _8_pin_interface                        (0x20 | 0x10)
#define _4_pin_interface                        (0x20 | 0x00)
#define _2_row_display                          (0x20 | 0x08)
#define _1_row_display                          (0x20 | 0x00)
#define _5x10_dots                              (0x20 | 0x40)
#define _5x7_dots                               (0x20 | 0x00)
                                   
#define dly                                     1

#define CMD                                     0
#define DAT                                     1


sbit Chip_Select at PORTB4_bit;
sbit SoftSpi_CLK at PORTB2_bit;
sbit SoftSpi_SDO at PORTB3_bit;
sbit SoftSpi_SDI at PINB5_bit;

sbit Chip_Select_Direction at DDB4_bit;
sbit SoftSpi_CLK_Direction at DDB2_bit;
sbit SoftSpi_SDO_Direction at DDB3_bit;
sbit SoftSpi_SDI_Direction at DDB5_bit;



unsigned char data_value;
                                    

void SPI_write_value(unsigned char value);
void LCD_init();
void LCD_send(unsigned char value, unsigned char type);
void LCD_4bit_send(unsigned char lcd_data);                                      
void LCD_putstr(char *lcd_string);
void LCD_putchar(char char_data);
void LCD_clear_home();            
void LCD_goto(unsigned char x_pos, unsigned char y_pos);