//
// Created by Kirill on 23.04.2020.
//

#ifndef TASK5_DATETIME_H
#define TASK5_DATETIME_H

#include "string"

using namespace std;

class DateTime {
private:
    int day;
    int month;
    int year;
    int minute;
    int hour;
    string sDay;
    string sMonth;
    string sYear;
    string sHour;
    string sMinute;
public:
    explicit DateTime(int d = 1, int m = 1, int y = 1900, int h = 12, int mm = 0);

    bool setDay(int day);

    bool setMonth(int month);

    bool setYear(int year);

    bool setHour(int hour);

    bool setMinute(int minute);

    string getDate() const;

    string getTime() const;

    string getFullDate() const;

    inline int getDay() const { return this->day; }

    inline int getMonth() const { return this->month; }

    inline int getYear() const { return this->year; }

    inline int getHour() const { return this->hour; }

    inline int getMinute() const { return this->minute; }
};


#endif //TASK5_DATETIME_H
