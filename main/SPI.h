#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "DMA.h"
#include "Timer.h"

#define SPI_MAIN            spi1
#define SPI_MAIN_FREQ       100000
#define DMA_SPI_MAIN_DERQ   DREQ_SPI1_TX

#define SPI_MAIN_MOSI       15
#define SPI_MAIN_SCK        14

#define SPI_MAIN_AD9833_CS  13

#define SPI_SEC             spi0
#define SPI_SEC_FREQ        100000
#define DMA_SPI_SEC_DERQ    DREQ_SPI0_TX

#define SPI_SEC_MOSI        19
#define SPI_SEC_SCK         18

#define SPI_SEC_MCP4231_CS  17


#define SPI_MAIN_8_BIT_TIME 90
#define SPI_SEC_8_BIT_TIME  90

bool SPI_main_send_data(uint8_t* data, uint8_t data_len);

void SPI_main_init(void);
void SPI_write_to_AD9833(uint8_t* data, uint8_t data_len);

void SPI_sec_init(void);
void SPI_write_to_MCP4231(uint8_t* data, uint8_t data_len);