#pragma once
#include "hardware/pwm.h"
#include <pico/stdlib.h>

enum Direction { INPUT, OUTPUT };

/*
 * Represents a GPIO pin, can have Input and Output directions
 */
class GpioPin
{
    uint pin;
    Direction dir;

public:
    GpioPin(uint, Direction);
    GpioPin(uint);
    void init();
    void set_dir(Direction);
    void on();
    void off();
    void on(int);
    void off(int);
};

/*
 * Represents a pwm controlled gpio pin
 */
class PwmPin 
{
    uint pin;
    uint slice;
    pwm_config config;
    float div;
    void(*handler)();
    
public:
    PwmPin(uint);
    PwmPin(uint, float);
    void set_handler(void(*)());
    void set_config(pwm_config);
    void build();
    void start_pwd();
};
