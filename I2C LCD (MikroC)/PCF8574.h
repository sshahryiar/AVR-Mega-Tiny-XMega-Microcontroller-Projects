sbit Soft_I2C_Scl_Output    at PORTB3_bit;
sbit Soft_I2C_Sda_Output    at PORTB4_bit;
sbit Soft_I2C_Scl_Input     at PINB3_bit;
sbit Soft_I2C_Sda_Input     at PINB4_bit;
sbit Soft_I2C_Scl_Direction at DDB3_bit;
sbit Soft_I2C_Sda_Direction at DDB4_bit;


#define PCF8574_address 		0x40

#define PCF8574_write_cmd		PCF8574_address
#define PCF8574_read_cmd		(PCF8574_address + 1)


unsigned char PCF8574_read();
void PCF8574_write(unsigned char data_byte);