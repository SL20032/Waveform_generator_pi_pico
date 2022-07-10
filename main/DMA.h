#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

int DMA_SPI_MAIN_Init(spi_inst_t* spi_inst, uint spi_DERQ);
bool DMA_SPI_Start_Transfer(int chan, uint8_t* data, uint8_t data_len);