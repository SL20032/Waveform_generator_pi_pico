#include "pico/stdlib.h"
#include "AD9833.h"
#include "PWM.h"
#include "SPI.h"
#include "PCM4251.h"

#define ONBOARD_LED 25
char data_qwe[2] = {0xaa,0xff};


int main() 
{
	SPI_main_init();
	SPI_sec_init();

	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED,true);
	gpio_put(ONBOARD_LED,1);

	/*gpio_put(SPI_SEC_MCP4231_CS,0);
	sleep_ms(1000);
	gpio_put(SPI_SEC_MCP4231_CS,1);*/

	//PWM0_Init();
	//PWM0_set_freq_and_duty(44100,50);
	//PWM0_enable();

	//sleep_ms(260);

	AD9833_Set_Freq(10000,AD9833_SINE);
	sleep_us(100);
	PCM4251_set_potenciometer_position(5,80);

	while (true) {
		/*for (int i = 0; i < 130; i++)
		{	
			PCM4251_set_potenciometer_position(i,25);
			i = i + 9;
			sleep_us(500);
		}*/
		


		//PCM4251_set_potenciometer_position(10,10);
		//sleep_ms(1000);
		//PCM4251_set_potenciometer_position(40,40);
		//sleep_ms(100);
		//PCM4251_set_potenciometer_position(80,80);
		//sleep_ms(100);
		//PCM4251_set_potenciometer_position(120,120);
		//sleep_ms(100);

	}

}