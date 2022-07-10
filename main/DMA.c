#include "DMA.h"

int DMA_SPI_MAIN_Init(spi_inst_t* spi_inst, uint spi_DERQ)
{
    int spi_main_mosi_chan = dma_claim_unused_channel(true);

    dma_channel_config spi_main_mosi_chan_config = dma_channel_get_default_config(spi_main_mosi_chan);
    channel_config_set_transfer_data_size(&spi_main_mosi_chan_config, DMA_SIZE_8);
    channel_config_set_read_increment(&spi_main_mosi_chan_config, true);
    channel_config_set_write_increment(&spi_main_mosi_chan_config, false);
    channel_config_set_dreq(&spi_main_mosi_chan_config, spi_DERQ);

    dma_channel_configure(
    spi_main_mosi_chan,
    &spi_main_mosi_chan_config,
    &spi_get_hw(spi_inst)->dr,
    NULL,
    0,
    false
    );

    return spi_main_mosi_chan;
}

bool DMA_SPI_Start_Transfer(int chan, uint8_t* data, uint8_t data_len)
{
    if (!dma_channel_is_busy(chan))
    {
        dma_channel_set_read_addr(chan, data, false);
        dma_channel_set_trans_count(chan, data_len, true);
        return true;
    }
    return false; 
}

