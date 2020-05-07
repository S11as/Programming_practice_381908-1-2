//
// Created by Kirill on 24.04.2020.
//

#include <iostream>
#include "../include/TicketOffice.h"

TicketOffice::TicketOffice(Cinema &cinema, bool refresh) {
    this->cinema = cinema;
    this->view = View();

    if(refresh){
        this->view.init(false);
        this->cinema.initTables();
        this->view.init(true);
    }

    this->orders = vector<Order>();
}


void TicketOffice::start() {
    bool isWorking = true;
    this->view.welcome();
    while (isWorking) {
        this->view.commands();
        int command = this->view.getCommand(1, 4);
        switch (command) {
            case 1: {
                this->order();
                break;
            }
            case 2: {
                this->schedule();
                break;
            }
            case 3: {
                this->showOrders();
                break;
            }
            case 4: {
                this->save();
                isWorking = false;
                break;
            }
            default: {
                throw out_of_range("no such command");
            }
        }
    }

}

void TicketOffice::order() {
    vector<DateTime> dates = this->cinema.getLatterDates();
    this->view.orderCommands(dates);

    int command = this->view.getCommand(1, this->cinema.getDaysSellTo());
    vector<Session> sessions = this->cinema.getSessionsByDate(dates[command - 1]);
    for (int i = 0; i < sessions.size(); ++i) {
        this->view.view(sessions[i], i + 1);
    }

    this->view.chooseSession();
    command = this->view.getCommand(1, sessions.size());
    Session session = sessions[command - 1];

    int places = View::inputNumber("Amount of usual places: ");
    int vipPlaces = View::inputNumber("Amount of VIP places: ");

    pair<bool, Order> result = this->cinema.createOrder(session, places, vipPlaces);
    if (result.first) {
        this->orders.push_back(result.second);
        this->view.order(true);
    } else {
        this->view.order(false);
    }

}

void TicketOffice::schedule() {
    vector<Session> sessions = this->cinema.getLatterSessions();
    for (int i = 0; i < sessions.size(); ++i) {
        this->view.view(sessions[i], i + 1);
    }
}

void TicketOffice::showOrders() {
    if (!this->orders.empty()) {
        this->view.ordersList(true);
        for (int i = 0; i < this->orders.size(); ++i) {
            this->view.view(this->orders[i], i + 1);
        }
        int number = View::inputNumber("Which to inspect: ");

        if (number > 0 && (number - 1) < this->orders.size()) {
            for (Ticket ticket : this->orders[number - 1].getTickets()) {
                this->view.view(ticket);
            }
        }
        int command = View::inputNumber("Do you want to cancel the order? (1 = yes, 0 = no)");
        if (command == 1) {
            this->orders.erase(this->orders.begin() + number - 1);
        }
    } else {
        this->view.ordersList(false);
    }
}

void TicketOffice::save() {
    for (Order order : this->orders) {
        this->cinema.saveSession(order.getSession());
    }
}



