#include "pico/stdlib.h"
#include "SPI.h"

#define AD9833_WRITE_FREQ0      0x4000
#define AD9833_WRITE_FREQ1      0x8000

#define AD9833_D28              0x2000
#define AD9833_RESET            0x100
#define AD9833_ACU_FREQ0        0x00
#define AD9833_ACU_FREQ1        0x800

#define AD9833_SINE             0x00
#define AD9833_TRIG             0x02
#define AD9833_SQER             0x20

void AD9833_Set_Freq(uint32_t freq, uint8_t sig_type);
void AD9833_Enter_reset_mode(void);
void AD9833_Exit_reset_mode(void);
