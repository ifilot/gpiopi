#include "rpicsb.h"

RPICSB::RPICSB() {
    // initialize GPIO
    GPIO::get().in(17);
    GPIO::get().in(27);
    GPIO::get().in(22);
    GPIO::get().in(4);
    GPIO::get().in(11);
    GPIO::get().in(10);

    GPIO::get().out(17);
    GPIO::get().out(27);
    GPIO::get().out(22);
    GPIO::get().out(4);
    GPIO::get().out(11);
    GPIO::get().out(10);
}

void RPICSB::red() {
	GPIO::get().unset(RPICSB_RED);
}

void RPICSB::green() {
	GPIO::get().unset(RPICSB_GREEN);
}

void RPICSB::blue() {
	GPIO::get().unset(RPICSB_BLUE);
}

void RPICSB::clear() {
    GPIO::get().set(RPICSB_RED);
    GPIO::get().set(RPICSB_GREEN);
    GPIO::get().set(RPICSB_BLUE);
    this->set_level(0);
}

void RPICSB::set_level(uint8_t level) {
    GPIO::get().unset(RPICSB_CS);
    // transmit command byte
    this->transmit8(0);
    // transmit data byte
    this->transmit8(level);
    GPIO::get().set(RPICSB_CS);
}

void RPICSB::transmit8(uint8_t state) {
    for(int i=7; i>=0; i--) {
        GPIO::get().unset(RPICSB_CLK);  // set clock low
        if(state & (1 << i)) {
            GPIO::get().set(RPICSB_SPO);
	} else {
            GPIO::get().unset(RPICSB_SPO);
	}
	GPIO::get().set(RPICSB_CLK);    // set clock high
    }
}
