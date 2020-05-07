//
// Created by Kirill on 23.04.2020.
//

#include "../include/DateTime.h"
#include <stdexcept>

DateTime::DateTime(int d, int m, int y, int h, int mm) {
    if (!(this->setDay(d) && this->setMonth(m) && this->setYear(y) && this->setHour(h) && this->setMinute(mm)))
        throw std::invalid_argument("wrong data properties");
}

bool DateTime::setDay(int day) {
    if (day >= 1 && day <= 31) {
        this->day = day;
        this->sDay = day <= 9 ? "0" + to_string(day) : to_string(day);
        return true;
    }
    return false;
}

bool DateTime::setMonth(int month) {
    if (month >= 1 && month <= 12) {
        this->month = month;
        this->sMonth = month <= 9 ? "0" + to_string(month) : to_string(month);
        return true;
    }
    return false;
}

bool DateTime::setYear(int year) {
    if (year >= 1) {
        this->year = year;
        this->sYear = to_string(year);
        return true;
    }
    return false;
}

string DateTime::getDate() const {
    return this->sDay + "." + this->sMonth + "." + this->sYear;
}

string DateTime::getTime() const {
    return this->sHour + ":" + this->sMinute;
}

bool DateTime::setHour(int hour) {
    if (hour >= 0 && month <= 23) {
        this->hour = hour;
        this->sHour = hour <= 9 ? "0" + to_string(hour) : to_string(hour);
        return true;
    }
    return false;
}

bool DateTime::setMinute(int minute) {
    if (minute >= 0 && month <= 23) {
        this->minute = minute;
        this->sMinute = minute <= 9 ? "0" + to_string(minute) : to_string(minute);
        return true;
    }
    return false;
}

string DateTime::getFullDate() const {
    return this->getTime() + " " + this->getDate();
}
