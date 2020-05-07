//
// Created by Kirill on 23.04.2020.
//

#include "../include/SessionTemplate.h"

SessionTemplate::SessionTemplate(int id, const string &name, int minute, int hour) {
    this->id = id;
    this->name = name;
    this->minute = minute;
    this->hour = hour;
}
