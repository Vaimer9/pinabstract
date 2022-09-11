cmake_minimum_required(VERSION 3.22.1)

set(PICO_SDK_FETCH_FROM_GIT on)
set (CMAKE_CXX_STANDARD 17)
include(pico_sdk_import.cmake)
# enable_language(C CXX ASM)

project(pinabstract VERSION 1.0.0 DESCRIPTION "Pin abstraction library for raspberry pi pico")

pico_sdk_init()

set(SOURCES
    src/pinabstract.cpp
    src/pinabstract.hpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER pinabstract.h)

target_link_libraries(
    ${PROJECT_NAME}
    pico_stdlib
    hardware_gpio
    hardware_pwm
)
