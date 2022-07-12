#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <math.h>

#define PWM_PIN 15

#define PWM_CLK 125000000
#define PWM_MAX_FREQ 100000

void PWM0_Init(void);
void PWM0_enable(void);
void PWM0_disable(void);
void PWM0_set_freq_and_duty(uint32_t target_freq, uint8_t duty);