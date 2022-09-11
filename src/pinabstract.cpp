#include "pinabstract.hpp"
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/irq.h>


/* GpioPin class  */
GpioPin::GpioPin(uint pin_no, Direction direction)
{
    dir = direction;
    pin = pin_no;
    bool dire = (dir == OUTPUT) ? true : false;
    gpio_init(pin);
    gpio_set_dir(pin, direction);
}

bool GpioPin::value()
{
    return gpio_get(pin);
}

void GpioPin::value(bool val)
{
    gpio_put(pin, val);
}

/* class PwmPin */
PwmPin::PwmPin(uint pin_i)
{
    pin = pin_i;
    div = 4.f;
    gpio_set_function(pin_i, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(pin_i);
    config = pwm_get_default_config();
}

PwmPin::PwmPin(uint pin_i, float div_i)
{
    pin = pin_i;
    div = div_i;
    gpio_set_function(pin_i, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(pin_i);
    config = pwm_get_default_config();
}

void PwmPin::set_handler(void(*func)())
{
    handler = func;
}

void PwmPin::set_config(pwm_config config_i)
{
    config = config_i;
}

void PwmPin::init()
{
    /*
     * Exit if handler isn't initialized
     * Can't print to stderr because can't be sure if stdio is initialized
     */
    if (handler == NULL)
    {
        return;
    }

    pwm_clear_irq(slice);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, handler);
    pwm_set_irq_enabled(slice, true);
    irq_set_enabled(PWM_IRQ_WRAP, true);
    pwm_config_set_clkdiv(&config, div);
    pwm_init(slice, &config, false);
}

void PwmPin::enable()
{
    pwm_set_enabled(slice, true);
}

void PwmPin::disable()
{
    pwm_set_enabled(slice, false);
}
