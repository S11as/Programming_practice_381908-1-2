//
// Created by Kirill on 29.03.2020.
//

#include "../include/Connector.h"

Connector::Connector(const string &database) {
    this->database = database;
    this->table = "films";
    this->init();
}

Database Connector::connect() {
    Database db = Database(this->database, OPEN_CREATE | OPEN_READWRITE);
    return db;
}

void Connector::init() {
    Database db = this->connect();
//    db.exec("DROP TABLE IF EXISTS films");
    db.exec("CREATE TABLE IF NOT EXISTS  films (id INTEGER PRIMARY KEY , name TEXT NOT NULL, producer TEXT NOT NULL, "
            "screenwriter TEXT NOT NULL,  composer TEXT NOT NULL, day INTEGER NOT NULL, month INTEGER NOT NULL, year INTEGER NOT NULL,"
            " box_office INTEGER NOT NULL)");
}

void Connector::insert(Film film) {
    Database db = this->connect();
    Statement query = Statement(db, "INSERT INTO films VALUES (NULL, :name, :producer, :screenwriter, :composer, "
                                    ":day, :month, :year, :box_office)");
    query.bind(":name", film.getName());
    query.bind(":producer", film.getProducer());
    query.bind(":screenwriter", film.getScreenwriter());
    query.bind(":composer", film.getComposer());
    query.bind(":day", film.getDay());
    query.bind(":month", film.getMonth());
    query.bind(":year", film.getYear());
    query.bind(":box_office", film.getBoxOffice());
    query.exec();
}

void Connector::update(Film which_film, Film update_to) {
    Database db = this->connect();
    Statement query = Statement(db, "UPDATE films SET name=:name, producer=:producer,"
                                    " screenwriter=:screenwriter, composer=:composer, day=:day, month=:month,"
                                    "year=:year, box_office=:box_office WHERE name=:old_name AND year=:old_year");
    query.bind(":name", update_to.getName());
    query.bind(":producer", update_to.getProducer());
    query.bind(":screenwriter", update_to.getScreenwriter());
    query.bind(":composer", update_to.getComposer());
    query.bind(":day", update_to.getDay());
    query.bind(":month", update_to.getMonth());
    query.bind(":year", update_to.getYear());
    query.bind(":box_office", update_to.getBoxOffice());
    query.bind(":old_name", which_film.getName());
    query.bind(":old_year", which_film.getYear());
    query.exec();
}

void Connector::remove(Film film) {
    Database db = this->connect();
    Statement query = Statement(db, "DELETE FROM films WHERE name=:name AND year=:year");
    query.bind(":name", film.getName());
    query.bind(":year", film.getYear());
    query.exec();
}

pair<bool, Film> Connector::get(const string &name, int year) {
    Database db = this->connect();

    string line = "SELECT * FROM films WHERE name=:name";
    if (year != 0) line += " AND year=:year";
    Statement query = Statement(db, line);

    query.bind(":name", name);
    if (year != 0) query.bind(":year", year);
    if (query.executeStep()) {
        Film film = Film(query.getColumn("name"), query.getColumn("producer"),
                         query.getColumn("screenwriter"), query.getColumn("composer"),
                         Date(query.getColumn("day"), query.getColumn("month"), query.getColumn("year")),
                         query.getColumn("box_office"));
        return pair<bool, Film>(true, film);
    }
    return pair<bool, Film>(false, Film());
}

pair<bool, Film> Connector::get(const Film &film) {
    Database db = this->connect();

    string line = "SELECT * FROM films WHERE name=:name";
    if (film.getYear() != 0) line += " AND year=:year";
    Statement query = Statement(db, line);

    query.bind(":name", film.getName());
    if (film.getYear() != 0) query.bind(":year", film.getYear());
    if (query.executeStep()) {
        Film film = Film(query.getColumn("name"), query.getColumn("producer"),
                         query.getColumn("screenwriter"), query.getColumn("composer"),
                         Date(query.getColumn("day"), query.getColumn("month"), query.getColumn("year")),
                         query.getColumn("box_office"));
        return pair<bool, Film>(true, film);
    }
    return pair<bool, Film>(false, Film());
}

int Connector::count(int year) {
    Database db = this->connect();
    string line;
    if (year) {
        line = "SELECT COUNT(*) FROM films WHERE year=" + to_string(year);
    } else {
        line = "SELECT COUNT(*) FROM films";
    }
    Statement query(db, line);
    query.executeStep();
    return query.getColumn("COUNT(*)");
}

vector<Film> Connector::byProducer(const string &producer) {
    Database db = this->connect();
    Statement query = Statement(db, "SELECT * FROM films WHERE producer=:producer");
    query.bind(":producer", producer);
    return this->getByQuery(query);
}

vector<Film> Connector::byYear(int year) {
    Database db = this->connect();
    Statement query = Statement(db, "SELECT * FROM films WHERE year=:year");
    query.bind(":year", year);
    return this->getByQuery(query);
}

vector <Film> Connector::maxBoxOffice(int amount, int year){
    string lineQuery = "SELECT * FROM films";
    if (year) {
        lineQuery += " WHERE year=" + to_string(year);
    }
    lineQuery += " ORDER BY box_office DESC";
    Database db = this->connect();
    Statement query = Statement(db, lineQuery);

    return this->getByQuery(query, amount);
}

vector<Film> Connector::getByQuery(Statement &query, int amount) {
    vector<Film> result = vector<Film>();
    if (query.executeStep()) {
        if (!amount) {
            do {
                result.emplace_back(query.getColumn("name"), query.getColumn("producer"),
                                      query.getColumn("screenwriter"), query.getColumn("composer"),
                                      Date(query.getColumn("day"), query.getColumn("month"),
                                           query.getColumn("year")),query.getColumn("box_office"));
            } while (query.executeStep());
        } else {
            int times = 1;
            do {
                result.emplace_back(query.getColumn("name"), query.getColumn("producer"),
                                    query.getColumn("screenwriter"), query.getColumn("composer"),
                                    Date(query.getColumn("day"), query.getColumn("month"),
                                         query.getColumn("year")),query.getColumn("box_office"));
                times++;
            } while (query.executeStep() && times <= amount);
        }
    }
    return result;
}



