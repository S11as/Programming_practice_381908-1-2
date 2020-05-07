//
// Created by Kirill on 23.04.2020.
//

#ifndef TASK5_SESSION_H
#define TASK5_SESSION_H

#include "DateTime.h"
#include "Hall.h"
#include "Ticket.h"

class Session {
public:
    Session();

    Session(const string &name, Hall &hall, DateTime &date, int price, int vipPrice, int occupiedPlaces = 0,
            int occupiedVipPlaces = 0, int id = 0);

    bool validatePlaces(int places, int vipPlaces) const;

    Ticket makeTicket(bool isVip);

    inline string getName() const { return this->name; }

    inline Hall getHall() const { return this->hall; }

    inline DateTime getDateTime() const { return this->date; }

    inline int getPrice() const { return this->price; }

    inline int getVipPrice() const { return this->vipPrice; }

    inline int getOccupiedPlaces() const { return this->occupiedPlaces; }

    inline int getOccupiedVipPlaces() const { return this->occupiedVipPlaces; }

    inline int getId() const { return this->id; }

private:
    int id;
    string name;
    Hall hall;
    DateTime date;
    int price{};
    int vipPrice{};
    int occupiedPlaces{};
    int occupiedVipPlaces{};
    const static int PLACES_IN_ONE_ROW = 25;
};


#endif //TASK5_SESSION_H
