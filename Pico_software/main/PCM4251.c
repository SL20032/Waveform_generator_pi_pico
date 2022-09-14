#include "PCM4251.h"

uint8_t pot_data[2];

void PCM4251_Command_Prep(uint8_t adress, uint8_t rw, uint16_t pot_position)
{
    pot_data[0] = adress | rw | (pot_position & 0x100);
    pot_data[1] = pot_position & 0xFF;
}

void PCM4251_set_potenciometer_position(uint16_t pot0_position, uint16_t pot1_position)
{
    PCM4251_Command_Prep(PCM4251_ADDR_POT0,PCM4251_WRITE,pot0_position);
    SPI_write_to_MCP4231(pot_data,2);
    sleep_us(250);
    PCM4251_Command_Prep(PCM4251_ADDR_POT1,PCM4251_WRITE,pot1_position);
    SPI_write_to_MCP4231(pot_data,2);
}