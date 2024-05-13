
#include <cstdlib>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "datetime.cpp"
#include "datetime.h"
#include <ncurses.h>
#include <unistd.h>
#include <getopt.h>

double getSaturation(int hour, int minute) {
    if ((hour > 21) || (hour < 5)) return 0.40;
    if ((hour > 5) && (hour < 21)) return 1.0;
    if (hour == 21) return 1.0 - (minute / 100.0);
    if (hour == 5) return 0.4 + (minute / 100.0);
    return 1;
}

int main(int argc, char** argv) {
    DateTime dt;
    while (true) {
        dt.Now();
        std::string command = "vibrant-cli eDP " + std::to_string(getSaturation(dt.getTime().hour, dt.getTime().minute));
        system(command.c_str());
        sleep(60);
    }
    return 0;
}