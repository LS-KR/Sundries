
#ifndef CPP_BITSET
#define CPP_BITSET

#include "BitSet.h"
#include <system_error>

BitSet::BitSet(unsigned long size) {
    this->size = size;
    unsigned long length = size / 8;
    if (size % 8 != 0)
        length += 1;
    this->length = length;
    this->c = new unsigned char[length];
    for (int i = 0; i < length; ++i) {
        c[i] &= 0x00;
    }
}

BitSet::~BitSet() {
    delete [] this->c;
    this->size = 0;
    this->length = 0;
}

unsigned char BitSet::digitMap(unsigned char i) {
    return 0x01 << (7 - i);
} 

bool BitSet::Set(unsigned long index, bool flag) {
    if (index > this->size) 
        throw std::errc::invalid_argument;
    unsigned char d = digitMap(index % 8);
    if (flag) {
        this->c[index / 8] |= d;
    }
    else {
        d = ~d;
        this->c[index / 8] &= d;
    }
    return flag;
}

bool BitSet::Set(unsigned long index) {
    return this->Set(index, true);
}

bool BitSet::Get(unsigned long index) {
    if (index > this->size) 
        throw std::errc::invalid_argument;
    unsigned char d = digitMap(index % 8);
    return this->c[index / 8] & d;
}

unsigned char* BitSet::Data() {
    return this->c;
}

#endif