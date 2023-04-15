#include "font.c"


#define TFT_data_out_port_low                                                            PORTC
#define TFT_data_out_port_high                                                           PORTA

#define TFT_data_in_port_low                                                             PINC
#define TFT_data_in_port_high                                                            PINA

#define TFT_port_config_low                                                              DDRC
#define TFT_port_config_high                                                             DDRA

#define TFT_RST_pin                                                                      PORTG0_bit
#define TFT_CS_pin                                                                       PORTG1_bit
#define TFT_WR_pin                                                                       PORTG2_bit
#define TFT_RS_pin                                                                       PORTD7_bit
//TFT_RD_pin pull up 3.3V

#define TFT_RST_pin_dir                                                                  DDG0_bit
#define TFT_CS_pin_dir                                                                   DDG1_bit
#define TFT_WR_pin_dir                                                                   DDG2_bit
#define TFT_RS_pin_dir                                                                   DDD7_bit

#define White                                                                            0xFFFF
#define Black                                                                            0x0000
#define Grey                                                                             0xF7DE
#define Blue                                                                             0x001F
#define Light_Blue                                                                       0x051F
#define Red                                                                              0xF800
#define Magenta                                                                          0xF81F
#define Green                                                                            0x07E0
#define Cyan                                                                             0x7FFF
#define Yellow                                                                           0xFFE0

#define DAT                                                                              1
#define CMD                                                                              0

#define SQUARE                                                                           0
#define ROUND                                                                            1

#define NO                                                                               0
#define YES                                                                              1

#define ON                                                                               1
#define OFF                                                                              0

#define output                                                                           1
#define input                                                                            0

#define high                                                                             1
#define low                                                                              0

#define  MAX_X                                                                           320
#define  MAX_Y                                                                           240



void TFT_init();
void TFT_GPIO_init();
void TFT_reset_sequence();
void TFT_write_word(unsigned int value);
void TFT_write(unsigned int value, unsigned char mode);
void TFT_write_reg(unsigned int cmd_value, unsigned int data_value);
void TFT_set_display_address_window(signed int xs, signed int ys, signed int xe, signed int ye);
void TFT_set_cursor(signed int x_pos, signed int y_pos);
void TFT_fill(unsigned int colour);
unsigned int TFT_BGR2RGB(unsigned int colour);
unsigned int RGB565_converter(unsigned char r, unsigned char g, unsigned char b);
void swap(signed int *a, signed int *b);
void Draw_Pixel(signed int x_pos, signed int y_pos, unsigned int colour);
void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour);
void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour);
void Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour);
void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour);
void Draw_H_Bar(signed int x1, signed int x2, signed int y1, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour);
void Draw_Font_Pixel(unsigned int x_pos, unsigned int y_pos, unsigned int colour, unsigned char pixel_size);
void print_char(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch);
void print_str(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch);
void print_C(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_I(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_D(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value, unsigned char points);
void print_F(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points);
void Draw_BMP(signed int x_pos, signed int y_pos, signed int W, signed int H, const unsigned int *bitmap);