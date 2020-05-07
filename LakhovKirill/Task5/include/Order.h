//
// Created by Kirill on 24.04.2020.
//

#ifndef TASK5_ORDER_H
#define TASK5_ORDER_H

#include <vector>
#include "Ticket.h"
#include "Session.h"

using namespace std;

class Order {
public:
    Order() = default;

    Order(const Session &session);

    void append(const Ticket &ticket);

    inline vector<Ticket> getTickets() const { return this->tickets; }

    inline int getPrice() const { return this->price; }

    inline Session getSession() const { return this->session; }

private:
    Session session;
    vector<Ticket> tickets;

    int price;

};


#endif //TASK5_ORDER_H
