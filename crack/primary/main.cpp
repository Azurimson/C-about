#include "config.h"

int main(int argc, char *argv[])
{
    Config c(argc, argv);
    c.print_parm();
    if (argc != 2 && argc != 5) {
        ;
    } else {
        c.start();
    }
    return 0;
}
