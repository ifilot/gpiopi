
#include "rpicsb.h"

int main() {

    RPICSB::get().clear();

    RPICSB::get().red();
    RPICSB::get().set_level(100);

    return 0;
}
