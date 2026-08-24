cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(blink C CXX ASM)

pico_sdk_init()

add_executable(blink
	main.cc
)

target_link_libraries(blink pico_stdlib)

pico_add_extra_outputs(blink)
