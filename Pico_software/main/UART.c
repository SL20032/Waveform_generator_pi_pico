#include "UART.h"

int UART_TX_DMA_chan = 0;
int UART_RX_DMA_chan = 0;
int MEM_to_MEM_DMA_chan = 0;

int usart_rx_indeks = 0;
volatile bool uart_frame_ready_flag = false;

static char UART_FRAME_START_BYTES[3] = "AT+";
char UART_INPUT_ARR[10];
char* UART_RX_PROCESSING_ARR;

void uart_rx_handler() 
{
    uint8_t data = uart_getc(UART_ID);

    if (data == UART_FRAME_START_BYTES[usart_rx_indeks])
    {
        usart_rx_indeks++;

        if (usart_rx_indeks > 2)
        {
            usart_rx_indeks = 0;
            uart_set_irq_enables(UART_ID, false, false);
            DMA_UART_RX_Start_Transfer(UART_RX_DMA_chan,UART_INPUT_ARR,7);
        }
        
    }
    else usart_rx_indeks = 0;
}

void uart_dma_handler()
{
    if (Is_DMA_chan_IRQ_responsible(UART_RX_DMA_chan))
    {
        DMA_IQR_settings_changer(MEM_to_MEM_DMA_chan, UART_RX_DMA_chan);
        DMA_MEM_to_MEM_Start_Transfer(MEM_to_MEM_DMA_chan,UART_INPUT_ARR,UART_RX_PROCESSING_ARR,5);
    }
    else
    {
        DMA_IQR_settings_changer(UART_RX_DMA_chan, MEM_to_MEM_DMA_chan);
        uart_frame_ready_flag = true;
        uart_set_irq_enables(UART_ID, true, false);
    }

    // Clear the interrupt request.
    dma_hw->ints0 = 1u << UART_RX_DMA_chan;
}


uint8_t calculate_crc(char* data, unsigned int length)
{
	uint8_t crc = 0;
	crc = 0x3e;  // CRC of three bytes (encoded "AT+")
	for (int i = 0; i < length; i++) {
		crc = (crc ^ data[i]);
	}
	return crc;
}

void UART_Init(char* input_data_bufer)
{
    gpio_set_function(UART_TX_PIN,GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN,GPIO_FUNC_UART);
    
    uart_init(UART_ID, UART_BAUD_RATE);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, UART_DATA_BITS, UART_STOP_BITS, UART_PARITY);
    uart_set_fifo_enabled(UART_ID, false);

    UART_TX_DMA_chan = DMA_UART_TX_Init(UART_ID,UART_TX_DERQ);
    UART_RX_DMA_chan = DMA_UART_RX_Init(UART_ID,UART_RX_DERQ,uart_dma_handler);
    MEM_to_MEM_DMA_chan = DMA_MEM_to_MEM_Init();

    UART_RX_PROCESSING_ARR = input_data_bufer;

    //seting up interrupt - RX Only
    irq_set_exclusive_handler(UART_IRQ, uart_rx_handler);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);

}

bool UART_Write(uint8_t* data, uint8_t data_len)
{
    if (uart_is_writable(UART_ID) == false) return false;
    else if (!DMA_UART_TX_Start_Transfer(UART_TX_DMA_chan, data, data_len)) return false;
    else return true;     
}

bool UART_is_new_data_avalible(void)
{
    bool temp = uart_frame_ready_flag;
    uart_frame_ready_flag = false;
    return temp;
}
