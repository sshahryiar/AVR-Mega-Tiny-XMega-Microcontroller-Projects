#define HX711_DATA          PINC7_bit
#define HX711_SCLK          PORTC6_bit

#define HIGH                1
#define LOW                 0

#define scale_factor        449.0


unsigned long zero_value;


void HX711_init(void);
unsigned long HX711_read(void); 
unsigned long HX711_avg(void);
float HX711_get_mass(void);