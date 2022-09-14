#include "SPI.h"

int SPI_MAIN_DMA_chan = 0;
int SPI_SEC_DMA_chan = 0;
bool SPI_MAIN_Busy = false;
bool SPI_SEC_Busy = false;

void TIMER_SPI_MAIN_handler()
{
    if(!spi_is_busy(SPI_MAIN))
    {
        gpio_put(SPI_MAIN_AD9833_CS,1);
        //gpio_put(SPI_SEC_MCP4231_CS,1);
        SPI_MAIN_Busy = false;
        SPI0_TIMER_Kill();
    }
    else SPI0_TIMER_Repeat();
}

void TIMER_SPI_SEC_handler()
{
    if(!spi_is_busy(SPI_SEC))
    {
        //gpio_put(SPI_MAIN_AD9833_CS,1);
        gpio_put(SPI_SEC_MCP4231_CS,1);
        SPI_SEC_Busy = false;
        SPI1_TIMER_Kill();
    }
    else SPI1_TIMER_Repeat();
}

/*
* Main SPI func
*/

void SPI_main_init(void)
{
    spi_init(SPI_MAIN,SPI_MAIN_FREQ);

    gpio_set_function(SPI_MAIN_MOSI,GPIO_FUNC_SPI);
    gpio_set_function(SPI_MAIN_SCK,GPIO_FUNC_SPI);

    //CS_AD line init
    gpio_init(SPI_MAIN_AD9833_CS);
    gpio_set_dir(SPI_MAIN_AD9833_CS,true);
    gpio_put(SPI_MAIN_AD9833_CS,1);

    //CS_MCP line init/*
    /*gpio_init(SPI_SEC_MCP4231_CS);
    gpio_set_dir(SPI_SEC_MCP4231_CS,true);
    gpio_put(SPI_SEC_MCP4231_CS,1);*/

    SPI_MAIN_DMA_chan = DMA_SPI_TX_Init(SPI_MAIN,DMA_SPI_MAIN_DERQ);
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

/*
* SEC SPI func
*/

void SPI_sec_init(void)
{
    spi_init(SPI_SEC,SPI_SEC_FREQ);

    gpio_set_function(SPI_SEC_MOSI,GPIO_FUNC_SPI);
    gpio_set_function(SPI_SEC_SCK,GPIO_FUNC_SPI);

    //CS line init
    gpio_init(SPI_SEC_MCP4231_CS);
    gpio_set_dir(SPI_SEC_MCP4231_CS,true);
    gpio_put(SPI_SEC_MCP4231_CS,1);

    SPI_SEC_DMA_chan = DMA_SPI_TX_Init(SPI_SEC,DMA_SPI_SEC_DERQ);
}

bool SPI_sec_send_data(uint8_t* data, uint8_t data_len)
{
    if (SPI_SEC_Busy == true) return false;
    else if (!DMA_SPI_Start_Transfer(SPI_SEC_DMA_chan, data, data_len)) return false;
    else
    {
        SPI_SEC_Busy = true;
        return true;
    }     
}

void SPI_write_to_AD9833(uint8_t* data, uint8_t data_len)
{
    gpio_put(SPI_MAIN_AD9833_CS,0);
    while(!SPI_main_send_data(data, data_len));
    SPI0_TIMER_Start(SPI_MAIN_8_BIT_TIME * data_len,TIMER_SPI_MAIN_handler);
}

void SPI_write_to_MCP4231(uint8_t* data, uint8_t data_len)
{
    gpio_put(SPI_SEC_MCP4231_CS,0);
    while(!SPI_sec_send_data(data, data_len));
    SPI1_TIMER_Start(SPI_MAIN_8_BIT_TIME * data_len,TIMER_SPI_SEC_handler);
}






