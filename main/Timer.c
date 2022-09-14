#include "Timer.h"

uint32_t SPI0_TIMER_period;
uint32_t SPI1_TIMER_period;

void SPI0_TIMER_Start(uint32_t period_us, irq_handler_t handler)
{
    hw_set_bits(&timer_hw->inte, 1u << TIMER_SPI0_NUM);
    irq_set_exclusive_handler(TIMER_SPI0_IRQ, handler);
    irq_set_enabled(TIMER_SPI0_IRQ, true);

    //aim the timer
    uint64_t target = timer_hw->timerawl + period_us;
    timer_hw->alarm[TIMER_SPI0_NUM] = (uint32_t) target;

    SPI0_TIMER_period = period_us;
}

void SPI0_TIMER_Kill(void)
{
    hw_clear_bits(&timer_hw->inte, 1u << TIMER_SPI0_NUM);    //disenable interrupt generation
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_SPI0_NUM);    //clear flag
}

void SPI0_TIMER_Repeat(void)
{
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_SPI0_NUM);    //clear flag

    //re aim the timer
    uint64_t target = timer_hw->timerawl + SPI0_TIMER_period;
    timer_hw->alarm[TIMER_SPI0_NUM] = (uint32_t) target;
}

void SPI1_TIMER_Start(uint32_t period_us, irq_handler_t handler)
{
    hw_set_bits(&timer_hw->inte, 1u << TIMER_SPI1_NUM);
    irq_set_exclusive_handler(TIMER_SPI1_IRQ, handler);
    irq_set_enabled(TIMER_SPI1_IRQ, true);

    //aim the timer
    uint64_t target = timer_hw->timerawl + period_us;
    timer_hw->alarm[TIMER_SPI1_NUM] = (uint32_t) target;

    SPI1_TIMER_period = period_us;
}

void SPI1_TIMER_Kill(void)
{
    hw_clear_bits(&timer_hw->inte, 1u << TIMER_SPI1_NUM);    //disenable interrupt generation
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_SPI1_NUM);    //clear flag
}

void SPI1_TIMER_Repeat(void)
{
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_SPI1_NUM);    //clear flag

    //re aim the timer
    uint64_t target = timer_hw->timerawl + SPI1_TIMER_period;
    timer_hw->alarm[TIMER_SPI1_NUM] = (uint32_t) target;
}