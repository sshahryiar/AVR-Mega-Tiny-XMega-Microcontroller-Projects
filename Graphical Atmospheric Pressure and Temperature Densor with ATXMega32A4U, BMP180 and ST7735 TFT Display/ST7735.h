#include "font.c"


#define CS_pin                                                                           PORTC_OUT.B4
#define RS_pin                                                                           PORTC_OUT.B3
#define RST_pin                                                                          PORTC_OUT.B2

#define ST7735_NOP                                                                       0x00
#define ST7735_SWRESET                                                                   0x01
#define ST7735_RDDID                                                                     0x04
#define ST7735_RDDST                                                                     0x09
#define ST7735_RDDPM                                                                     0x0A
#define ST7735_RDD_MADCTL                                                                0x0B
#define STT7735_RDD_COLMOD                                                               0x0C
#define ST7735_RDDIM                                                                     0x0D
#define ST7735_RDDSM                                                                     0x0E

#define ST7735_SLPIN                                                                     0x10
#define ST7735_SLPOUT                                                                    0x11
#define ST7735_PTLON                                                                     0x12
#define ST7735_NORON                                                                     0x13

#define ST7735_INVOFF                                                                    0x20
#define ST7735_INVON                                                                     0x21
#define ST7735_GAMSET                                                                    0x26
#define ST7735_DISPOFF                                                                   0x28
#define ST7735_DISPON                                                                    0x29
#define ST7735_CASET                                                                     0x2A
#define ST7735_RASET                                                                     0x2B
#define ST7735_RAMWR                                                                     0x2C
#define ST7735_RAMRD                                                                     0x2E

#define ST7735_PTLAR                                                                     0x30
#define ST7735_TEOFF                                                                     0x34
#define ST7735_TEON                                                                      0x35
#define ST7735_MADCTL                                                                    0x36
#define ST7735_IDMOFF                                                                    0x38
#define ST7735_IDMON                                                                     0x39
#define ST7735_COLMOD                                                                    0x3A

#define ST7735_RDID1                                                                     0xDA
#define ST7735_RDID2                                                                     0xDB
#define ST7735_RDID3                                                                     0xDC
#define ST7735_RDID4                                                                     0xDD

#define ST7735_FRMCTR1                                                                   0xB1
#define ST7735_FRMCTR2                                                                   0xB2
#define ST7735_FRMCTR3                                                                   0xB3
#define ST7735_INVCTR                                                                    0xB4
#define ST7735_DISSET5                                                                   0xB6

#define ST7735_PWCTR1                                                                    0xC0
#define ST7735_PWCTR2                                                                    0xC1
#define ST7735_PWCTR3                                                                    0xC2
#define ST7735_PWCTR4                                                                    0xC3
#define ST7735_PWCTR5                                                                    0xC4
#define ST7735_VMCTR1                                                                    0xC5

#define ST7735_RDID1                                                                     0xDA
#define ST7735_RDID2                                                                     0xDB
#define ST7735_RDID3                                                                     0xDC
#define ST7735_RDID4                                                                     0xDD

#define ST7735_PWCTR6                                                                    0xFC

#define ST7735_GMCTRP1                                                                   0xE0
#define ST7735_GMCTRN1                                                                   0xE1

#define ST7735_MADCTL_MY                                                                 0x80
#define ST7735_MADCTL_MX                                                                 0x40
#define ST7735_MADCTL_MV                                                                 0x20
#define ST7735_MADCTL_ML                                                                 0x10
#define ST7735_MADCTL_RGB                                                                0x08
#define ST7735_MADCTL_MH                                                                 0x04

#define White                                                                            0xFFFF
#define Black                                                                            0x0000
#define Grey                                                                             0xF7DE
#define Grey2                                                                            0x8430
#define Light_Grey                                                                       0xC618
#define Dark_Grey                                                                        0x8410
#define Purple                                                                           0xF81F
#define Grey_Blue                                                                        0x5458
#define Blue                                                                             0x001F
#define Dark_Blue                                                                        0x01CF
#define Light_Blue                                                                       0x051F
#define Light_Blue_2                                                                     0x7D7C
#define Red                                                                              0xF800
#define Green                                                                            0x07E0
#define Cyan                                                                             0x7FFF
#define Yellow                                                                           0xFFE0
#define Orange                                                                           0xFC08
#define Magenta                                                                          0xF81F

#define CMD                                                                              0
#define DAT                                                                              1

#define SQUARE                                                                           0
#define ROUND                                                                            1

#define NO                                                                               0
#define YES                                                                              1

#define HIGH                                                                             1
#define LOW                                                                              0

#define TFT_WIDTH                                                                        128
#define TFT_LENGTH                                                                       160

#define X_max                                                                            TFT_WIDTH
#define Y_max                                                                            TFT_LENGTH

#define pixels                                                                           (X_max * Y_max)


unsigned char w = TFT_WIDTH;
unsigned char l = TFT_LENGTH;


void swap(signed int *a, signed int *b);
void setup_TFT_peripherals();
void TFT_Write(unsigned char value, unsigned char mode);
void ST7735_Reset();
void ST7735_init();
void TFT_write_word(unsigned int value);
void TFT_set_display_window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye);
void Invert_Display(unsigned char i);
unsigned int Swap_Colour(unsigned int colour);
unsigned int Color565(unsigned char r, unsigned char g, unsigned char b);
void Set_Rotation(unsigned char m);
void TFT_fill(unsigned int colour);
void TFT_fill_area(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour);
void Draw_Point(unsigned int x_pos, unsigned int y_pos, unsigned char pen_width, unsigned int colour);
void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour);
void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour);
void Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour);
void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour);
void Draw_H_Bar(signed int x1, signed int x2, signed int y1, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour);
void Draw_Font_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour, unsigned char pixel_size);
void print_char(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch);
void print_str(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch);
void print_C(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_I(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_D(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points);
void print_F(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points);
void Draw_BMP(signed int x_pos1, signed int y_pos1, signed int x_pos2, signed int y_pos2, unsigned char *bitmap);