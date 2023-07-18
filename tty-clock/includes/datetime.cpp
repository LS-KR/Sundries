
#include "datetime.h"
#include <string>

DateTime::DateTime() {
    time_t t = time(0);
    tm* now = localtime(&t);
    this->Year = now->tm_year + 1900;
    this->Month = now->tm_mon;
    this->Day = now->tm_mday;
    this->Hour = now->tm_hour;
    this->Minute = now->tm_min;
    this->Second = now->tm_sec;
}

DateTime::DateTime(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second) {
    this->Year = year;
    this->Month = month;
    this->Day = day;
    this->Hour = hour;
    this->Minute = minute;
    this->Second = second;
}

DateTime::DateTime(uint16_t hour, uint16_t minute, uint16_t second) {
    time_t t = time(0);
    tm* now = localtime(&t);
    this->Year = now->tm_year + 1900;
    this->Month = now->tm_mon;
    this->Day = now->tm_mday;
    this->Hour = hour;
    this->Minute = minute;
    this->Second = second;
}

std::string DateTime::ToString() {
    return std::to_string(this->Year) + "/" + std::to_string(this->Month) + "/" + std::to_string(this->Day) + " " + (this->Hour > 10 ? "" : "0") + std::to_string(this->Hour) + ":" + (this->Minute > 10 ? "" : "0") + std::to_string(this->Minute) + ":" + (this->Second > 10 ? "" : "0") + std::to_string(this->Second);
}

Date DateTime::getDate() {
    ::Date d;
    d.year = this->Year;
    d.month = this->Month;
    d.day = this->Day;
    return d;
}

Time DateTime::getTime() {
    ::Time t;
    t.hour = this->Hour;
    t.minute = this->Minute;
    t.second = this->Second;
    return t;
}

void DateTime::Now() {
    time_t t = time(0);
    tm* now = localtime(&t);
    Year = now->tm_year + 1900;
    Month = now->tm_mon;
    Day = now->tm_mday;
    Hour = now->tm_hour;
    Minute = now->tm_min;
    Second = now->tm_sec;
}