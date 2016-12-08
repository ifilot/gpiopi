#include "gpio.h"

GPIO::GPIO() {
    this->pin_status.resize(21, PIN_OFF);
}

void GPIO::set_pin_high(unsigned int pin_id) {
    if(pin_id > 20) {
        std::cerr << "Invalid pin number requested, aborting" << std::endl;
        exit(-1);
    }

    this->set_pin_output(pin_id);

    std::string path = "/sys/class/gpio/gpio" + std::to_string(pin_id) + "/value";
    std::ofstream gpiostr(path.c_str());
    if(gpiostr < 0) {
        std::cerr << "Unable to export GPIO" << std::endl;
        exit(-1);
    } else {
        gpiostr << "1";
    }
    gpiostr.close();
}


void GPIO::set_pin_low(unsigned int pin_id) {
    if(pin_id > 20) {
        std::cerr << "Invalid pin number requested, aborting" << std::endl;
        exit(-1);
    }

    this->set_pin_output(pin_id);

    std::string path = "/sys/class/gpio/gpio" + std::to_string(pin_id) + "/value";
    std::ofstream gpiostr(path.c_str());
    if(gpiostr < 0) {
        std::cerr << "Unable to export GPIO" << std::endl;
        exit(-1);
    } else {
        gpiostr << "0";
    }
    gpiostr.close();
}

void GPIO::set_pin_output(unsigned int pin_id) {
    if(pin_id > 20) {
        std::cerr << "Invalid pin number requested, aborting" << std::endl;
        exit(-1);
    }

    switch(this->pin_status[pin_id]) {
        case PIN_OFF:
            this->open_pin(pin_id);
        break;
        case PIN_INPUT:
            std::cerr << "Pin is already set to input, this operation is not allowed." << std::endl;
            exit(-1);
        break;
        case PIN_OUTPUT:
            return;
        break;
    }

    std::string path = "/sys/class/gpio/gpio" + std::to_string(pin_id) + "/direction";
    std::ofstream gpiostr(path.c_str());
    if(gpiostr < 0) {
        std::cerr << "Unable to change direction GPIO" << std::endl;
        exit(-1);
    } else {
        gpiostr << "out";
        this->pin_status[pin_id] = PIN_OUTPUT;
    }
    gpiostr.close();
}

void GPIO::open_pin(unsigned int pin_id) {
    std::string path = "/sys/class/gpio/export";
    std::ofstream gpiostr(path.c_str());
    if(gpiostr < 0) {
        std::cerr << "Unable to export GPIO" << std::endl;
        exit(-1);
    } else {
        gpiostr << pin_id;
        this->pin_status[pin_id] = PIN_ON;
    }
    gpiostr.close();

    // wait some time for pin to be enabled
    usleep(100000); // 100 ms
}

void GPIO::close_pin(unsigned int pin_id) {
    std::string path = "/sys/class/gpio/unexport";
    std::ofstream gpiostr(path.c_str());
    if(gpiostr < 0) {
        std::cerr << "Unable to unexport GPIO" << std::endl;
        exit(-1);
    } else {
        gpiostr << pin_id;
        this->pin_status[pin_id] = PIN_OFF;
    }
    gpiostr.close();
}

GPIO::~GPIO() {
    for(size_t i = 0; i<this->pin_status.size(); i++) {
        if(this->pin_status[i] != PIN_OFF) {
            this->close_pin(i);
        }
    }
}
