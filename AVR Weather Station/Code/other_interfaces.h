#define wind_pin                                0
#define batt_pin                                6
#define TEMT6000_pin                            7

#define wind_speed_min                          0.0
#define wind_speed_max                          30.0
#define batt_divider_ratio                      4.9
#define nominal_VDD                             3.33
#define min_ADC_count_at_no_wind                39.0
#define max_ADC_count                           1023.0
#define TEMT6000_fixed_resistor_value_in_k_ohms 1.0
#define gain                                    4000.0


#define status_LED                              PORTD4_bit


void other_interfaces_init();
unsigned int ADC_Read(unsigned char channel);
unsigned int adc_avg(unsigned char channel);
float map(float value, float xp_min, float xp_max, float yp_min, float yp_max);
float constrain(float value, float value_min, float value_max);
float get_wind_speed();
float get_bv();
unsigned int get_lux();