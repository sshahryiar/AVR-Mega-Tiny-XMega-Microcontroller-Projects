#include <atmel_start.h>
#include <avr/pgmspace.h>


//TM1640_DIN    PORTB.0
//TM1640_CLK    PORTB.1

#define HIGH                              true
#define LOW                               false

#define ON                                true
#define OFF                               false

#define YES                               true
#define NO                                false

#define ROUND                             true
#define SQUARE                            false

#define bit_shift_right(val, shift_size)  (val >> shift_size)
#define bit_shift_left(val, shift_size)   (val << shift_size)
#define bit_mask(bit_pos)                 bit_shift_left(1, bit_pos)

#define bit_set(val, bit_val)             (val |= bit_mask(bit_val))
#define bit_clr(val, bit_val)             (val &= (~bit_mask(bit_val)))
#define bit_tgl(val, bit_val)             (val ^= bit_mask(bit_val))

#define auto_address                      0x40
#define fixed_address                     0x44
#define normal_mode                       0x40
#define test_mode                         0x48

#define start_address                     0xC0

#define brightness_5_pc                   0x88
#define brightness_10_pc                  0x89
#define brightness_25_pc                  0x8A
#define brightness_60_pc                  0x8B
#define brightness_70_pc                  0x8C
#define brightness_75_pc                  0x8D
#define brightness_80_pc                  0x8E
#define brightness_100_pc                 0x8F
#define display_off                       0x80
#define display_on                        0x8F

#define x_size                            16
#define x_max                             x_size
#define x_min                             0
#define y_size                            8
#define y_max                             y_size
#define y_min                             0


unsigned char buffer[16];


void TM1640_init(unsigned char brightness_level);
void TM1640_write(unsigned char value);
void TM1640_send_command(unsigned char value);
void TM1640_send_data(unsigned char address, unsigned char value);
void TM1640_clear_display(void);
void TM1640_draw_pixel(unsigned char x_pos, unsigned char y_pos, unsigned char state);
void TM1640_draw_line(signed char x1, signed char y1, signed char x2, signed char y2, unsigned char colour);
void TM1640_draw_rectangle(signed char x1, signed char y1, signed char x2, signed char y2, unsigned char fill, unsigned char colour, unsigned char type);
void TM1640_draw_circle(signed char xc, signed char yc, signed char radius, unsigned char fill, unsigned char colour);
void TM1640_print_char(unsigned char x_pos, unsigned char y_pos, unsigned char ch);
void TM1640_print_string(unsigned char x_pos, unsigned char y_pos, unsigned char *ch);
void TM1640_print_chr(unsigned char x_pos, unsigned char y_pos, signed int value);
void TM1640_print_int(unsigned char x_pos, unsigned char y_pos, signed long value);