
#include "datetime.h"
#include <bits/types/time_t.h>
#include <cstdint>
#include <string>
#include <time.h>


DateTime::DateTime() {
    time_t t = time(0);
    tm* now = localtime(&t);
    this->Year = now->tm_year + 1900;
    this->Month = now->tm_mon + 1;
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
    this->Month = now->tm_mon + 1;
    this->Day = now->tm_mday;
    this->Hour = hour;
    this->Minute = minute;
    this->Second = second;
}

std::string DateTime::ToString() {
    return std::to_string(this->Year) + "/" + std::to_string(this->Month) + "/" + std::to_string(this->Day) + " " + (this->Hour > 10 ? "" : "0") + std::to_string(this->Hour) + ":" + (this->Minute > 10 ? "" : "0") + std::to_string(this->Minute) + ":" + (this->Second > 10 ? "" : "0") + std::to_string(this->Second);
}

bool DateTime::isLeap(int year) {
    if (!(year % 400)) return true;
    if (!(year % 100)) return false;
    if (!(year % 4))   return true;
    return false;
}

int DateTime::dayOfYear(int year, int month, int day) {
    int d = 0;
    if (isLeap(year) && (month > 2)) d += 1;
    while (--month) d += daysInMonth[month];
    return d + day;
}

::Week DateTime::getWeek(int year, int month, int day) {
    int y0 = year - (14 - month) / 12;
    int x = year + year / 4 - year / 100 + year / 400;
    int m0 = month + 12 * ((14 - month) / 12) - 2;
    int d0 = (day + x + (31 * m0) / 12);
    return (::Week) (d0 % 7);
}

Date DateTime::getDate() {
    ::Date d;
    d.year = this->Year;
    d.month = this->Month;
    d.day = this->Day;
    d.week = getWeek(this->Year, this->Month, this->Day);
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
    Month = now->tm_mon + 1;
    Day = now->tm_mday;
    Hour = now->tm_hour;
    Minute = now->tm_min;
    Second = now->tm_sec;
}

bool DateTime::operator==(DateTime t) {
    if (this->Year != t.Year)
        return false;
    if (this->Month != t.Month)
        return false;
    if (this->Day != t.Day)
        return false;
    if (this->Hour != t.Hour)
        return false;
    if (this->Minute != t.Minute)
        return false;
    if (this->Day != t.Day)
        return false;
    return true;
}

bool DateTime::operator!=(DateTime t) {
    return !(*this == t);
}

bool DateTime::operator<(DateTime t) {
    if (this->Year != t.Year)
        return this->Year < t.Year;
    if (this->Month != t.Month)
        return this->Month < t.Month;
    if (this->Day != t.Day)
        return this->Day < t.Day;
    if (this->Hour != t.Hour)
        return this->Hour < t.Hour;
    if (this->Minute != t.Minute)
        return this->Minute < t.Minute;
    return this->Second < t.Second;
}

bool DateTime::operator<=(DateTime t) {
    return ((*this < t) || (*this == t));
}

bool DateTime::operator>(DateTime t) {
    return !(*this <= t);
}

bool DateTime::operator>=(DateTime t) {
    return ((*this > t) || (*this == t));
}
