//
// Created by Kirill on 23.04.2020.
//

#ifndef TASK5_CINEMA_H
#define TASK5_CINEMA_H

#include "Connector.h"
#include "Order.h"

class Cinema {
public:
    Cinema(const string &database = "cinema.db3", int daysSellTo = 3);

    void initTables();

    vector<Session> getLatterSessions();

    vector<DateTime> getLatterDates();

    inline int getDaysSellTo() const { return this->daysSellTo; };

    vector<Session> getSessionsByDate(const DateTime &date);

    pair<bool, Order> createOrder(Session &session, int places, int vipPlaces);

    void saveSession(const Session &session);

private:
    Connector connector;

    static DateTime currentDate(int add = 0);

    int daysSellTo;
};


#endif //TASK5_CINEMA_H
