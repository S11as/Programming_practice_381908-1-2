//
// Created by Kirill Lakhov on 14.03.2020.
//

#include <stdexcept>
#include "../include/Date.h"

Date::Date(int d, int m, int y) {
    if (!(this->setDay(d) && this->setMonth(m) && this->setYear(y))) throw  std::invalid_argument("wrong data properties");
}

bool Date::setDay(int day) {
    if (day >= 1 && day <= 31) {
        this->day = day;
        this->sDay = day <= 9 ? "0" + to_string(day) : to_string(day);
        return true;
    }
    return false;
}

bool Date::setMonth(int month) {
    if(month>=1 && month <= 12){
        this->month = month;
        this->sMonth = month <= 9 ? "0" + to_string(month) : to_string(month);
        return true;
    }
    return false;
}

bool Date::setYear(int year) {
    if(year >= 1){
        this->year = year;
        this->sYear = to_string(year);
        return true;
    }
    return false;
}

string Date::getDate() const {
    return this->sDay+"."+this->sMonth+"."+this->sYear;
}
