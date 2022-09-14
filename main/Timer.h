#include "pico/stdlib.h"
#include "hardware/irq.h"

#define TIMER_SPI0_NUM   0
#define TIMER_SPI0_IRQ   TIMER_IRQ_0

#define TIMER_SPI1_NUM   1
#define TIMER_SPI1_IRQ   TIMER_IRQ_1

void SPI0_TIMER_Start(uint32_t period_us, irq_handler_t handler);
void SPI0_TIMER_Kill(void);
void SPI0_TIMER_Repeat(void);

void SPI1_TIMER_Start(uint32_t period_us, irq_handler_t handler);
void SPI1_TIMER_Kill(void);
void SPI1_TIMER_Repeat(void);