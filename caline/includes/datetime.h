
#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <cstdint>
#include <string>
#include <sys/time.h>
#include <sys/types.h>

typedef enum {
    Sunday = 0,
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6
} Week;

typedef struct {
    uint16_t year;
    uint16_t month;
    uint16_t day;
    ::Week week;
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
    bool operator == (DateTime t);
    bool operator != (DateTime t);
    bool operator > (DateTime t);
    bool operator < (DateTime t);
    bool operator >= (DateTime t);
    bool operator <= (DateTime t);
private:
    uint16_t Year;
    uint16_t Month;
    uint16_t Day;
    uint16_t Hour;
    uint16_t Minute;
    uint16_t Second;
    static constexpr int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int dayOfYear(int year, int month, int day);
    bool isLeap(int year);
    ::Week getWeek(int year, int month, int day);
protected:
};

#endif