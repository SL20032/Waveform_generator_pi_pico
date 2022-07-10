#include "pico/stdlib.h"
#include "hardware/irq.h"

#define TIMER_SPI_NUM   0
#define TIMER_SPI_IRQ   TIMER_IRQ_0

void SPI_TIMER_Start(uint32_t period_us, irq_handler_t handler);
void SPI_TIMER_Kill(void);
void SPI_TIMER_Repeat(void);