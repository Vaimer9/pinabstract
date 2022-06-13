#pragma once
#include "hardware/pwm.h"
#include <pico/stdlib.h>

enum Direction { INPUT, OUTPUT };
enum PinType { GPIO, PWM };

/*
 * Represents a normal Pin
 */
class Pin
{
public:
    uint pin;

};

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
    PinType pin_type();
};

/*
 * Represents a pwm controlled gpio pin
 */
class PwmPin 
{
    uint pin;
    uint slice;
    pwm_config* config;
    void(*handler)();
    
public:
    PwmPin(uint);
    void set_handler(void(*)());
    void set_config(pwm_config*);
    void build();
    void start_pwd();
    PinType pin_type();
};

