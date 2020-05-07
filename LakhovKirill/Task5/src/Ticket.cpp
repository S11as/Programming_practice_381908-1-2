//
// Created by Kirill on 24.04.2020.
//

#include "../include/Ticket.h"

Ticket::Ticket(int hall, int row, int place, int price, const DateTime &dateTime, const string &name) {
    this->hall = hall;
    this->row = row;
    this->place = place;
    this->price = price;
    this->datetime = dateTime;
    this->name = name;
}
