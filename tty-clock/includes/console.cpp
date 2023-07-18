
#include "console.h"
#include <cstdio>
#include <ostream>
#include <string>

Console::Console() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    boxl.height = w.ws_row;
    boxl.width = w.ws_col;
}

void Console::WriteLine() {
    std::cout << std::endl;
}

void Console::WriteLine(std::string s) {
    std::cout << s << std::endl;
}

void Console::Write(std::string s) {
    std::cout << s << std::flush;
}

void Console::WriteLine(short val) {
    WriteLine(std::to_string(val));
}

void Console::WriteLine(long val) {
    WriteLine(std::to_string(val));
}

void Console::WriteLine(float val) {
    WriteLine(std::to_string(val));
}

void Console::WriteLine(double val) {
    WriteLine(std::to_string(val));
}

void Console::WriteLine(long long val) {
    WriteLine(std::to_string(val));
}

void Console::WriteLine(char val) {
    std::printf("%c", val);
    WriteLine();
}

void Console::Write(short val) {
    Write(std::to_string(val));
}

void Console::Write(long val) {
    Write(std::to_string(val));
}

void Console::Write(float val) {
    Write(std::to_string(val));
}

void Console::Write(double val) {
    Write(std::to_string(val));
}

void Console::Write(long long val) {
    Write(std::to_string(val));
}

void Console::Write(char val) {
    std::printf("%c", val);
}

std::string Console::ReadLine() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}

std::string Console::ReadLine(std::string notice) {
    Write(notice);
    return ReadLine();
}

Box Console::getConsoleBox() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    boxl.height = w.ws_row;
    boxl.width = w.ws_col;
    return boxl;
}

bool Console::kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void Console::initTermios(int echo) {
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON;
    if (echo) {
        current.c_lflag |= ECHO;
    } 
    else {
        current.c_lflag &= ~ECHO;
    }
    tcsetattr(0, TCSANOW, &current);
}

void Console::resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}

char Console::getch_(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

char Console::getKey() {
    return getch_(0);
}

char Console::getKeyw() {
    return getch_(1);
}

void Console::HideEcho() {
    initTermios(0);
}

void Console::ShowEcho() {
    initTermios(1);
}