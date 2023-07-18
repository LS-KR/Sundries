
#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <cstdint>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

typedef struct {
    uint16_t year;
    uint16_t month;
    uint16_t day;
} Date;

typedef struct {
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
} Time;

class DateTime {
public:
    DateTime();
    DateTime(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second);
    DateTime(uint16_t hour, uint16_t minute, uint16_t second);
    std::string ToString();
    uint32_t GetUNIXd();
    ::Date getDate();
    ::Time getTime();
    void Now();
private:
    uint16_t Year;
    uint16_t Month;
    uint16_t Day;
    uint16_t Hour;
    uint16_t Minute;
    uint16_t Second;
protected:
};

#endif