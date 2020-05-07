//
// Created by Kirill on 23.04.2020.
//

#include "../include/Hall.h"

Hall::Hall(int id, int price, int vipPrice, int places, int vipPlaces) {
    this->id = id;
    this->price = price;
    this->vipPrice = vipPrice;
    this->places = places;
    this->vipPlaces = vipPlaces;
}

int Hall::calculatePriceByHour(int hour) {
    if (hour >= 18 && hour <= 23) {
        return this->price + (int) this->price * 0.5;
    } else if (hour >= 0 && hour <= 12) {
        return this->price - (int) this->price * 0.25;
    }
    return this->price;
}

int Hall::calculateVipPriceByHour(int hour) {
    if (hour >= 18 && hour <= 23) {
        return this->vipPrice + (int) this->vipPrice * 0.5;
    } else if (hour >= 0 && hour <= 12) {
        return this->vipPrice - (int) this->vipPrice * 0.25;
    }
    return this->vipPrice;
}
