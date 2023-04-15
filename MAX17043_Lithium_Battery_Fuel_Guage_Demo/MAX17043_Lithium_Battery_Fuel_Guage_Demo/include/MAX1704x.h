#include <atmel_start.h>
#include <i2c_master.h>
#include <i2c_simple_master.h>


#define MAX1704x_I2C_ADDRESS		0x36

#define MAX1704x_VCELL_REG			0x02
#define MAX1704x_SOC_REG			0x04
#define MAX1704x_MODE_REG			0x06
#define MAX1704x_VERSION_REG		0x08
#define MAX1704x_CONFIG_REG			0x0C
#define MAX1704x_COMMAND_REG		0xFE

//1.25mV for MAX17043 and 2.50mV for MAX17044
#define V_Scale						1.25  


void MAX1704x_init(void);
void MAX1704x_soft_reset(void);
void MAX1704x_quick_start(void);
unsigned int MAX1704x_get_version(void);
unsigned char MAX1704x_get_compensation_value(void);
unsigned char MAX1704x_get_alert_threshold_value(void);
bool MAX1704x_check_alert_status(void);
void MAX1704x_clear_alert(void);
float MAX1704x_get_cell_voltage(void);
float MAX1704x_get_SOC(void);