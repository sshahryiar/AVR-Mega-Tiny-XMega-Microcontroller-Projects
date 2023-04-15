#define TRUE                           1
#define FALSE                          0

#define SET                            TRUE
#define RESET                          FALSE

#define HIGH                           SET 
#define LOW                            RESET


#define TM1622_CMD_SYS_DIS             0x00    // (0000-0000-X) Turn off system oscillator, LCD bias generator
#define TM1622_CMD_SYS_EN              0x01    // (0000-0001-X) Turn on  system oscillator
#define TM1622_CMD_LCD_OFF             0x02    // (0000-0010-X) Turn off LCD display 
#define TM1622_CMD_LCD_ON              0x03    // (0000-0011-X) Turn on  LCD display
#define TM1622_CMD_TIMER_DIS           0x04    // (0000-0100-X) Disable time base output  
#define TM1622_CMD_WDT_DIS             0x05    // (0000-0101-X) Disable WDT time-out flag output
#define TM1622_CMD_TIMER_EN            0x06    // (0000-0110-X) Enable time base output 
#define TM1622_CMD_WDT_EN              0x07    // (0000-0111-X) Enable WDT time-out flag output
#define TM1622_CMD_TONE_OFF            0x08    // (0000-1000-X) Turn off tone outputs
#define TM1622_CMD_CLR_TIMER           0x0D    // (0000-1101-X) Clear the contents of the time base generator
#define TM1622_CMD_CLR_WDT             0x0F    // (0000-1111-X) Clear the contents of WDT stage          
#define TM1622_CMD_RC_32K              0x18    // (0001-10XX-X) System clock source, on-chip RC oscillator
#define TM1622_CMD_EXT_32K             0x1C    // (0001-11XX-X) System clock source, external clock source
#define TM1622_CMD_TONE_4K             0x40    // (010X-XXXX-X) Tone frequency output: 4kHz
#define TM1622_CMD_TONE_2K             0x60    // (0110-XXXX-X) Tone frequency output: 2kHz
#define TM1622_CMD_IRQ_DIS             0x80    // (100X-0XXX-X) Disable IRQ output
#define TM1622_CMD_IRQ_EN              0x88    // (100X-0XXX-X) Enable IRQ output
#define TM1622_CMD_F1                  0xA0    // (101X-0000-X) Time base clock output: 1Hz, The WDT time-out flag after: 4s
#define TM1622_CMD_F2                  0xA1    // (101X-0001-X) Time base clock output: 2Hz, The WDT time-out flag after: 2s
#define TM1622_CMD_F4                  0xA2    // (101X-0010-X) Time base clock output: 4Hz, The WDT time-out flag after: 1s
#define TM1622_CMD_F8                  0xA3    // (101X-0011-X) Time base clock output: 8Hz, The WDT time-out flag after: 1/2s
#define TM1622_CMD_F16                 0xA4    // (101X-0100-X) Time base clock output: 16Hz, The WDT time-out flag after: 1/4s
#define TM1622_CMD_F32                 0xA5    // (101X-0101-X) Time base clock output: 32Hz, The WDT time-out flag after: 1/8s
#define TM1622_CMD_F64                 0xA6    // (101X-0110-X) Time base clock output: 64Hz, The WDT time-out flag after: 1/16s
#define TM1622_CMD_F128                0xA7    // (101X-0111-X) Time base clock output: 128Hz, The WDT time-out flag after: 1/32s
#define TM1622_CMD_TEST_MODE           0xE0    // (1110-0000-X) Test mode
#define TM1622_CMD_NORMAL_MODE         0xE3    // (1110-0011-X) Normal mode

#define TM1621_CMD_BIAS_COM            0x29    // (0010-10X1-X) 1/3 bias, 4 commons // TM1621 only

#define TM1622_ADDRS                   0x40    // TM1622 has 64 possible 4-bit addresses

#define LSB_FORMAT                     TRUE
#define MSB_FORMAT                     FALSE

#define TM1622_COMMAND_OP_ID           0x04
#define TM1622_WRITE_OP_ID             0x05
#define TM1622_READ_OP_ID              0x06

#define TM1622_no_of_digits            10


#define TM1622_CS_PIN_DIR_OUT          do{DDC0_bit = SET;}while(0)
#define TM1622_WR_PIN_DIR_OUT          do{DDC1_bit = SET;}while(0)
#define TM1622_DAT_PIN_DIR_OUT         do{DDC2_bit = SET;}while(0)

#define TM1622_CS_PIN                  PORTC0_bit
#define TM1622_WR_PIN                  PORTC1_bit
#define TM1622_DAT_PIN                 PORTC2_bit

#define TM1622_CS_PIN_HIGH             do{TM1622_CS_PIN = HIGH;}while(0)     
#define TM1622_WR_PIN_HIGH             do{TM1622_WR_PIN = HIGH;}while(0)     
#define TM1622_DAT_PIN_HIGH            do{TM1622_DAT_PIN = HIGH;}while(0)     

#define TM1622_CS_PIN_LOW              do{TM1622_CS_PIN = LOW;}while(0)     
#define TM1622_WR_PIN_LOW              do{TM1622_WR_PIN = LOW;}while(0)     
#define TM1622_DAT_PIN_LOW             do{TM1622_DAT_PIN = LOW;}while(0)     


void TM162x_init(void);
void TM162x_all_elements_state(unsigned char state);
void TM162x_all_segments_state(unsigned char state);
void TM162x_write_bits(unsigned int value, unsigned char no_of_bits, unsigned char format);
void TM162x_write_command(unsigned char value);
void TM162x_write_data(unsigned char address, unsigned int value, unsigned char no_of_bits);
void TM1622_write_char(unsigned char pos, char ch);
void TM1622_write_str(unsigned char pos, char *ch);
void TM1622_print_custom_char(unsigned char pos, unsigned char char_index);
void TM1622_clear_display(void);