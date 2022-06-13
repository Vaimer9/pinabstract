#include <stdio.h>
#include <pico/stdlib.h>
#include <pico.h>
#include "pin.hpp"

int main(void)
{
    stdio_init_all();
    GpioPin gpio_pin = GpioPin(25);

    gpio_pin.set_dir(OUTPUT);
    gpio_pin.init();

    while (true)
    {
        printf("yeehaaww\n");
        gpio_pin.on(300);
        gpio_pin.off(300);
    }

    return 0;
}
