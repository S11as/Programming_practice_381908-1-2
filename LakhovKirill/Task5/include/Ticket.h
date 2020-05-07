//
// Created by Kirill on 24.04.2020.
//

#ifndef TASK5_TICKET_H
#define TASK5_TICKET_H

#include "Hall.h"
#include "DateTime.h"

using namespace std;

class Ticket {
public:
    Ticket(int hall, int row, int place, int price, const DateTime &dateTime, const string &name);

    inline int getPrice() const { return this->price; }

    inline DateTime getDateTime() const { return this->datetime; }

    inline string getName() const { return this->name; }

    inline int getHall() const { return this->hall; }

    inline int getRow() const { return this->row; }

    inline int getPlace() const { return this->place; }

private:
    int hall;
    string name;
    DateTime datetime;
    int row;
    int place;
    int price;
};


#endif //TASK5_TICKET_H
