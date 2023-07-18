
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include "datetime.cpp"
#include "console.cpp"
#include "shownumber.h"
#include <cctype>
#include <ncurses.h>

bool showSecond = false;
int transcount = 0;
std::string transcolor[5] = {
    "\033[38;2;85;205;253m\033[48;2;85;205;253m",
    "\033[38;2;246;170;183m\033[48;2;246;170;183m",
    "\033[38;2;255;255;255m\033[48;2;255;255;255m",
    "\033[38;2;246;170;183m\033[48;2;246;170;183m",
    "\033[38;2;85;205;253m\033[48;2;85;205;253m"
};
int spaceCount = 0;
int returnCount = 0;

int main(void) {
    DateTime dt;
    Console console;
    Box b = console.getConsoleBox();
    console.HideEcho();
    if ((b.height < 5) || (b.width < 39)) {
        console.WriteLine("Too small console!");
        return 233;
    }
    while (true) {
        system("clear");
        if (returnCount) {
            for (int r = 0; r < returnCount; ++r)
                console.WriteLine();
        }
        for (int j = 0; j < 5; ++j) {
            if (spaceCount) {
                for (int space = 0; space < spaceCount; ++space)
                    console.Write(' ');
            }
            showNumber(dt.getTime().hour / 10, j, (transcount != 5) ? "\033[92;102m" : transcolor[j]);
            console.Write("\033[0m  ");
            showNumber(dt.getTime().hour % 10, j, (transcount != 5) ? "\033[92;102m" : transcolor[j]);
            console.Write(((j == 1) || (j == 3)) ? ("\033[0m  " + ((transcount != 5) ? "\033[92;102m" : transcolor[j]) + "  \033[0m  ") : ("\033[0m      "));
            showNumber(dt.getTime().minute / 10, j, (transcount != 5) ? "\033[92;102m" : transcolor[j]);
            console.Write("\033[0m  ");
            showNumber(dt.getTime().minute % 10, j, (transcount != 5) ? "\033[92;102m" : transcolor[j]);
            if (showSecond) {
                console.Write(((j == 1) || (j == 3)) ? ("\033[0m  " + ((transcount != 5) ? "\033[92;102m" : transcolor[j]) + "  \033[0m  ") : ("\033[0m      "));
                showNumber(dt.getTime().second / 10, j, (transcount != 5) ? "\033[92;102m" : transcolor[j]);
                console.Write("\033[0m  ");
                showNumber(dt.getTime().second % 10, j, (transcount != 5) ? "\033[92;102m" : transcolor[j]);
                console.Write("\033[0m  ");
            }
            console.WriteLine("\033[0m");
        }
        if (console.kbhit()) {
            char c = console.getKey();
            switch (c) {
                case 'a':
                    if (transcount == 2) ++transcount;
                    break;
                case 'c': {
                    b = console.getConsoleBox();
                    int clockwidth = showSecond ? 54 : 38;
                    spaceCount = (b.width - clockwidth) / 2;
                    returnCount = (b.height - 5) / 2;
                    break;
                }
                case 'm':
                    spaceCount = 0;
                    returnCount = 0;
                    break;
                case 'n':
                    if (transcount == 3) ++transcount;
                    break;
                case 'r':
                    if (transcount == 1) ++transcount;
                    break;
                case 's':
                    showSecond = !showSecond;
                    if (transcount == 4) ++transcount; 
                    break;
                case 't':
                    if (transcount == 0) ++transcount;
                    break;
                case 'q' :
                    return 0;
                default:
                    ;
            }
        }
        dt.Now();
        sleep(1);
    }
    return 0;
}