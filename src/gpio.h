#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

class GPIO {

private:
    enum {
        PIN_OFF,
        PIN_ON,
        PIN_OUTPUT,
        PIN_INPUT
    };

    std::vector<uint8_t> pin_status;    // track pin status

public:
    GPIO();

    void set_pin_high(unsigned int pin_id);
    void set_pin_low(unsigned int pin_id);

    void set_pin_input(unsigned int pin_id);
    void set_pin_output(unsigned int pin_id);

    ~GPIO();

private:
    void open_pin(unsigned int pin_id);
    void close_pin(unsigned int pin_id);

};

#endif //_GPIO_H
