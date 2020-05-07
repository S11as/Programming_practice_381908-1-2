//
// Created by Kirill on 23.04.2020.
//

#ifndef TASK5_HALL_H
#define TASK5_HALL_H


class Hall {
public:
    Hall(int id = 1, int price = 100, int vipPrice = 200, int places = 100, int vipPlaces = 50);

    inline int getPrice() { return this->price; }

    inline int getVipPrice() { return this->vipPrice; }

    inline int getId() { return this->id; }

    inline int getPlaces() const { return this->places; }

    inline int getVipPlaces() const { return this->vipPlaces; }

    int calculatePriceByHour(int hour);

    int calculateVipPriceByHour(int hour);

private:
    int id;
    int price;
    int vipPrice;
    int places;
    int vipPlaces;
};


#endif //TASK5_HALL_H
