
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "datetime.cpp"
#include "console.cpp"
#include "shownumber.h"

int main(void) {
    DateTime dt;
    Console console;
    Box b = console.getConsoleBox();
    if ((b.height < 5) || (b.width < 17)) {
        console.WriteLine("Too small console!");
        return 233;
    }
    while (true) {
        system("clear");
        for (int j = 0; j < 5; ++j) {
            showNumber(dt.getTime().hour / 10, j);
            console.Write("\033[0m  ");
            showNumber(dt.getTime().hour % 10, j);
            console.Write(((j == 1) || (j == 3)) ? ("\033[0m  \033[92;102m  \033[0m  ") : "\033[0m      ");
            showNumber(dt.getTime().minute / 10, j);
            console.Write("\033[0m  ");
            showNumber(dt.getTime().minute % 10, j);   
            console.WriteLine("\033[0m");
        }
        dt.Now();
        sleep(1);
    }
    return 0;
}