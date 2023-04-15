#define number_of_LEDs                          256
#define number_of_bits                          24
#define channels                                3

#define one                                     0xF8
#define zero                                    0xC0

#define HIGH                                    1
#define LOW                                     0

#define ON                                      1
#define OFF                                     0

#define YES                                     1
#define NO                                      0


unsigned char LED_colours[number_of_LEDs][channels];


void swap(signed int *a, signed int *b);
void WS2812_init(void);
void WS2812_update(void);
void WS2812_reset(void);
void WS2812_send_data(unsigned char r, unsigned char g, unsigned char b);
void WS2812_set_common_colour_on_all_LEDs(unsigned char r, unsigned char g, unsigned char b);
void WS2812_set_colour_on_channel(unsigned int channel, unsigned char r, unsigned char g, unsigned char b);
void WS2812_set_colour_xy(signed int x_pos, signed int y_pos, unsigned char r, unsigned char g, unsigned char b);
void WS2812_Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char r, unsigned char g, unsigned char b);
void WS2812_Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned char r, unsigned char g, unsigned char b);
void WS2812_Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned char r, unsigned char g, unsigned char b);
void WS2812_Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char r, unsigned char g, unsigned char b);
void WS2812_Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned char r, unsigned char g, unsigned char b);
void WS2812_Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned char r, unsigned char g, unsigned char b);