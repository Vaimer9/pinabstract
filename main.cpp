#include <pico/stdlib.h>
#include <pico.h>
#include "pin.hpp"

#define PINOUT 25

void on_pwm_wrap() {
    static int fade = 0;
    static bool going_up = true;

    pwm_clear_irq(pwm_gpio_to_slice_num(PINOUT));

    if (going_up) {
        ++fade;
        if (fade > 255) {
            fade = 255;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }
    pwm_set_gpio_level(PINOUT, fade * fade);
}

int main(void)
{
    PwmPin pwm_pin(PINOUT, 4.f);
    pwm_pin.set_handler(on_pwm_wrap);
    pwm_pin.build();
    pwm_pin.start_pwd();

    while (true)
        tight_loop_contents();

    return 0;
}
