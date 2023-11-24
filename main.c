#include "Cprintf3.h"



int main()
{
    cprintf("-----------------Standard colors-----------------\n\n");

    cprintf("**************** Flag based ****************\n");
    cprintf("----Dark colors----\n");

    cprintf("#rForeground#x\n");
    cprintf("#gForeground#x\n");
    cprintf("#yForeground#x\n");
    cprintf("#bForeground#x\n");
    cprintf("#mForeground#x\n");
    cprintf("#cForeground#x\n");
    cprintf("#wForeground#x\n");

    cprintf("$rBackground$x\n");
    cprintf("$gBackground$x\n");
    cprintf("$yBackground$x\n");
    cprintf("$bBackground$x\n");
    cprintf("$mBackground$x\n");
    cprintf("$cBackground$x\n");
    cprintf("$wBackground$x\n");
    cprintf("$dBackground$x\n\n");

    cprintf("----Bright colors----\n");

    cprintf("&rForeground&x\n");
    cprintf("&gForeground&x\n");
    cprintf("&yForeground&x\n");
    cprintf("&bForeground&x\n");
    cprintf("&mForeground&x\n");
    cprintf("&cForeground&x\n");
    cprintf("&wForeground&x\n");

    cprintf("@rBackground@x\n");
    cprintf("@gBackground@x\n");
    cprintf("@yBackground@x\n");
    cprintf("@bBackground@x\n");
    cprintf("@mBackground@x\n");
    cprintf("@cBackground@x\n");
    cprintf("@wBackground@x\n\n");

    cprintf("**************** Custom control ****************\n");

    ansiSTDColorFG(30);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(31);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(32);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(33);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(34);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(35);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(36);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(37);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(39);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(40);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(41);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(42);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(43);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(44);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(45);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(46);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(47);
    cprintf("Standard colors\n");
    ansiReset();

    ansiSTDColorFG(49);
    cprintf("Standard colors\n\n");
    ansiReset();

    cprintf("*********Foreground with background (Any possible combination)*********\n");

    ansiSTDColorFG_BG(91, 105);
    cprintf("Foreground + Background\n\n");
    ansiReset();

    cprintf("************* 255 colors (Xterm) *************\n");

    ansiXtermFG(160);
    cprintf("Xterm Support\n\n");
    ansiReset();

    ansiXtermFG_BG(27, 196);
    cprintf("Xterm Foreground + Background\n");
    ansiReset();

    cprintf("************ RGB support (True color) ************\n");

    ansiRGB_FG(255, 131, 48);
    cprintf("Foreground\n");
    ansiReset();

    ansiRGB_BG(255, 131, 48);
    cprintf("Background\n");
    ansiReset();

    ansiRGB_FG_BG(255, 12, 32, 5, 105, 255);
    cprintf("Foreground + Background\n\n");
    ansiReset();

    cprintf("************ Unicode Support ************\n");

    cprintf("██████████████████");
    cprintf("░░░░░░░░░░░░░░░░░░░░░░░░░\n");
}
