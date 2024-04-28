
#include <exception>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
#include <vector>
#include "base64.cpp"

std::string base = "";
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
                std::cout << "usage: encode [-f file] [-o output]" << std::endl;
                return 0;
        }
    }
    std::ifstream fi;
    if (filename.empty()) {
        std::cout << "Input: " << std::flush;
        std::cin >> base;
        if (base.empty()) return 3;
        Base64 base64;
        auto data = base64.decode(base);
        if (output.empty()) {
            for (auto v : data) {
                std::cout << v << std::flush;
            }
        }
        else {
            try {
                std::ofstream fo;
                fo.open(output, std::ios_base::out | std::ios_base::binary);
                fo.write((char*)data.data(), data.size());
                fo.close();
            }
            catch (std::bad_exception e) {
                std::cout << "Failed to write file: " << e.what() << std::endl;
                return 1;
            }
        }
    }
    else {
        try {
            fi.open(filename, std::ios_base::in);
        }
        catch (std::exception e) {
            std::cout << "Failed to open file: " << e.what() << std::endl;
            return 2;
        }
        Base64 base64;
        while (!fi.eof()) {
            base = "";
            for (int i = 0; i < 4; ++i) {
                char c = '\0';
                fi.read(&c, 1);
                base += c;
            }
            auto data = base64.decode(base);
            for (auto v : data) {
                if (output.empty()) {
                    std::cout << v << std::flush;
                }
                else {
                    try {
                        std::ofstream fo;
                        fo.open(output, std::ios_base::app);
                        fo.write((char*)(&v), 1);
                        fo.close();
                    }
                    catch (std::exception e) {
                        std::cout << "Failed to write file: " << e.what() << std::endl;
                        return 2;
                    }
                }
            }
        }
    }
    return 0;
}