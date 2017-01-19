#include "gpio.h"

int main() {
    // Set up gpi pointer for direct register access

    // pin setup
    // 17 : BLUE
    // 27 : GREEN
    // 22 : RED

    GPIO::get().in(17);
    GPIO::get().in(27);
    GPIO::get().in(22);

    GPIO::get().out(17);
    GPIO::get().out(27);
    GPIO::get().out(22);

    GPIO::get().set(17);


    return 0;
}
