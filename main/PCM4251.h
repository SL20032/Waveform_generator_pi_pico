#include "SPI.h"
#include "pico/stdlib.h"

#define PCM4251_WRITE       0x00
#define PCM4251_READ        0x0C

#define PCM4251_ADDR_POT0   0x00
#define PCM4251_ADDR_POT1   0x10

void PCM4251_set_potenciometer_position(uint16_t pot0_position, uint16_t pot1_position);
