#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/dma.h"

#define DMA_IQR_UART_RX DMA_IRQ_0

int DMA_SPI_TX_Init(spi_inst_t* spi_inst, uint spi_DERQ);
bool DMA_SPI_Start_Transfer(int chan, uint8_t* data, uint8_t data_len);

int DMA_UART_TX_Init(uart_inst_t * uart_inst, uint uart_tx_DERQ);
bool DMA_UART_TX_Start_Transfer(int chan, uint8_t* data, uint8_t data_len);

int DMA_UART_RX_Init(uart_inst_t * uart_inst, uint uart_rx_DERQ, irq_handler_t DMA_finished_handler);
bool DMA_UART_RX_Start_Transfer(int chan, uint8_t* data_buf, uint8_t number_of_bytes);

int DMA_MEM_to_MEM_Init(void);
bool DMA_MEM_to_MEM_Start_Transfer(int chan, uint8_t* data, uint8_t* data_buf, uint8_t data_len);

bool Is_DMA_chan_IRQ_responsible(int chan);
void DMA_IQR_settings_changer(int enabled_chan, int disabled_chan);