#include "SPI.h"

int SPI_MAIN_DMA_chan = 0;
bool SPI_MAIN_Busy = false;

void TIMER_SPI_handler()
{
    if(!spi_is_busy(SPI_MAIN))
    {
        gpio_put(SPI_MAIN_AD9833_CS,1);
        SPI_MAIN_Busy = false;
        SPI_TIMER_Kill();
    }
    else SPI_TIMER_Repeat();
}

void SPI_main_init(void)
{
    spi_init(SPI_MAIN,SPI_MAIN_FREQ);

    gpio_set_function(SPI_MAIN_MOSI,GPIO_FUNC_SPI);
    gpio_set_function(SPI_MAIN_SCK,GPIO_FUNC_SPI);

    //CS line init
    gpio_init(SPI_MAIN_AD9833_CS);
    gpio_set_dir(SPI_MAIN_AD9833_CS,true);
    gpio_put(SPI_MAIN_AD9833_CS,1);

    SPI_MAIN_DMA_chan = DMA_SPI_MAIN_Init(SPI_MAIN,DMA_SPI_MAIN_DERQ);
}

bool SPI_main_send_data(uint8_t* data, uint8_t data_len)
{
    if (SPI_MAIN_Busy == true) return false;
    else if (!DMA_SPI_Start_Transfer(SPI_MAIN_DMA_chan, data, data_len)) return false;
    else
    {
        SPI_MAIN_Busy = true;
        return true;
    }     
}

void SPI_write_to_AD9833(uint8_t* data, uint8_t data_len)
{
    gpio_put(SPI_MAIN_AD9833_CS,0);
    while(!SPI_main_send_data(data, data_len));
    SPI_TIMER_Start(SPI_MAIN_8_BIT_TIME * data_len,TIMER_SPI_handler);
}






