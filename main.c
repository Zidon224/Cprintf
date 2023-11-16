#include "Cprintf.h"


int main()
{
    ANSI_RGB_FG(255, 67, 0);
    cprintf("██████████████████░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    ANSI_RST();

    ANSI_XTERM_FG(62);
    cprintf("Colored text");
    ANSI_RST();
}