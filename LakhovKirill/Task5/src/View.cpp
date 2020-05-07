//
// Created by Kirill on 24.04.2020.
//

#include <iostream>
#include <regex>
#include "../include/View.h"

View::View(const string &cinemaName) {
    this->name = cinemaName;
}

void View::welcome() {
    std::cout << "Hello there! welcome to our Film Ticket office " << this->name << std::endl;
}

void View::commands() {
    std::cout << "\nHere is what you can do there" << std::endl;
    std::cout << "1. Start order" << std::endl;
    std::cout << "2. Get " << this->name << " schedule" << std::endl;
    std::cout << "3. Orders " << this->name << std::endl;
    std::cout << "4. Exit " << this->name << std::endl;
}

int View::inputNumber(const string &whatNumber) {
    string str;
    int number;
    while (true) {
        std::cout << whatNumber << std::endl;
        cin >> str;
        try {
            number = stoi(str);
            break;
        } catch (invalid_argument &e) {
            std::cout << "You need to enter a number" << std::endl;
        }
    }
    return number;
}

bool View::parser(const string &str) {
    regex oneWord(R"(^[a-zA-Z]+$)");
    smatch match;
    return regex_search(str, match, oneWord);
}

string View::inputName(const string &who, const string &error, bool strict) {
    string name;
    if (strict) {
        while (true) {
            std::cout << who << std::endl;
            cin >> name;
            if (View::parser(name)) {
                break;
            } else {
                std::cout << error << std::endl;
            }
        }
    } else {
        std::cout << who << std::endl;
        cin >> name;
    }
    return name;
}

int View::getCommand(int min, int max) {
    while (true) {
        int command = View::inputNumber("Command:");
        if (command >= min && command <= max) {
            return command;
        } else {
            std::cout << "No such command number, try again" << std::endl;
        }
    }
}

void View::view(const Session &session, int number) {
    std::cout << "\n" << std::endl;
    std::cout << "Session #" << number << std::endl;
    std::cout << this->name << "'s " << "Film: " << session.getName() << std::endl;
    std::cout << "Date: " << session.getDateTime().getFullDate() << std::endl;
    std::cout << "Hall #" << session.getHall().getId() << std::endl;
    std::cout << "Free places: " << session.getHall().getPlaces() - session.getOccupiedPlaces() << std::endl;
    std::cout << "Free VIP places: " << session.getHall().getVipPlaces() - session.getOccupiedVipPlaces() << std::endl;
    std::cout << "Standart place price: " << session.getPrice() << std::endl;
    std::cout << "VIP place price: " << session.getVipPrice() << std::endl;
}

void View::init(bool isFinished) {
    if (isFinished) {
        std::cout << this->name << "'s films are initialized\n" << std::endl;
    } else {
        std::cout << this->name << "'s films are being initialized" << std::endl;
    }
}

void View::orderCommands(vector<DateTime> dates) {
    std::cout << "Choose date" << std::endl;
    for (int i = 0; i < dates.size(); ++i) {
        std::cout << i + 1 << ". " << dates[i].getDate() << std::endl;
    }
}

void View::chooseSession() {
    std::cout << "Enter session's number" << std::endl;
}

void View::order(bool success) {
    if (success) {
        std::cout << "Order successfully stored" << std::endl;
    } else {
        std::cout << "Order cant be stored because there are not enough places. Try again" << std::endl;
    }
}

void View::ordersList(bool exists) {
    if (exists) {
        std::cout << "\nThe list of orders:" << std::endl;
    } else {
        std::cout << "\nThere are no orders yet!" << std::endl;
    }
}

void View::view(const Order &order, int number) {
    std::cout << "\nOrder #" << number << std::endl;
    std::cout << "Price: " << order.getPrice() << std::endl;
}

void View::view(const Ticket &ticket) {
    std::cout << "\n" << std::endl;
    std::cout << "Ticket" << std::endl;
    std::cout << "Date: " << ticket.getDateTime().getFullDate() << std::endl;
    std::cout << "Film: " << ticket.getName() << std::endl;
    std::cout << "Hall #" << ticket.getHall() << std::endl;
    std::cout << "Row: " << ticket.getRow() << " Place:" << ticket.getPlace() << std::endl;
}
