#define number_of_LEDs                          16
#define number_of_bits                          24


#define one                                     0xF8
#define zero                                    0xC0

#define HIGH                                    1
#define LOW                                     0


unsigned char LED_colours[number_of_LEDs][3];


void WS2812_init();
void WS2812_update();
void WS2812_reset();
void WS2812_set_common_colour_on_all_LEDs(unsigned char r, unsigned char g, unsigned char b);
void WS2812_set_colour_on_channel(unsigned int channel, unsigned char r, unsigned char g, unsigned char b);
void WS2812_send_data(unsigned char r, unsigned char g, unsigned char b);