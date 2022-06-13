#include <pico/stdlib.h>
#include <pico.h>
#include "pin.hpp"

int main(void)
{
    GpioPin gpio_pin = GpioPin(25);
    gpio_pin.init();

    while (true)
    {
        gpio_pin.on(300);
        gpio_pin.off(300);
    }

    return 0;
}
