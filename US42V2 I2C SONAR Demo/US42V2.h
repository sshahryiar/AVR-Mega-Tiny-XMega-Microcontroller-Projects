#define I2C_bus_speed                                     20000

#define US42V2_default_I2C_address                        0xE0

#define US42V2_get_range_cmd                              0x51
#define US42V2_change_address_unlock_1_cmd                0xAA        
#define US42V2_change_address_unlock_2_cmd                0xA5                                                                        


void US42V2_init(void);
unsigned int US42V2_get_distance(unsigned char slave_address);
void US42V2_change_slave_address(unsigned char old_slave_address, unsigned char new_slave_address);