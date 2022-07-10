add_executable(main
         main.c
         DMA.c
         SPI.c
         AD9833.c
         Timer.c
         )

 # Import pico_stdlib which imports commonly used features
 target_link_libraries(main pico_stdlib hardware_spi hardware_dma hardware_irq)

 # Create map/bin/hex file etc.
 pico_add_extra_outputs(main)
