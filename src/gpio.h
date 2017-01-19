#ifndef _GPIO_H
#define _GPIO_H

#define BCM2708_PERI_BASE       0x20000000
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000) // GPIO_CONTROLLER

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

class GPIO {
private:
    int mem_fd;
    void *gpio_map;

    // I/O access
    volatile unsigned *gpio;

public:
    static GPIO& get() {
        static GPIO gpio_instance;
	return gpio_instance;
    }

    void in(unsigned int g);
    void out(unsigned int g);
    void set_alt(unsigned int g, unsigned int a);

    void set(unsigned int g);
    void unset(unsigned int g);

private:
    GPIO();

    void setup_io();

    GPIO(GPIO const&)           = delete;
    void operator=(GPIO const&) = delete;
};

void setup_io();

#endif //_GPIO_H
