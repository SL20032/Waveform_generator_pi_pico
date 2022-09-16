#include "pico/stdlib.h"
#include "AD9833.h"
#include "PWM.h"
#include "SPI.h"
#include "UART.h"
#include "PCM4251.h"

#define ONBOARD_LED 25

char Input_arr[10];

int main() 
{
	SPI_main_init();
	SPI_sec_init();
	UART_Init(Input_arr);
	//sei();

	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED,true);
	gpio_put(ONBOARD_LED,1);

	AD9833_Set_Freq(10000,AD9833_SINE);
	sleep_us(100);
	PCM4251_set_potenciometer_position(5,80);

	//UART_Write("bcdgr",5);

	while (true) {
		if(UART_is_new_data_avalible())
		{
			UART_Write(Input_arr,5);
		}
	}
}