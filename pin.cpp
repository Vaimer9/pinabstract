#include "pin.hpp"
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/irq.h>

/* class GpioPin */
GpioPin::GpioPin(uint pin_no, Direction direction)
{
    dir = direction;
    pin = pin_no;
}

GpioPin::GpioPin(uint pin_no)
{
    dir = OUTPUT;
    pin = pin_no;
}

void GpioPin::set_dir(Direction dir_i)
{
    dir = dir_i;
}

void GpioPin::init()
{
    bool direction = (dir == OUTPUT) ? true : false;    
    gpio_init(pin);
    gpio_set_dir(pin, direction);
}

void GpioPin::on()
{
    gpio_put(pin, true);
}

void GpioPin::off()
{
    gpio_put(pin, false);
}

void GpioPin::on(int delay)
{
    gpio_put(pin, true);
    sleep_ms(delay);
}

void GpioPin::off(int delay)
{
    gpio_put(pin, false);
    sleep_ms(delay);
}

PinType GpioPin::pin_type()
{
    return GPIO;
}

/* class PwmPin */
PwmPin::PwmPin(uint pin_i)
{
    pin = pin_i;
    gpio_set_function(pin_i, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(pin_i);
}

void PwmPin::set_handler(void(*func)())
{
    handler = func;
}

void PwmPin::set_config(pwm_config* config_i)
{
    config = config_i;
}

void PwmPin::build()
{
    pwm_clear_irq(slice);
    pwm_set_irq_enabled(slice, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, handler);
    irq_set_enabled(PWM_IRQ_WRAP, true);
}

void PwmPin::start_pwd()
{
    pwm_config_set_clkdiv(config, 4.f);
    pwm_init(slice, config, true);
}

PinType PwmPin::pin_type()
{
    return PWM;
}
