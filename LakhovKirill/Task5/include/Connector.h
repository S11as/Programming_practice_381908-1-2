//
// Created by Kirill on 23.04.2020.
//

#ifndef TASK5_CONNECTOR_H
#define TASK5_CONNECTOR_H

#include "string"
#include <SQLiteCpp/SQLiteCpp.h>
#include "vector"
#include "Hall.h"
#include "SessionTemplate.h"
#include "Session.h"

using namespace std;
using namespace SQLite;

class Connector {
public:
    Connector(const string &database = "cinema.db3");

    Database connect();

    void initTemplateTable();

    void initSessionTable();

    void initHallTable();

    int count(const string &table);

    Hall getHall(int id);

    SessionTemplate getSessionTemplate(int id);

    void save(const Session &session);

    vector<Session> getSessionsByDate(const DateTime &date);

private:
    string database;
    string table;

    static int rand(int a, int b);

    static struct tm *currentDate(int add = 0);
};


#endif //TASK5_CONNECTOR_H
