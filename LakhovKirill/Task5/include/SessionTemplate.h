//
// Created by Kirill on 23.04.2020.
//

#ifndef TASK5_SESSIONTEMPLATE_H
#define TASK5_SESSIONTEMPLATE_H

#include "string"

using namespace std;

class SessionTemplate {
public:
    explicit SessionTemplate(int id = 1, const string &name = "Film", int minute = 0, int hour = 12);

    inline int getHour() { return this->hour; }

    inline int getMinute() { return this->minute; }

    inline string getName() { return this->name; }

private:
    int id;
    string name;
    int minute;
    int hour;
};


#endif //TASK5_SESSIONTEMPLATE_H
