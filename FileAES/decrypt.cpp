
#include <exception>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include "AES.cpp"
#include "AES.h"

std::string filename;
std::string passwd;
std::string output = "output.bin";
bool ascii = false;

int main(int argc, char** argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, "af:p:o:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'p':
                passwd = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            case 'a':
                ascii = true;
            default:
                std::cout << "usage: encrypt <-f file> <-p password> [-o output] [-a ascii]" << std::endl;
                return 0;
        }
    }
    if (filename.empty()) {
        std::cout << "usage: encrypt <-f file> <-p password> [-o output]" << std::endl;
        return 1;
    }
    if (passwd.empty()) {
        std::cout << "usage: encrypt <-f file> <-p password> [-o output]" << std::endl;
        return 1;
    }
    auto aes = AES(AESKeyLength::AES_256);
    std::ifstream fi;
    try {
        fi.open(filename, std::ios_base::binary);
    }
    catch (std::exception e) {
        std::cout << "Failed to open file: " << e.what() << std::endl;
        return 233;
    }
    std::vector<unsigned char> data;
    while (!fi.eof()) {
        unsigned char c = '\0';
        fi.read((char*)(&c), sizeof(c));
        data.push_back(c);
    }
    if (data.size() % 16 != 0) {
        int l = 16 - (data.size() % 16);
        while (l--) data.push_back('\0');
    }
    std::vector<unsigned char> passwdVec;
    for (auto v : passwd) {
        if (ascii && ((v < 0x20) || (v > 0x7E))) continue;
        passwdVec.push_back(v);
    }
    auto decrypted = aes.DecryptECB(data, passwdVec);
    std::ofstream fo;
    try {
        fo.open(output, std::ios_base::binary);
    } 
    catch (std::exception e) {
        std::cout << "Failed to open file: " << e.what() << std::endl;
        return 233;
    }
    for (auto v : decrypted) {
        fo.write((char*)(&v), sizeof(unsigned char));
    }
    return 0;
}