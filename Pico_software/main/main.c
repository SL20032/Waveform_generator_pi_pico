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
	
	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED,true);
	gpio_put(ONBOARD_LED,1);

	AD9833_Set_Freq(100,AD9833_SINE);
	sleep_us(100);
	PCM4251_set_potenciometer_position(5,80);

	while (true) {
		if(UART_is_new_data_avalible())
		{
			//checking CRC
			if (/*calculate_crc(Input_arr,6) == Input_arr[6]*/ true)
			{
				uint32_t temp_freq = Input_arr[3] + (Input_arr[2] << 8) + (Input_arr[1] << 16) + (Input_arr[0] << 24);
				AD9833_Set_Freq(temp_freq,AD9833_SINE);
				PCM4251_set_potenciometer_position(Input_arr[4],Input_arr[5]);	
				UART_Write("OK",2);
				sleep_ms(10);
			}
			else UART_Write("FAIL",4);
		}
	}
}