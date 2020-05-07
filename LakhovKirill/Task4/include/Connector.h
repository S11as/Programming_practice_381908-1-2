//
// Created by Kirill on 29.03.2020.
//

#ifndef TASK4_CONNECTOR_H
#define TASK4_CONNECTOR_H

#include "string"
#include "Film.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include "vector"

using namespace std;
using namespace SQLite;

class Connector {
private:
    Database connect();

    void init();

    vector<Film> getByQuery(Statement &query, int amount=0);
public:
    Connector() = default;

    explicit Connector(const string &database);

    void insert(Film film);

    void remove(Film film);

    void update(Film which_film, Film update_to);

    pair<bool, Film> get(const string &name, int year);

    pair<bool, Film> get(const Film &film);

    int count(int year = 0);

    vector <Film> byProducer(const string& producer);

    vector <Film> byYear(int year);

    vector <Film> maxBoxOffice(int amount, int year);
private:
    string database;
    string table;
};


#endif //TASK4_CONNECTOR_H
