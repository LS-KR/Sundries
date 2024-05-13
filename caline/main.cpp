
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include "datetime.h"
#include "datetime.cpp"

int line = -1;
int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main(int argc, char** argv) {
    void show(DateTime dt);
    int opt = 0;
    while ((opt = getopt(argc, argv, "l:")) != -1) {
        switch (opt) {
            case 'l':
                line = atoi(optarg);
                break;
            default:
                break;
        }
    }
    DateTime dt;
    dt.Now();
    if (line == -1) {
        show(dt);
    }
    else {
        auto date = dt.getDate();
        date.day = line * 7 + 1;
        dt = DateTime(date.year, date.month, date.day, 0, 0, 0);
        show(dt);
    }
}

void show(DateTime dt) {
    if (dt.getDate().week == Sunday) {
        for (int i = 0; i < 7; ++i) {
            std::printf("%3d", dt.getDate().day + i);
        }
    }
    else {
        int d = dt.getDate().day;
        auto date = dt.getDate();
        while (dt.getDate().week != Sunday) {
            d -= 1;
            if (d == 0) {
                date.month = date.month - 1;
                d = daysInMonth[date.month];
            }
            dt = DateTime(date.year, date.month, d, 0, 0, 0);
            date = dt.getDate();
        }
        for (int i = 0; i < 7; ++i) {
            int d = dt.getDate().day;
            if (d + i <= 0) 
                std::printf("%3d", d + i + daysInMonth[((dt.getDate().month - 1) > 0) ? (dt.getDate().month - 1) : 12]);
            else if (d + i <= daysInMonth[dt.getDate().month])
                std::printf("%3d", d + i);
            else
                std::printf("%3d", d + i - daysInMonth[dt.getDate().month]);
        }
    }
}