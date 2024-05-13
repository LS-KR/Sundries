
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "datetime.cpp"
#include "console.cpp"
#include "shownumber.h"
#include <cctype>
#include <ncurses.h>
#include <unistd.h>
#include <getopt.h>

bool showSecond = false;
int transcount = 0;
int tick = 1000;
int ns = 0;
std::string transcolor[5] = {
    "\033[38;2;85;205;253m\033[48;2;85;205;253m",
    "\033[38;2;246;170;183m\033[48;2;246;170;183m",
    "\033[38;2;255;255;255m\033[48;2;255;255;255m",
    "\033[38;2;246;170;183m\033[48;2;246;170;183m",
    "\033[38;2;85;205;253m\033[48;2;85;205;253m"
};
std::string transdatecolor[3] = {
    "\033[38;2;85;205;253m",
    "\033[38;2;246;170;183m",
    "\033[38;2;255;255;255m"
};
std::string normalColor = "\033[92;102m";
std::string dateColor = "\033[0m\033[92m";
int spaceCount = 0;
int returnCount = 0;
bool showonce = false;
bool screensaver = false;
bool blinking = false;
bool center = false;

bool setColor(char t) {
    if ((t >= '0') && (t <= '7')){
        normalColor = "\033[" + std::to_string(((int)t) - 0x30 + 40) + ";" + std::to_string(((int)t) - 0x30 + 30) + "m";
        dateColor = "\033[0m\033[" + std::to_string(((int)t) - 0x30 + 30) + "m";
    }
    else if (t == '8'){
        normalColor = "\033[90;100m";
        dateColor = "\033[0m\033[90m";
    }
    else if (t == '9'){
        normalColor = "\033[91;101m";
        dateColor = "\033[0m\033[91m";
    }
    else if ((std::tolower(t) >= 'a') && (std::tolower(t) <= 'f')){
        normalColor = "\033[" + std::to_string(((int)std::tolower(t)) - 0x61 + 92) + ";" + std::to_string(((int)std::tolower(t)) - 0x61 + 102) + "m";
        dateColor = "\033[0m\033[" + std::to_string(((int)std::tolower(t)) - 0x61 + 92) + "m";
    }
    else {
        return false;
    }
    return true;
}

int hexCharToInt(char c) {
    if ((c >= '0') && (c <= '9'))
        return (c - '0');
    if ((c >= 'A') && (c <= 'F'))
        return (c - 'A' + 10);
    if ((c >= 'a') && (c <= 'f'))
        return (c - 'a' + 10);
    return -1;
}

bool setRGBColor(char* color) {
    unsigned int r = 0, g = 0, b = 0;
    unsigned long rgb = 0;
    while (*(++color)) {
        rgb <<= 4;
        rgb += hexCharToInt(*color);
        if (hexCharToInt(*color) == -1)
            return false;
    }
    r = (rgb >> 16) & 0xFF;
    g = (rgb >> 8) & 0xFF;
    b = rgb & 0xFF;
    normalColor = "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    dateColor = "\033[0m\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    return true;
}

int main(int argc, char** argv) {
    DateTime dt;
    Console console;
    Box b = console.getConsoleBox();
    int opt = 0;
    console.HideEcho();
    if ((b.height < 6) || (b.width < 39)) {
        console.WriteLine("Too small console!");
        return 233;
    }
    while ((opt = getopt(argc, argv, "hsc1SC:t:a:b")) != -1) {
        switch (opt) {
            case 'h':
                std::cout << "usage: tty-clock [-hsc1Sb] [-C Color] [-t ticks] [-a nsticks]" << std::endl;
                std::cout << "    -h         show this page" << std::endl;
                std::cout << "    -s         show second" << std::endl;
                std::cout << "    -c         center the clock when start" << std::endl;
                std::cout << "    -1         show once" << std::endl;
                std::cout << "    -C Color   change color: 0~F or RGB color" << std::endl;
                std::cout << "    -S         screen saver mode" << std::endl;
                std::cout << "    -t ticks   set the delay between refresh (default:1000 ms)" << std::endl;
                std::cout << "    -a nsticks set the delay between refresh (microsecond, add to -t ticks)" << std::endl;
                std::cout << "    -b         enable blinking" << std::endl;
                std::cout << std::endl;
                std::cout << "keyboard shortcuts:" <<std::endl;
                std::cout << "    Q: quit tty-clock" << std::endl;
                std::cout << "    C: center the clock" << std::endl;
                std::cout << "    M: Locate the clock at topleft" << std::endl;
                std::cout << "    S: show/unshow the second" << std::endl;
                std::cout << "    E: Change color" << std::endl;
                return 0;
            case 's':
                showSecond = true;
                break;
            case 'c':{
                b = console.getConsoleBox();
                int clockwidth = showSecond ? 54 : 38;
                spaceCount = (b.width - clockwidth) / 2;
                returnCount = (b.height - 6) / 2;
                center = true;
                break;
            }
            case 'C': {
                if (optarg[0] == '#') {
                    if (!setRGBColor(optarg))
                        return 8;
                    break;
                }
                if (!setColor(optarg[0]))
                    return 8;
                break;
            }
            case 'S':
                screensaver = true;
                break;
            case 't': 
                tick = atoi(optarg);
                break;
            case 'a':
                ns = atoi(optarg);
                break;
            case 'b' :
                blinking = true;
                break;
            case '1':
                showonce = true;
        }
    }
    while (true) {
        if (!showonce) 
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
            showNumber(dt.getTime().hour / 10, j, (transcount != 5) ? normalColor : transcolor[j]);
            console.Write("\033[0m  ");
            showNumber(dt.getTime().hour % 10, j, (transcount != 5) ? normalColor : transcolor[j]);
            console.Write(((j == 1) || (j == 3)) ? (((!blinking) || (dt.getTime().second % 2 == 0)) ? ("\033[0m  " + ((transcount != 5) ? normalColor : transcolor[j]) + "  \033[0m  ") : ("\033[0m      ")): ("\033[0m      "));
            showNumber(dt.getTime().minute / 10, j, (transcount != 5) ? normalColor : transcolor[j]);
            console.Write("\033[0m  ");
            showNumber(dt.getTime().minute % 10, j, (transcount != 5) ? normalColor : transcolor[j]);
            if (showSecond) {
                console.Write(((j == 1) || (j == 3)) ? (((!blinking) || (dt.getTime().second % 2 == 0)) ? ("\033[0m  " + ((transcount != 5) ? normalColor : transcolor[j]) + "  \033[0m  ") : ("\033[0m      ")): ("\033[0m      "));
            showNumber(dt.getTime().second / 10, j, (transcount != 5) ? normalColor : transcolor[j]);
                console.Write("\033[0m  ");
                showNumber(dt.getTime().second % 10, j, (transcount != 5) ? normalColor : transcolor[j]);
                console.Write("\033[0m  ");
            }
            console.WriteLine("\033[0m");
        }
        if (spaceCount) {
            for (int space = 0; space < spaceCount; ++space)
                console.Write(' ');
        }
        for (int i = 0; i < (showSecond ? 22 : 12); ++i) 
            console.Write(" ");
        console.WriteLine(((transcount != 5) ? dateColor : (transdatecolor[dt.getTime().second % 3])) + std::to_string(dt.getDate().year) + "/" + (((dt.getDate().month + 1 >= 10) ? "" : "0") + std::to_string(dt.getDate().month + 1)) + "/" + (((dt.getDate().day >= 10) ? "" : "0") + std::to_string(dt.getDate().day)) + "\033[0m");
        if (console.kbhit()) {
            if (screensaver)
                return 0;
            char c = console.getKey();
            switch (c) {
                case 'a':
                    if (transcount == 2) ++transcount;
                    break;
                case 'c': {
                    b = console.getConsoleBox();
                    int clockwidth = showSecond ? 54 : 38;
                    spaceCount = (b.width - clockwidth) / 2;
                    returnCount = (b.height - 6) / 2;
                    center = true;
                    break;
                }
                case 'e': {
                    system("clear");
                    b = console.getConsoleBox();
                    std::string from = "";
                    if (center) {
                        for (int i = 0; i < ((b.height - 6) / 2); ++i) 
                            std::cout << std::endl;
                        for (int i = 0; i < ((b.width - 32) / 2); ++i) 
                            from += " ";
                    }
                    std::cout << from + "\033[0mSelect color:" << std::endl;
                    std::cout << from + "\033[40m    \033[41m    \033[42m    \033[43m    \033[44m    \033[45m    \033[46m    \033[47m    \033[0m" << std::endl;
                    std::cout << from + "\033[40m   0\033[41m   1\033[42m   2\033[43m   3\033[44m   4\033[45m   5\033[46m   6\033[47m   7\033[0m" << std::endl;
                    std::cout << from + "\033[100m    \033[101m    \033[102m    \033[103m    \033[104m    \033[105m    \033[106m    \033[107m    \033[0m" << std::endl;
                    std::cout << from + "\033[100m   8\033[101m   9\033[102m   A\033[103m   B\033[104m   C\033[105m   D\033[106m   E\033[107m   F\033[0m" << std::endl;
                    std::cout << from + "\033[0m" << std::endl;
                    do {
                        while (!console.kbhit());
                    } while (!setColor(console.getKey()));
                    break;
                }
                case 'm':
                    spaceCount = 0;
                    returnCount = 0;
                    center = false;
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
        if (showonce) break;
        dt.Now();
        usleep(tick * 1000 + ns);
    }
    return 0;
}