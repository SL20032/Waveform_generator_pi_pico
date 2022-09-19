#include "pico/stdlib.h"
#include "AD9833.h"
#include "PWM.h"
#include "SPI.h"
#include "UART.h"
#include "PCM4251.h"

#include "hardware/uart.h"

#define ONBOARD_LED 25

char Input_arr[10];
char test_arr[10] = {0x41, 0x54, 0x2b, 80, 0, 0, 0, 10, 40, 0xEE};

int main() 
{
	SPI_main_init();
	SPI_sec_init();
	UART_Init(Input_arr);

	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED,true);
	gpio_put(ONBOARD_LED,1);

	AD9833_Set_Freq(1000,AD9833_SINE);
	sleep_us(100);
	PCM4251_set_potenciometer_position(5,80);

	sleep_ms(1000);
	UART_Write(test_arr,10);

	while (true) {
		if(UART_is_new_data_avalible())
		{
			//checking CRC
			if (/*check_crc(Input_arr,6)*/true)
			{
				uint8_t temp_sig_type;

				switch (Input_arr[3])
				{
				case 0:
					temp_sig_type = AD9833_SINE;
					break;
				case 1:
					temp_sig_type = AD9833_TRIG;
					break;
				case 2:
					temp_sig_type = AD9833_SQER;
					break;
				}
				
				AD9833_Set_Freq(Input_arr[2] + (Input_arr[1] << 8) + (Input_arr[0] << 16),temp_sig_type);
				PCM4251_set_potenciometer_position(Input_arr[4],Input_arr[5]);
				UART_Write("OK",2);
			}
			else UART_Write("FAIL",4);
		}
	}
}