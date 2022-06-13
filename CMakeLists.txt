cmake_minimum_required(VERSION 3.22.3)

set(PICO_SDK_FETCH_FROM_GIT on)
set (CMAKE_CXX_STANDARD 17)
include(pico_sdk_import.cmake)
enable_language(C CXX ASM)
project(main)

pico_sdk_init()

set(SOURCES main.cpp pin.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

pico_add_extra_outputs(main)
target_link_libraries(
    main
    pico_stdlib
    hardware_gpio
    hardware_pwm
)
