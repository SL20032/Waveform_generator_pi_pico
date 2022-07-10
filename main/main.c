#include "pico/stdlib.h"
#include "SPI.h"

#define ONBOARD_LED 25

uint8_t data[8] = {0xaa,0xbb,0xcc,0xdd,0xee,0xff,0xab,0xbc};

int main() 
{
	SPI_main_init();

	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED,true);
	gpio_put(ONBOARD_LED,1);

	while (true) {
		SPI_write_to_AD9833(data,8);
		sleep_ms(250);
	}
}