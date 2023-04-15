#define HIGH                                               1
#define LOW                                                0

#define MAX31855_SS_pin                                    PORTB2_bit

#define MAX31855_SS_pin_HIGH                               MAX31855_SS_pin = HIGH
#define MAX31855_SS_pin_LOW                                MAX31855_SS_pin = LOW

#define no_fault                                           0x00
#define thermocouple_not_detected                          0x01
#define thermocouple_short_circuited_to_GND                0x02
#define thermocouple_short_circuited_to_VCC                0x04


void MAX31855_init(void);
signed long MAX31855_read(void);
unsigned char MAX31855_get_data(float *T_r, float *T_amb);