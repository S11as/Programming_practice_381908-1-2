//
// Created by Kirill on 23.04.2020.
//

#include <chrono>
#include "../include/Cinema.h"
#include "../include/Connector.h"


Cinema::Cinema(const string &database, int daysSellTo) {
    this->connector = Connector(database);
    this->daysSellTo = daysSellTo;
}

void Cinema::initTables() {
    this->connector.initTemplateTable();
    this->connector.initHallTable();
    this->connector.initSessionTable();
}

vector<Session> Cinema::getLatterSessions() {
    vector<Session> sessions = vector<Session>();
    for (int i = 0; i < this->daysSellTo; ++i) {
        DateTime date = Cinema::currentDate(i);
        for (const Session &session : this->connector.getSessionsByDate(date)) {
            sessions.push_back(session);
        }
    }
    return sessions;
}

DateTime Cinema::currentDate(int add) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24 * add));
    struct tm *_time = std::localtime(&now_c);
    return DateTime(_time->tm_mday, _time->tm_mon + 1, _time->tm_year + 1900, _time->tm_hour, _time->tm_min);
}

vector<DateTime> Cinema::getLatterDates() {
    vector<DateTime> dates = vector<DateTime>();
    for (int i = 0; i < this->daysSellTo; ++i) {
        dates.push_back(Cinema::currentDate(i));
    }
    return dates;
}

vector<Session> Cinema::getSessionsByDate(const DateTime &date) {
    return this->connector.getSessionsByDate(date);
}

pair<bool, Order> Cinema::createOrder(Session &session, int places, int vipPlaces) {
    auto result = pair<bool, Order>(false, Order());
    if (session.validatePlaces(places, vipPlaces)) {
        result.first = true;
        Order order = Order(session);
        for (int i = 0; i < places; ++i) {
            order.append(session.makeTicket(false));
        }
        for (int i = 0; i < vipPlaces; ++i) {
            order.append(session.makeTicket(true));
        }
        result.second = order;
    }
    return result;
}

void Cinema::saveSession(const Session &session) {
    this->connector.save(session);
}

