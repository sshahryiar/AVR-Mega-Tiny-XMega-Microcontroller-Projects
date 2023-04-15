#include <atmel_start.h>
#include <string.h>
#include <util/delay.h>
#include <TM1640.h>
#include <MSGEQ7.h>


float map(float value, float x_mn, float x_mx, float y_mn, float y_mx);


int main(void)
{
	unsigned char c = 0;
	unsigned char h = 0;
	
	atmel_start_init();
	
	MSGEQ7_init();
	TM1640_init(brightness_10_pc);

	while(1)
	{
		read_MSGEQ7();
		
		for(c = 0; c < 7; c++)
		{
			h = (unsigned char)map((float)spectrum_values[c], 0.0, 1023.0, 0.0, 7.0);
			TM1640_draw_line((1 + (c * 2)), 0, (1 + (c * 2)), 7,  NO);
			TM1640_draw_line((1 + (c * 2)), 0, (1 + (c * 2)), h,  YES);
		};
		
		_delay_ms(40);
	};
}


float map(float value, float x_mn, float x_mx, float y_mn, float y_mx)
{
	return (y_mn + (((y_mx - y_mn) / (x_mx - x_mn)) * (value - x_mn)));
}
