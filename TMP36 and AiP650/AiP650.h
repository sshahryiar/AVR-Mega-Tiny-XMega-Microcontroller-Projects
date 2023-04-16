#define LOW                     0
#define HIGH                    1

#define SDA_DDR                 DDC4_bit
#define SCK_DDR                 DDC5_bit

#define SDA_pin                 PORTC4_bit
#define SCK_pin                 PORTC5_bit

#define SDA_in                  PINC4_bit

#define AiP650_NUM_of_DIGITS    0x04

#define AiP650_DISPMODE_4x8     0x01
#define AiP650_DISPMODE_4x7     0x09

#define AiP650_CMD_MODE         0x48
#define AiP650_CMD_DATA_READ    0x49
#define AiP650_CMD_ADDRESS      0x68

#define bit_delay               5


void AiP650_GPIO_init(void);
void AiP650_init(void);
void AiP650_start(void);
void AiP650_stop(void);
void AiP650_write(unsigned char value);
void AiP650_send(unsigned char address, unsigned char value);
void AiP650_clear_display(void);
void AiP650_print_int(signed int value);
void AiP650_print_float(float f_value);