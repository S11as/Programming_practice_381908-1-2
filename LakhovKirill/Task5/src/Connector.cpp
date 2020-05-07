//
// Created by Kirill on 23.04.2020.
//

#include "../include/Connector.h"
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

Database Connector::connect() {
    Database db = Database(this->database, OPEN_CREATE | OPEN_READWRITE);
    return db;
}

Connector::Connector(const string &database) {
    this->database = database;
}

void Connector::initTemplateTable() {
    Database db = this->connect();
    db.exec("DROP TABLE IF EXISTS sessions_template");
    db.exec("CREATE TABLE IF NOT EXISTS  sessions_template (id INTEGER PRIMARY KEY , name TEXT NOT NULL,"
            " minute INTEGER NOT NULL, hour INTEGER NOT NULL)");

    for (int i = 0; i < 10; ++i) {
        Statement query = Statement(db, "INSERT INTO sessions_template VALUES (NULL, :name, :minute, :hour)");
        query.bind(":name", "Film" + to_string(i));
        query.bind(":hour", Connector::rand(0, 23));
        query.bind(":minute", Connector::rand(0, 59));
        query.exec();
    }
}

int Connector::rand(int a, int b) {
    std::mt19937 generator(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
    std::uniform_int_distribution<> uid(a, b);
    return uid(generator);
}

void Connector::initHallTable() {
    Database db = this->connect();
    db.exec("DROP TABLE IF EXISTS halls");
    db.exec("CREATE TABLE IF NOT EXISTS  halls (id INTEGER PRIMARY KEY , price INTEGER NOT NULL, vip_price INTEGER NOT NULL,"
            " places INTEGER NOT NULL, vip_places INTEGER NOT NULL)");

    for (int i = 0; i < 5; ++i) {
        Statement query = Statement(db, "INSERT INTO halls VALUES (NULL, :price, :vip_price, :places, :vip_places)");
        int allPlaces = Connector::rand(200, 300);
        int vipPlaces = Connector::rand(50, 100);
        int places = allPlaces - vipPlaces;
        int price = Connector::rand(50, 250);
        int vipPrice = price * 2;
        query.bind(":price", price);
        query.bind(":vip_price", vipPrice);
        query.bind(":places", places);
        query.bind(":vip_places", vipPlaces);
        query.exec();
    }
}

void Connector::initSessionTable() {
    Database db = this->connect();
    db.exec("DROP TABLE IF EXISTS sessions");
    db.exec("CREATE TABLE IF NOT EXISTS  sessions (id INTEGER PRIMARY KEY, name TEXT NOT NULL, hall INTEGER NOT NULL,"
            " day INTEGER NOT NULL, month INTEGER NOT NULL, year INTEGER NOT NULL, minute INTEGER NOT NULL, hour INTEGER NOT NULL,"
            "occupied_places INTEGER NOT NULL, occupied_vip_places INTEGER NOT NULL, price INTEGER NOT NULL, vip_price INTEGER NOT NULL)");

    for (int i = 0; i < 30; ++i) {
        int filmsInTheDay = Connector::rand(1, 5);
        vector<int> ids = vector<int>();
        int j = 0;
        while (j < filmsInTheDay) {
            int hallId = Connector::rand(1, this->count("halls"));
            int sessionId = Connector::rand(1, this->count("sessions_template"));
            if (binary_search(ids.begin(), ids.end(), hallId)) {
                continue;
            }
            Hall hall = this->getHall(hallId);
            SessionTemplate sessionTemplate = this->getSessionTemplate(sessionId);

            int hour = sessionTemplate.getHour();

            DateTime dateTime = DateTime(Connector::currentDate(i)->tm_mday, Connector::currentDate(i)->tm_mon + 1,
                                         Connector::currentDate(i)->tm_year + 1900,
                                         sessionTemplate.getHour(),
                                         sessionTemplate.getMinute());

            Session session = Session(sessionTemplate.getName(), hall, dateTime, hall.calculatePriceByHour(hour),
                                      hall.calculateVipPriceByHour(hour), Connector::rand(1, hall.getPlaces()),
                                      Connector::rand(1, hall.getVipPlaces())
            );
            this->save(session);
            j++;
        }
    }
}

int Connector::count(const string &table) {
    Database db = this->connect();
    Statement query(db, "SELECT COUNT(*) FROM " + table);
    query.executeStep();
    return query.getColumn("COUNT(*)");
}

Hall Connector::getHall(int id) {
    Database db = this->connect();
    Statement query(db, "SELECT * FROM halls WHERE id=" + to_string(id));
    query.executeStep();
    return Hall(query.getColumn("id"), query.getColumn("price"), query.getColumn("vip_price"),
                query.getColumn("places"), query.getColumn("vip_places"));
}

SessionTemplate Connector::getSessionTemplate(int id) {
    Database db = this->connect();
    Statement query(db, "SELECT * FROM sessions_template WHERE id=" + to_string(id));
    query.executeStep();
    return SessionTemplate(query.getColumn("id"), query.getColumn("name"), query.getColumn("minute"),
                           query.getColumn("hour"));
}

struct tm *Connector::currentDate(int add) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24 * add));
    return std::localtime(&now_c);
}

void Connector::save(const Session &session) {
    Database db = this->connect();
    if (session.getId() == 0) {
        Statement query = Statement(db, "INSERT INTO sessions VALUES (NULL, :name, :hall, "
                                        ":day, :month, :year, :minute, :hour, :occupied_places, :occupied_vip_places,"
                                        ":price, :vip_price)");
        query.bind(":name", session.getName());
        query.bind(":hall", session.getHall().getId());
        query.bind(":day", session.getDateTime().getDay());
        query.bind(":month", session.getDateTime().getMonth());
        query.bind(":year", session.getDateTime().getYear());
        query.bind(":minute", session.getDateTime().getMinute());
        query.bind(":hour", session.getDateTime().getHour());
        query.bind(":occupied_places", session.getOccupiedPlaces());
        query.bind(":occupied_vip_places", session.getOccupiedVipPlaces());
        query.bind(":price", session.getPrice());
        query.bind(":vip_price", session.getVipPrice());
        query.exec();
    } else {
        Statement query = Statement(db, "UPDATE sessions SET occupied_places=:occupied_places, "
                                        "occupied_vip_places=:occupied_vip_places "
                                        "WHERE day=:day AND month=:month AND year=:year AND minute=:minute AND hour=:hour");

        query.bind(":day", session.getDateTime().getDay());
        query.bind(":month", session.getDateTime().getMonth());
        query.bind(":year", session.getDateTime().getYear());
        query.bind(":minute", session.getDateTime().getMinute());
        query.bind(":hour", session.getDateTime().getHour());
        query.bind(":occupied_places", session.getOccupiedPlaces());
        query.bind(":occupied_vip_places", session.getOccupiedVipPlaces());
        query.exec();
    }

}

vector<Session> Connector::getSessionsByDate(const DateTime &date) {
    Database db = this->connect();
    Statement query(db, "SELECT * FROM sessions WHERE day=:day AND month=:month AND year=:year");
    query.bind(":day", date.getDay());
    query.bind(":month", date.getMonth());
    query.bind(":year", date.getYear());

    vector<Session> sessions = vector<Session>();
    while (query.executeStep()) {
        Hall hall = this->getHall(query.getColumn("hall"));
        DateTime dateTime = DateTime(query.getColumn("day"), query.getColumn("month"), query.getColumn("year"),
                                     query.getColumn("hour"), query.getColumn("minute"));
        sessions.emplace_back(query.getColumn("name"), hall, dateTime, query.getColumn("price"),
                              query.getColumn("vip_price"), query.getColumn("occupied_places"),
                              query.getColumn("occupied_vip_places"), query.getColumn("id"));
    }
    return sessions;
}
