

#ifndef TASK4_FILMLIBRARY_H
#define TASK4_FILMLIBRARY_H

#include "SQLiteCpp/SQLiteCpp.h"
#include "Film.h"
#include "Connector.h"
#include "View.h"

using namespace std;
using namespace SQLite;

class FilmLibrary {
private:
    string database="films.db3";
    Connector connector;
    View view;
public:
    FilmLibrary(const string& database="films.db3", const string& title="film-library-1");

    void start();

private:

    void createNewFilmCommand();

    void findFilmCommand();


    void changeFilmCommand(const Film &to_change);

    void allProducerFilmsCommand();

    void allYearFilmsCommand();

    void maxBoxOfficeCommand(bool isYear = false);

    void allFilmsCountCommand();

};


#endif //TASK4_FILMLIBRARY_H
