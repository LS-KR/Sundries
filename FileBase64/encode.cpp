
#include <exception>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
#include "base64.cpp"

std::string filename = "";
std::string output = "";

int main(int argc, char** argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, "f:o:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            default:
                std::cout << "usage: encode <-f file> [-o output]" << std::endl;
                return 0;
        }
    }
    if (filename.empty()) {
        std::cout << "usage: encode <-f file> [-o output]" << std::endl;
        return 1;
    }
    std::ifstream fi;
    try {
        fi.open(filename, std::ios_base::binary);
    }
    catch (std::exception e) {
        std::cout << "Failed to open file: " << e.what() << std::endl;
    }
    std::ofstream fo;
    if (!output.empty()) {
        try {
            fo.open(output, std::ios_base::out);
        }
        catch (std::exception e) {
            std::cout << "Failed to open file: " << e.what() << std::endl;
            return 3;
        }
    }
    while (!fi.eof()) {
        unsigned char data[3] = {0, 0, 0};
        Base64 base64;
        
        fi.read((char*)data, 3 * sizeof(unsigned char));
        if (output.empty()) {
            std::cout << base64.encode(data, 3, fi.eof()) << std::flush;
        }
        else {
            fo.write(base64.encode(data, 3, false).c_str(), base64.encode(data, 3, false).size());
        }
    }
    return 0;
}