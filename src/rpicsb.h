#ifndef _RPICSB_H
#define _RPICSB_H

#include <stdint.h>

#include "gpio.h"

#define RPICSB_RED      22
#define RPICSB_GREEN    27
#define RPICSB_BLUE     17
#define RPICSB_CS        4
#define RPICSB_CLK      11
#define RPICSB_SPO      10

class RPICSB {
private:
    
public:
    static RPICSB get() {
        static RPICSB rpicsb_instance;
	return rpicsb_instance;
    }

    void red();
    void green();
    void blue();

    void set_level(uint8_t level);

    void clear();

private:
    RPICSB();

    void transmit8(uint8_t state);
};

#endif // _RPI_CSB
