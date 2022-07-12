#include "pico/stdlib.h"
#include "AD9833.h"
#include "PWM.h"

#define ONBOARD_LED 25

int main() 
{
	SPI_main_init();

	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED,true);
	gpio_put(ONBOARD_LED,1);

	PWM0_Init();
	PWM0_set_freq_and_duty(44100,50);
	PWM0_enable();

	sleep_ms(250);

	while (true) {
		AD9833_Set_Freq(600,AD9833_SINE);
		sleep_ms(2000);
		AD9833_Set_Freq(12000,AD9833_TRIG);
		sleep_ms(2000);
	}
}