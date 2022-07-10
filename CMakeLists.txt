cmake_minimum_required(VERSION 3.12)

set (ENV{PICO_SDK_PATH} "C:/Tools/pi/pico/pico-sdk")
set (ENV{PICO_TOOLCHAIN_PATH} "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.07/bin")

include(pico_sdk_import.cmake)

enable_language( C CXX ASM )
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(AD9833)

pico_sdk_init()

add_subdirectory(main)