
#include <cstddef>
#include <iostream>
#include <cmath>
#include <iterator>
#include <string>
#include <time.h>
#include <cstdlib>
#include <sys/time.h>
#include <iterator>

int getTimeSecond(void) {
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    return (now->tm_sec);
}

int rd(int _max) {
    for (int i = getTimeSecond(); i >= 0; --i)
        std::rand();
    return std::rand() % _max;
}

std::string adj[] = {
    "fast","slow","good","bad","expensive","cheap","thick","thin","narrow","wide","broad","loud","quiet","intelligent","stupid","wet","dry","heavy","light","hard","soft","shallow","deep","easy","difficult","weak","strong","rich","poor","young","old","long","short","high","low","generous","mean","true","false","beautiful","ugly","new","old","happy","sad","safe","dangerous","early","late","light","dark","tight","loose","full","empty","many","few","alive","dead","hot","cold","interesting","boring","lucky","unlucky","important","unimportant","right","wrong","far","near","clean","dirty","nice","nasty","pleasant","unpleasant","excellent","terrible","fair","unfair","normal","abnormal"
};

std::string noun[] = {
    "curtain","garage","mailbox","skylight","balcony","lawn","window","television","console","chair","floor","clock","calendar","door","bookcase","light","pillow","lamp","wall","matches","table","vase","telephone","basket","dish","counter","sink","wok","pan","ladle","gas","oven","broom","mop","rice","blender","water","toaster","knife","microwave","shower","faucet","paper","toilet","tub","drain","tile","mirror","sink","rug","towel","captain","copilot","exit","passenger","map","chalk","board","classroom","organ","globe","eraser","rack","shoe","platform","desk","book","umbrella","tie","coat","socks","radio","stair","skirt","sweater","cookie","cup"
};

int main(int argc, char** argv) {
    std::cout << adj[rd(83)] << " "
              << noun[rd(77)] << " "
              << noun[rd(77)] << " "
              << noun[rd(77)] << std::endl;
    return 0;
}