#define bit_set(reg, bit_val)               reg |= (1 << bit_val)
#define bit_clr(reg, bit_val)               reg &= (~(1 << bit_val))
#define bit_tgl(reg, bit_val)               reg ^= (1 << bit_val)
#define get_bit(reg, bit_val)               (reg & (1 << bit_val))
#define get_reg(reg, msk)                   (reg & msk)

#define HIGH		                 1
#define LOW			        0

#define TRUE			        1
#define FALSE			        0

#define YES			        1
#define NO			        0

#define ENABLE			        1
#define DISABLE			        0

#define DHT11_sense_pin                     0
#define DHT11_PORT                          PORTA
#define DHT11_PIN                           PINA
#define DHT11_DIR                           DDRA

#define DHT11_INPUT()                       do{bit_clr(DHT11_PORT, DHT11_sense_pin);\
                                               bit_clr(DHT11_DIR, DHT11_sense_pin);\
                                               }while(0)
                                               
#define DHT11_OUTPUT()                      bit_set(DHT11_DIR, DHT11_sense_pin)

#define DHT11_IN()                          get_bit(DHT11_PIN, DHT11_sense_pin)

#define DHT11_OUT_LOW()                     bit_clr(DHT11_PORT, DHT11_sense_pin)
#define DHT11_OUT_HIGH()                    bit_set(DHT11_PORT, DHT11_sense_pin)


unsigned char values[5];


void DHT11_init(void);
unsigned char get_byte(void);
unsigned char get_data(void);