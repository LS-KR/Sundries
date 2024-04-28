
#ifndef H_BASE64
#define H_BASE64

#include <string>
#include <vector>

class Base64 {
public:
    std::string encode(unsigned char *data, int length, bool end);
    std::string encode(std::vector<unsigned char> data);
    std::vector<unsigned char> decode(std::string s);
private:
    const char *b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned char index(char c);
};

#endif