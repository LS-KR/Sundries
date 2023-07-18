
#ifndef CONSOLE_H
#define  CONSOLE_H

#include <string>
#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <sys/select.h>

typedef struct {
    long width;
    long height;
} Box;

class Console {
public:
    Console();
    void WriteLine();
    void WriteLine(std::string s);
    void Write(std::string s);
    void WriteLine(short val);
    void WriteLine(long val);
    void WriteLine(float val);
    void WriteLine(double val);
    void WriteLine(long long val);
    void WriteLine(char val);
    void Write(short val);
    void Write(long val);
    void Write(float val);
    void Write(double val);
    void Write(long long val);
    void Write(char val);
    std::string ReadLine();
    std::string ReadLine(std::string notice);
    ::Box getConsoleBox();
    bool kbhit();
    char getKey();
    char getKeyw();
    void HideEcho();
    void ShowEcho();
private:
    Box boxl;
    void initTermios(int echo);
    void resetTermios(void);
    char getch_(int echo);
    struct termios old, current;
protected:
};

#endif