
#ifndef VSTRING_H
#define VSTRING_H

#include <curses.h>
#define readonly const

#include <string>
#include <cstring>

class VString {
public:
    VString(std::string);
    VString(char*);
    readonly char* c_str();
    readonly std::string string();
    VString operator+(VString);
    VString operator+(std::string);
    VString operator+(char*);
    bool operator>(VString);
    bool operator>(std::string);
    bool operator>(char*);
    bool operator>=(VString);
    bool operator>=(std::string);
    bool operator>=(char*);
    bool operator<(VString);
    bool operator<(std::string);
    bool operator<(char*);
    bool operator<=(VString);
    bool operator<=(std::string);
    bool operator<=(char*);
    bool operator==(VString);
    bool operator==(std::string);
    bool operator==(char*);
    void operator=(VString);
    void operator=(std::string);
    void operator=(char*);
private:
    std::string source;
protected:
};

inline VString::VString(std::string string) {
    this->source = string;
}

inline VString::VString(char* charmap) {
    this->source = charmap;
}

inline readonly char* VString::c_str() {
    return this->source.c_str();
}

inline readonly std::string VString::string() {
    return this->source;
}

inline VString VString::operator+(VString v) {
    return VString(this->source + v.string());
}

inline VString VString::operator+(std::string s) {
    return VString(this->source + s);
}

inline VString VString::operator+(char* charmap) {
    return VString(this->source + charmap);
}

inline bool VString::operator>(VString v) {
    return std::strcmp(this->c_str(), v.c_str()) > 0;
}

inline bool VString::operator<(VString v) {
    return std::strcmp(this->c_str(), v.c_str()) < 0;
}

inline bool VString::operator==(VString v) {
    return std::strcmp(this->c_str(), v.c_str()) == 0;
}

inline bool VString::operator>=(VString v) {
    return ((*this) > v) || ((*this) == v);
}

inline bool VString::operator<=(VString v) {
    return ((*this) < v) || ((*this) == v);
}

inline bool VString::operator>(std::string v) {
    return std::strcmp(this->c_str(), v.c_str()) > 0;
}

inline bool VString::operator<(std::string v) {
    return std::strcmp(this->c_str(), v.c_str()) < 0;
}

inline bool VString::operator==(std::string v) {
    return std::strcmp(this->c_str(), v.c_str()) == 0;
}

inline bool VString::operator>=(std::string v) {
    return ((*this) > v) || ((*this) == v);
}

inline bool VString::operator<=(std::string v) {
    return ((*this) < v) || ((*this) == v);
}

inline bool VString::operator>(char* v) {
    return std::strcmp(this->c_str(), v) > 0;
}

inline bool VString::operator<(char* v) {
    return std::strcmp(this->c_str(), v) < 0;
}

inline bool VString::operator==(char* v) {
    return std::strcmp(this->c_str(), v) == 0;
}

inline bool VString::operator>=(char* v) {
    return ((*this) > v) || ((*this) == v);
}

inline bool VString::operator<=(char* v) {
    return ((*this) < v) || ((*this) == v);
}

inline void VString::operator=(VString v) {
    this->source = v.string();
}

inline void VString::operator=(std::string v) {
    this->source = v;
}

inline void VString::operator=(char* v) {
    this->source = v;
}

#endif