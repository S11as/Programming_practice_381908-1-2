

#include "../include/FilmLibrary.h"

#include <utility>
#include <iostream>
#include <regex>
#include <codecvt>

using namespace std;
using namespace SQLite;

FilmLibrary::FilmLibrary(const string& database, const string& title) {
    this->database = database;
    this->connector = Connector(this->database);
    this->view = View(title);
}


void FilmLibrary::start() {
    bool isWorking = true;
    this->view.welcome();
    while(isWorking){
        this->view.commands();
        int command = this->view.getCommand(1,8);
        switch (command) {
            case 1: {
                this->createNewFilmCommand();
                break;
            }
            case 2: {
                this->findFilmCommand();
                break;
            }
            case 3: {
                this->allProducerFilmsCommand();
                break;
            }
            case 4: {
                this->allYearFilmsCommand();
                break;
            }
            case 5: {
                this->maxBoxOfficeCommand();
                break;
            }
            case 6: {
                this->maxBoxOfficeCommand(true);
                break;
            }
            case 7: {
                this->allFilmsCountCommand();
                break;
            }
            case 8:{
                this->view.exit();
                isWorking = false;
                break;
            }
            default: {
                throw out_of_range("no such command");
            }
        }
    }
}

void FilmLibrary::createNewFilmCommand() {
    Film film = this->view.getNewFilm();
    pair<bool, Film> result = this->connector.get(film);
    if (result.first) {
        this->connector.update(result.second, film);
        this->view.newFilmStatus("is already in library, rewriting");
    } else {
        this->connector.insert(film);
        this->view.newFilmStatus("created");
    }
}

void FilmLibrary::findFilmCommand() {
    pair<string, int> searchData = this->view.search();
    pair<bool, Film> result = this->connector.get(searchData.first, searchData.second);
    if (result.first) {
        this->view.subCommands();
        int command = this->view.getCommand(1,3);
        switch (command) {
            case 1: {
                this->view.print(result.second);
                break;
            }
            case 2: {
                this->changeFilmCommand(result.second);
                this->view.newFilmStatus("changed");
                break;
            }
            case 3: {
                this->connector.remove(result.second);
                this->view.newFilmStatus("deleted");
                break;
            }
            default:{
                throw out_of_range("no such command");
            }
        }
    } else {
        this->view.filmNotFound();
    }
}

void FilmLibrary::changeFilmCommand(const Film &to_change) {
    Film new_film = this->view.getNewFilm();
    this->connector.update(to_change, new_film);
}

void FilmLibrary::allProducerFilmsCommand() {
    string producer = View::inputName("Producer", "Input producer's lastname as one word");
    vector<Film> films = this->connector.byProducer(producer);
    if(films.empty()){
        this->view.empty("producer");
    }else{
        for(auto const& film : films){
            this->view.shortPrint(film);
        }
    }
}

void FilmLibrary::allYearFilmsCommand() {
    int year = View::inputNumber("Year, when films were released: ");
    vector<Film> films = this->connector.byYear(year);
    if(films.empty()){
        this->view.empty("year");
    }else{
        for(auto const& film : films){
            this->view.shortPrint(film);
        }
    }
}

void FilmLibrary::maxBoxOfficeCommand(bool isYear) {
    int filmAmount = View::inputNumber("Amount of films: ");
    int allFilms = this->connector.count();
    bool tooMuch = filmAmount > allFilms;
    filmAmount = tooMuch ? allFilms : filmAmount;
    int year = 0;
    if(isYear) year = View::inputNumber("Year:");
    vector<Film> films = this->connector.maxBoxOffice(filmAmount, year);
    if(films.empty()){
        this->view.noFilms();
    }else{
        for(auto const& film : films){
            this->view.shortPrint(film);
        }
    }
    if (tooMuch && !films.empty()) this->view.noFilms(true);
}

void FilmLibrary::allFilmsCountCommand() {
    this->view.count(this->connector.count());
}





