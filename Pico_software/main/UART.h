#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "DMA.h"

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define UART_ID         uart0
#define UART_BAUD_RATE  19200
#define UART_DATA_BITS  8
#define UART_STOP_BITS  1
#define UART_PARITY     UART_PARITY_NONE

#define UART_TX_DERQ    DREQ_UART0_TX
#define UART_RX_DERQ    DREQ_UART0_RX
#define UART_IRQ        UART0_IRQ

void UART_Init(char* input_data_bufer);
bool UART_Write(uint8_t* data, uint8_t data_len);
bool UART_is_new_data_avalible(void);