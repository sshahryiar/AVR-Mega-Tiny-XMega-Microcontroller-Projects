#define MAX44009_address                  0x94
#define MAX44009_Write                    MAX44009_address
#define MAX44009_Read                     (MAX44009_address + 1)

#define INTERRUPT_STATUS_REG              0x00
#define INTERRUPT_ENABLE_REG              0x01
#define CONFIGURATION_REG                 0x02
#define LUX_HIGH_BYTE_REG                 0x03
#define LUX_LOW_BYTE_REG                  0x04
#define UPPER_THRESHOLD_HIGH_BYTE_REG     0x05
#define LOWER_THRESHOLD_HIGH_BYTE_REG     0x06
#define THRESHOLD_TIMER_REG               0x07


void MAX44009_init(void);
void MAX44009_write(unsigned char address, unsigned char value);
unsigned char MAX44009_read_byte(unsigned char address);
unsigned long MAX44009_get_LUX_value(void);