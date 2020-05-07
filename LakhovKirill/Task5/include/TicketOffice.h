//
// Created by Kirill on 24.04.2020.
//

#ifndef TASK5_TICKETOFFICE_H
#define TASK5_TICKETOFFICE_H

using namespace std;

#include "Cinema.h"
#include "View.h"
#include "Order.h"

class TicketOffice {
public:
    explicit TicketOffice(Cinema &cinema, bool refresh);

    void start();

    void order();

    void schedule();

    void showOrders();

    void save();

private:
    Cinema cinema;
    View view;
    vector<Order> orders;
};


#endif //TASK5_TICKETOFFICE_H
