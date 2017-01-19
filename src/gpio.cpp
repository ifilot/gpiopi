#include "gpio.h"

GPIO::GPIO() {
    this->setup_io();
}

//
// Set up a memory regions to access GPIO
//
void GPIO::setup_io() {
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }
 
   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );
 
   close(mem_fd); //No need to keep mem_fd open after mmap
 
   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }
 
   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
}


void GPIO::in(unsigned int g) {
    *(this->gpio+((g)/10)) &= ~(7<<(((g)%10)*3));
}

void GPIO::out(unsigned int g) {
    *(gpio+((g)/10)) |=  (1<<(((g)%10)*3));
}

void GPIO::set_alt(unsigned int g, unsigned int a) {
    *(this->gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3));
}

void GPIO::set(unsigned int g) {
    *(this->gpio+7) |= (1 << g); // sets   bits which are 1 ignores bits which are 0
}

void GPIO::unset(unsigned int g) {
    *(this->gpio+10) |= (1 << g);  // clears bits which are 1 ignores bits which are 0
}
