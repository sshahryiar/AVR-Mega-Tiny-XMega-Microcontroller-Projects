#define F_CPU 16000000UL

#include <atmel_start.h>
#include <util/delay.h>
#include "WS2812.h"


#define delay1                      90
#define delay2                      60


int main(void)
{
	signed char i = 0;
	signed char j = 0;
	
	atmel_start_init();
	WS2812_init();
	
	while(1)
	{
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 0);
			if(i > 0)
			{
				j = (i - 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 0);
			if(i > 0)
			{
				j = (i - 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 255);
			if(i > 0)
			{
				j = (i - 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 255);
			if(i > 0)
			{
				j = (i - 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 255);
			if(i > 0)
			{
				j = (i - 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 0);
			if(i > 0)
			{
				j = (i - 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 255);
			if(i > 0)
			{
				j = (i - 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		
		WS2812_reset();
		for(i = (number_of_LEDs - 1); i > -1; i--)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 0);
			if(i < (number_of_LEDs - 1))
			{
				j = (i + 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = (number_of_LEDs - 1); i > -1; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 0);
			if(i < (number_of_LEDs - 1))
			{
				j = (i + 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = (number_of_LEDs - 1); i > -1; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 255);
			if(i < (number_of_LEDs - 1))
			{
				j = (i + 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = (number_of_LEDs - 1); i > -1; i--)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 255);
			if(i < (number_of_LEDs - 1))
			{
				j = (i + 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = (number_of_LEDs - 1); i > -1; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 255);
			if(i < (number_of_LEDs - 1))
			{
				j = (i + 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = (number_of_LEDs - 1); i > -1; i--)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 0);
			if(i < (number_of_LEDs - 1))
			{
				j = (i + 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		WS2812_reset();
		for(i = (number_of_LEDs - 1); i > -1; i--)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 255);
			if(i < (number_of_LEDs - 1))
			{
				j = (i + 1);
				WS2812_set_colour_on_channel(j, 0, 0, 0);
			}
			_delay_ms(delay1);
		}
		
		
				
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(2000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 0);
			_delay_ms(delay2);
		}
		_delay_ms(2000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 0);
			_delay_ms(delay2);
		}
		_delay_ms(2000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		
		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		for(i = (number_of_LEDs - 1); i > -1 ; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(1000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 0);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		for(i = (number_of_LEDs - 1); i > -1 ; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(1000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		for(i = (number_of_LEDs - 1); i > -1 ; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(1000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 0, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		for(i = (number_of_LEDs - 1); i > -1 ; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(1000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 0, 255, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		for(i = (number_of_LEDs - 1); i > -1 ; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(1000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 0);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		for(i = (number_of_LEDs - 1); i > -1 ; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(1000);

		WS2812_reset();
		for(i = 0; i < number_of_LEDs; i++)
		{
			WS2812_set_colour_on_channel(i, 255, 255, 255);
			_delay_ms(delay2);
		}
		_delay_ms(2000);
		
		for(i = (number_of_LEDs - 1); i > -1 ; i--)
		{
			WS2812_set_colour_on_channel(i, 0, 0, 0);
			_delay_ms(delay2);
		}
		_delay_ms(1000);
	}
}
