//
// Created by Kirill on 24.04.2020.
//

#include "../include/Order.h"

void Order::append(const Ticket &ticket) {
    this->tickets.push_back(ticket);
    this->price += ticket.getPrice();
}

Order::Order(const Session &session) {
    this->session = session;
    this->price = 0;
}
