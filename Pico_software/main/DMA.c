#include "DMA.h"

//------------------------------------------------------------------------------------------------------------------------
//SPI - Write
//------------------------------------------------------------------------------------------------------------------------

int DMA_SPI_TX_Init(spi_inst_t* spi_inst, uint spi_DERQ)
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

//------------------------------------------------------------------------------------------------------------------------
//UART - Write
//------------------------------------------------------------------------------------------------------------------------

int DMA_UART_TX_Init(uart_inst_t * uart_inst, uint uart_tx_DERQ)
{
    int uart_tx_chan = dma_claim_unused_channel(true);

    dma_channel_config uart_tx_chan_config = dma_channel_get_default_config(uart_tx_chan);
    channel_config_set_transfer_data_size(&uart_tx_chan_config, DMA_SIZE_8);
    channel_config_set_read_increment(&uart_tx_chan_config, true);
    channel_config_set_write_increment(&uart_tx_chan_config, false);
    channel_config_set_dreq(&uart_tx_chan_config, uart_tx_DERQ);

    dma_channel_configure(
    uart_tx_chan,
    &uart_tx_chan_config,
    &uart_get_hw(uart_inst)->dr,
    NULL,
    0,
    false
    );

    return uart_tx_chan;
}

bool DMA_UART_TX_Start_Transfer(int chan, uint8_t* data, uint8_t data_len)
{
    if (!dma_channel_is_busy(chan))
    {
        dma_channel_set_read_addr(chan, data, false);
        dma_channel_set_trans_count(chan, data_len, true);
        return true;
    }
    return false; 
}

//------------------------------------------------------------------------------------------------------------------------
//UART - READ
//------------------------------------------------------------------------------------------------------------------------

int DMA_UART_RX_Init(uart_inst_t * uart_inst, uint uart_rx_DERQ, irq_handler_t DMA_finished_handler)
{
    int uart_rx_chan = dma_claim_unused_channel(true);
    
    dma_channel_config uart_rx_dma_chan_config = dma_channel_get_default_config(uart_rx_chan);
    channel_config_set_transfer_data_size(&uart_rx_dma_chan_config, DMA_SIZE_8);
    channel_config_set_read_increment(&uart_rx_dma_chan_config, false);
    channel_config_set_write_increment(&uart_rx_dma_chan_config, true);
    channel_config_set_dreq(&uart_rx_dma_chan_config,DREQ_UART0_RX/*uart_rx_DERQ*/);

    dma_channel_configure(
    uart_rx_chan,
    &uart_rx_dma_chan_config,
    NULL,
    &uart0_hw->dr,//&uart_get_hw(uart_inst)->dr,
    0,
    false
    );

    dma_channel_set_irq0_enabled(uart_rx_chan, true);
    irq_set_exclusive_handler(DMA_IRQ_0,DMA_finished_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    return uart_rx_chan;
}

bool DMA_UART_RX_Start_Transfer(int chan, uint8_t* data_buf, uint8_t number_of_bytes)
{
    if (!dma_channel_is_busy(chan))
    {
        dma_channel_set_write_addr(chan, data_buf, false);
        dma_channel_set_trans_count(chan, number_of_bytes, true);
        return true;
    }
    return false; 
}

//------------------------------------------------------------------------------------------------------------------------
//MEMORY to MEMORY
//------------------------------------------------------------------------------------------------------------------------

int DMA_MEM_to_MEM_Init(void)
{
    int mem_to_mem_chan = dma_claim_unused_channel(true);
    
    dma_channel_config mem_to_mem_chan_config = dma_channel_get_default_config(mem_to_mem_chan);
    channel_config_set_transfer_data_size(&mem_to_mem_chan_config, DMA_SIZE_8);
    channel_config_set_read_increment(&mem_to_mem_chan_config, true);
    channel_config_set_write_increment(&mem_to_mem_chan_config, true);

    dma_channel_configure(
    mem_to_mem_chan,
    &mem_to_mem_chan_config,
    NULL,
    NULL,
    0,
    false
    );

    return mem_to_mem_chan;
}

bool DMA_MEM_to_MEM_Start_Transfer(int chan, uint8_t* data, uint8_t* data_buf, uint8_t data_len)
{
    if (!dma_channel_is_busy(chan))
    {
        dma_channel_set_read_addr(chan, data, false);
        dma_channel_set_write_addr(chan, data_buf, false);
        dma_channel_set_trans_count(chan, data_len, true);
        return true;
    }
    return false; 
}

//------------------------------------------------------------------------------------------------------------------------
//Support func
//------------------------------------------------------------------------------------------------------------------------

bool Is_DMA_chan_IRQ_responsible(int chan)
{
    return dma_channel_get_irq0_status(chan);
}

void DMA_IQR_settings_changer(int enabled_chan, int disabled_chan)
{
    dma_channel_set_irq0_enabled(disabled_chan, false);
    dma_channel_set_irq0_enabled(enabled_chan, true);
}


