#include "PWM.h"

uint PWM0_slice_num = 0;
uint PWM0_chan_num = 0;

void PWM0_Init(void)
{
    //seting gpio func
    gpio_set_function(PWM_PIN,GPIO_FUNC_PWM);

    //PWM config struct
    pwm_config PWM0_config = pwm_get_default_config(); 
    pwm_config_set_clkdiv(&PWM0_config, (float)1);
    pwm_config_set_wrap(&PWM0_config,0xFFFF);
    
    //PWM clock setings (slice)
    PWM0_slice_num = pwm_gpio_to_slice_num(PWM_PIN);    //check witch PWM clock powers gpio pin
	PWM0_chan_num = pwm_gpio_to_channel(PWM_PIN);
    pwm_init(PWM0_slice_num, &PWM0_config, false);

}

void PWM0_enable(void)
{
    pwm_set_enabled(PWM0_slice_num, true);
}

void PWM0_disable(void)
{
    pwm_set_enabled(PWM0_slice_num, false);
}

uint8_t CALC_best_clk_div(uint32_t target_freq)
{
    uint8_t div = 1;
    uint8_t best_div = 0;
    double freq_test = 0;
    double diviation = 0;
    double best_diviation = 0;
    uint32_t pwm_wrap = 0;

    if (target_freq > PWM_MAX_FREQ) target_freq = PWM_MAX_FREQ;    

    for (div = 1;div < 30;div++)
    {
        pwm_wrap = (PWM_CLK / (target_freq * div)) - 1;
        if (pwm_wrap < 65536 && pwm_wrap > 100)
        {
            freq_test = ((double)PWM_CLK / ((pwm_wrap + 1) * div));
            diviation = fabs((double)freq_test - target_freq);
            if (diviation < best_diviation ^ (best_diviation == 0 && best_div == 0))
            {
                best_div = div;
                best_diviation = diviation;
            }
        }  
    }

    return best_div;
}

uint32_t CALC_wrap(uint32_t target_freq, uint8_t div)
{
    uint16_t pwm_wrap;
    if (target_freq > PWM_MAX_FREQ) target_freq = PWM_MAX_FREQ;
    pwm_wrap = (PWM_CLK / (target_freq * div)) - 1;

    return pwm_wrap;
}

/*
*  Function for setting freq and duty of PWM0 
* (duty param values 0 - 100)
* (target freq max 100 000)
*/
void PWM0_set_freq_and_duty(uint32_t target_freq, uint8_t duty)
{
    uint8_t div = CALC_best_clk_div(target_freq);
    uint16_t wrap = CALC_wrap(target_freq, div);
    
    pwm_set_clkdiv(PWM0_slice_num, (float)div);
    pwm_set_wrap(PWM0_slice_num, wrap);
    pwm_set_chan_level(PWM0_slice_num, PWM0_chan_num, (wrap / 100) * duty);
}







