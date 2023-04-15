#include "MSGEQ7.h"
#include <string.h>
#include <util/delay.h>


void MSGEQ7_init(void)
{
	
	MSGEQ7_STB_set_level(false);
	_delay_ms(1);
	
	MSGEQ7_RST_set_level(true);
	_delay_ms(1);
	
	MSGEQ7_RST_set_level(false);
	MSGEQ7_STB_set_level(true);
	_delay_ms(1);
}


void read_MSGEQ7(void)
{

	unsigned char s = 0;
	
	memset(spectrum_values, 0, sizeof(spectrum_values));
	
	MSGEQ7_RST_set_level(true);
	MSGEQ7_RST_set_level(false);

	for(s = 0; s < 7; s++)
	{
		MSGEQ7_STB_set_level(false);
		_delay_us(23);

		spectrum_values[s] = ADC_0_get_conversion(0);
		
		MSGEQ7_STB_set_level(true);
		_delay_us(1);
	}

}