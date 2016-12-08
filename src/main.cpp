#include <iostream>
#include <unistd.h>

#include "gpio.h"

int main() {
    GPIO gpio;

    for(unsigned int i=0; i<10; i++) {
        gpio.set_pin_high(2);
        usleep(500000);
        gpio.set_pin_low(2);
        gpio.set_pin_high(3);
        usleep(500000);
        gpio.set_pin_low(3);
    }

    return 0;
}
