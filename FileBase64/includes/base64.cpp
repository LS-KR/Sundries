
#include "base64.h"
#include <string>
#include <vector>

std::string Base64::encode(unsigned char *data, int length, bool end) {
    int r_length = (length / 3) * 3;
    std::string s = "";
    for (int i = 0; i < r_length; i += 3) {
        unsigned char a[4] = {0, 0, 0, 0};
        a[0] = data[i] >> 2;
        a[1] = ((data[i] & 0x03) << 4) | ((data[i + 1] & 0xF0) >> 4);
        a[2] = ((data[i + 1] & 0x0F) << 2) | ((data[i + 2] & 0xC0) >> 6);
        a[3] = data[i + 2] & 0x3F;
        for (auto v : a) {
            s += b64[v];
        }
    }
    switch (length % 3) {
        case 1: {
            unsigned char b[2] = { static_cast<unsigned char>(data[r_length] >> 2), static_cast<unsigned char>((data[r_length] & 0x03) << 4)};
            s += b64[b[0]];
            s += b64[b[1]];
            s += (end ? "==" : "AA");
            break;
        }
        case 2: {
            unsigned char c[3] = { static_cast<unsigned char>(data[r_length] >> 2), static_cast<unsigned char>(((data[r_length] & 0x03) << 4) | ((data[r_length + 1] & 0xF0) >> 4 )), static_cast<unsigned char>((data[r_length + 1] & 0x0F) << 2)};
            s += b64[c[0]];
            s += b64[c[1]];
            s += b64[c[2]];
            s += (end ? "=" : "A");
            break;
        }
        default:
            break;
    }
    return s;
}

std::string Base64::encode(std::vector<unsigned char> data) {
    return encode(data.data(), data.size(), false);
}

unsigned char Base64::index(char c) {
    if ((c >= 'A') && (c <= 'Z'))
        return c - 'A';
    if ((c >= 'a') && (c <= 'z'))
        return c - 'a' + 26;
    if ((c >= '0') && (c <= '9'))
        return c - '0' + 52;
    if (c == '+')
        return 62;
    if (c == '/')
        return 63;
    if (c == '=')
        return 0;
    return 64;
}

std::vector<unsigned char> Base64::decode(std::string s) {
    std::vector<unsigned char> data;
    for (int i = 0; i < s.size(); i += 4) {
        unsigned char c[3] = {0, 0, 0};
        c[0] = (index(s.c_str()[i]) << 2) | ((index(s.c_str()[i + 1]) & 0x30) >> 4);
        c[1] = ((index(s.c_str()[i + 1]) & 0x0F) << 4) | ((index(s.c_str()[i + 2]) & 0x3C) >> 2);
        c[2] = ((index(s.c_str()[i + 2]) & 0x03) << 6) | index(s.c_str()[i + 3]);
        data.push_back(c[0]);
        if (s.c_str()[i + 2] != '=') 
            data.push_back(c[1]);
        if (s.c_str()[i + 3] != '=') 
            data.push_back(c[2]);
    }
    return data;
}