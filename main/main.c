#include "pico/stdlib.h"
#include "AD9833.h"

#define ONBOARD_LED 25



int main() 
{
	SPI_main_init();

	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED,true);
	gpio_put(ONBOARD_LED,1);
	
	sleep_ms(250);

	while (true) {
		AD9833_Set_Freq(600,AD9833_SINE);
		sleep_ms(2000);
		AD9833_Set_Freq(10000,AD9833_TRIG);
		sleep_ms(2000);
	}
}