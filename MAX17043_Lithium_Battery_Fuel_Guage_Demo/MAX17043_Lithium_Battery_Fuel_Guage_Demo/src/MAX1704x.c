#include "MAX1704x.h"


void MAX1704x_init(void)
{
	MAX1704x_soft_reset();
	MAX1704x_quick_start();
}


void MAX1704x_soft_reset(void)
{
	I2C_write2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_COMMAND_REG, 0x0054);
}


void MAX1704x_quick_start(void)
{
	I2C_write2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_MODE_REG, 0x4000);
}


unsigned int MAX1704x_get_version(void)
{
	return I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_VERSION_REG);
}


unsigned char MAX1704x_get_compensation_value(void)
{
	unsigned int value = 0;
	
	value = I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_CONFIG_REG);
	value &= 0xFF00;
	value >>= 0x08;
	
	return ((unsigned char)value);
}


unsigned char MAX1704x_get_alert_threshold_value(void)
{
	return (32 - (unsigned char)(I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_CONFIG_REG) & 0x001F));
}


void MAX1704x_set_alert_threshold_value(unsigned char value)
{
	unsigned int tmp = 0x0000;
	
	tmp = I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_CONFIG_REG);
	
	if(value >= 32)
	{
		value = 32;		
	}
	
	value = (32 - value);
	
	I2C_write2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_CONFIG_REG, ((tmp & 0xFFE0) | value));
}


bool MAX1704x_check_alert_status(void)
{
	unsigned int tmp = 0x0000;
	
	tmp = I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_CONFIG_REG);
	tmp &= 0x0020;
	
	if(tmp != 0)
	{
		return 1;		
	}
	else
	{
		return 0;	
	}
}


void MAX1704x_clear_alert(void)
{
	I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_CONFIG_REG);
}



float MAX1704x_get_cell_voltage(void)
{
	unsigned int tmp = 0x0000;

	tmp = I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_VCELL_REG);	
	tmp >>= 4;
	
	return (float)((float)tmp * V_Scale);
}


float MAX1704x_get_SOC(void)
{
	unsigned char LB = 0x00;
	unsigned char HB = 0x00;
	
	unsigned int tmp = 0x0000;
	float soc = 0.0;
	
	tmp = I2C_read2ByteRegister(MAX1704x_I2C_ADDRESS, MAX1704x_SOC_REG);
	
	LB = (tmp & 0x00FF);
	HB = ((tmp & 0xFF00) >> 0x08);
	
	soc = ((float)LB);
	soc /= 256.0;
	soc += ((float)HB);	
	
	return soc;
}