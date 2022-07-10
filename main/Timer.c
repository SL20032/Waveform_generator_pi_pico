#include "Timer.h"

uint32_t SPI_TIMER_period;

void SPI_TIMER_Start(uint32_t period_us, irq_handler_t handler)
{
    hw_set_bits(&timer_hw->inte, 1u << TIMER_SPI_NUM);
    irq_set_exclusive_handler(TIMER_SPI_IRQ, handler);
    irq_set_enabled(TIMER_SPI_IRQ, true);

    //aim the timer
    uint64_t target = timer_hw->timerawl + period_us;
    timer_hw->alarm[TIMER_SPI_NUM] = (uint32_t) target;

    SPI_TIMER_period = period_us;
}

void SPI_TIMER_Kill(void)
{
    hw_clear_bits(&timer_hw->inte, 1u << TIMER_SPI_NUM);    //disenable interrupt generation
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_SPI_NUM);    //clear flag
}

void SPI_TIMER_Repeat(void)
{
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_SPI_NUM);    //clear flag

    //re aim the timer
    uint64_t target = timer_hw->timerawl + SPI_TIMER_period;
    timer_hw->alarm[TIMER_SPI_NUM] = (uint32_t) target;
}