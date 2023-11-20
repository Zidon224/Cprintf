#include "Cprintf2.h"


int main()
{
    cprintf("#c██████████████████#x");
    cprintf("#b░░░░░░░░░░░░░░░░░░░░░░░░░#x\n");
    cprintf("#rStuff#x\n");
    cprintf("#gStuff#x\n");
    cprintf("#yStuff#x\n");
    cprintf("#bStuff#x\n");
    cprintf("#mStuff#x\n");
    cprintf("#cStuff#x\n");
    cprintf("#wStuff#x\n");
    //cprintf("#dStuff#x\n");

    cprintf("$rStuff$x\n");
    cprintf("$gStuff$x\n");
    cprintf("$yStuff$x\n");
    cprintf("$bStuff$x\n");
    cprintf("$mStuff$x\n");
    cprintf("$cStuff$x\n");
    cprintf("$wStuff$x\n");
    cprintf("$dStuff$x\n");

    cprintf("&rStuff&x\n");
    cprintf("&gStuff&x\n");
    cprintf("&yStuff&x\n");
    cprintf("&bStuff&x\n");
    cprintf("&mStuff&x\n");
    cprintf("&cStuff&x\n");
    cprintf("&wStuff&x\n");

    cprintf("@rStuff@x\n");
    cprintf("@gStuff@x\n");
    cprintf("@yStuff@x\n");
    cprintf("@bStuff@x\n");
    cprintf("@mStuff@x\n");
    cprintf("@cStuff@x\n");
    cprintf("@wStuff@x\n");


    
    

    ansiRGB(235, 63, 255);
    cprintf("Test\n");
}
