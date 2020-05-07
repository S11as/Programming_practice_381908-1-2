//
// Created by Kirill on 24.04.2020.
//

#ifndef TASK5_VIEW_H
#define TASK5_VIEW_H

#include <string>
#include "Session.h"
#include "Order.h"
#include "Ticket.h"

using namespace std;

class View {
public:
    View(const string &cinemaName = "Cinema");

    void welcome();

    void commands();

    int getCommand(int min, int max);

    void orderCommands(vector<DateTime> dates);

    void view(const Session &session, int number);

    void view(const Order &order, int number);

    void view(const Ticket &ticket);

    void init(bool isFinished);

    void chooseSession();

    void order(bool success);

    void ordersList(bool exists);

    static int inputNumber(const string &whatNumber);

private:
    string name;

    static string inputName(const string &who, const string &error, bool strict = true);

    static bool parser(const string &str);
};


#endif //TASK5_VIEW_H
