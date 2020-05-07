//
// Created by Kirill on 23.04.2020.
//

#include "../include/Session.h"

Session::Session() = default;

Session::Session(const string &name, Hall &hall, DateTime &date, int price, int vipPrice, int occupiedPlaces,
                 int occupiedVipPlaces, int id) {
    this->name = name;
    this->hall = hall;
    this->date = date;
    this->price = price;
    this->vipPrice = vipPrice;
    this->occupiedPlaces = occupiedPlaces;
    this->occupiedVipPlaces = occupiedVipPlaces;
    this->id = id;
}

bool Session::validatePlaces(int places, int vipPlaces) const {
    if (places <= 0 && vipPlaces <= 0)
        return false;
    int freePlaces = this->hall.getPlaces() - this->occupiedPlaces;
    int freeVipPlaces = this->hall.getVipPlaces() - this->occupiedVipPlaces;
    return (freePlaces >= places) && (freeVipPlaces >= vipPlaces);
}

Ticket Session::makeTicket(bool isVip) {
    //считаем что все VIP сидят в конце зала, после стандартов
    if (isVip) {
        this->occupiedVipPlaces++;
        int occupiedRows = (this->hall.getPlaces() + this->occupiedVipPlaces) / Session::PLACES_IN_ONE_ROW;
        int row = occupiedRows + 1;
        int place = (this->hall.getPlaces() + this->occupiedVipPlaces) - occupiedRows * Session::PLACES_IN_ONE_ROW;
        place = place == 0 ? 25 : place;
        return Ticket(this->hall.getId(), row, place, this->vipPrice, this->getDateTime(), this->getName());
    } else {
        this->occupiedPlaces++;
        int occupiedRows = (this->occupiedPlaces / Session::PLACES_IN_ONE_ROW);
        int row = occupiedRows + 1;
        int place = this->occupiedPlaces - occupiedRows * Session::PLACES_IN_ONE_ROW;
        place = place == 0 ? 25 : place;
        return Ticket(this->hall.getId(), row, place, this->price, this->getDateTime(), this->getName());
    }
}

