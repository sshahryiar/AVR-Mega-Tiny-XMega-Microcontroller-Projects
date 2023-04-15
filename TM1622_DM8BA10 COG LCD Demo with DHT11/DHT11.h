#define TRUE                            1
#define FALSE                           0

#define SET                             TRUE
#define RESET                           FALSE

#define HIGH                            SET
#define LOW                             RESET

#define pin_dly                         6

#define DHT11_PIN                       PORTD0_bit

#define DHT11_PIN_DIR_OUT               do{DDD0_bit = SET; delay_cyc(pin_dly);}while(0)
#define DHT11_PIN_DIR_IN                do{DDD0_bit = RESET; delay_cyc(pin_dly);}while(0)

#define DHT11_PIN_HIGH                  do{DHT11_PIN = HIGH;}while(0)
#define DHT11_PIN_LOW                   do{DHT11_PIN = LOW;}while(0)

#define DHT11_GET_PIN                   PIND0_bit


#define DHT11_normal_state              0
#define DHT11_sensor_error_state        1
#define DHT11_no_sensor_state           2
#define DHT11_checksum_error_state      3


unsigned char values[0x05];


void DHT11_init(void);
unsigned char DHT11_get_byte(void);
unsigned char DHT11_get_data(void);