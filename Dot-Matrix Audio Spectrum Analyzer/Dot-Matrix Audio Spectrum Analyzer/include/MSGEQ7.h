#include <atmel_start.h>


//MSGEQ7_OUT		PORTC.0
//MSGEQ7_RST		PORTC.1
//MSGEQ7_STB		PORTC.2


signed int spectrum_values[7];


void MSGEQ7_init(void);
void read_MSGEQ7(void);