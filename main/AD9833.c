#include "AD9833.h"

uint8_t  sig_type_global = 0;
uint8_t  data[8];

uint32_t AD9833_Calc_FREQ_REG_value(uint32_t freq)
{
    double temp = 10.73741824 * freq;
    return (uint32_t)temp;
}

void AD9833_Comand_prep(uint32_t FREQ_REG, uint8_t sig_type)
{
    uint16_t temp[4];

    temp[0] = AD9833_D28 | AD9833_ACU_FREQ0 | AD9833_RESET | sig_type_global;
    temp[1] = AD9833_WRITE_FREQ0 | (FREQ_REG & 0x3FFF);
    temp[2] = AD9833_WRITE_FREQ0 | (FREQ_REG >> 14);
    temp[3] = AD9833_D28 | AD9833_ACU_FREQ0 | sig_type;

    sig_type_global = sig_type;

    uint8_t indeks = 0;
    for (uint8_t i = 0; i < 4; i++)
    {
        data[indeks] = (temp[i] >> 8);
        data[indeks + 1] = (temp[i] & 0xFF);
        indeks += 2;
    }
    
}

void AD9833_Set_Freq(uint32_t freq, uint8_t sig_type)
{
    AD9833_Comand_prep(AD9833_Calc_FREQ_REG_value(freq), sig_type);
    SPI_write_to_AD9833(data,8);
}

void AD9833_Enter_reset_mode(void)
{
    uint8_t temp[2] = {
        (AD9833_ACU_FREQ0 | sig_type_global | AD9833_RESET) >> 8,
        (AD9833_ACU_FREQ0 | sig_type_global | AD9833_RESET) & 0xFF
    };
    
    SPI_write_to_AD9833(temp,2);
}

void AD9833_Exit_reset_mode(void)
{
    uint8_t temp[2] = {
        (AD9833_ACU_FREQ0 | sig_type_global) >> 8,
        (AD9833_ACU_FREQ0 | sig_type_global) & 0xFF
    };
    
    SPI_write_to_AD9833(temp,2);
}