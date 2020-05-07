//
// Created by Kirill on 29.03.2020.
//

#include <regex>
#include "../include/View.h"

View::View(const string &title) {
    this->belongsTo = title;
}

void View::welcome() {
    std::cout << this->belongsTo << std::endl;
    std::cout << "Welcome to the app which allows you to interact with your personal Film library" << std::endl;
}

void View::commands() {
    std::cout << "\n";
    std::cout << "Choose next action:" << std::endl;
    std::cout << "1.Add film" << std::endl;
    std::cout << "2.Find film by name and get information/change/delete it" << std::endl;
    std::cout << "3.All producer films" << std::endl;
    std::cout << "4.All films in particular year" << std::endl;
    std::cout << "5.N films with max box office" << std::endl;
    std::cout << "6.N films with max box office in particular year" << std::endl;
    std::cout << "7.Amount of films in library" << std::endl;
    std::cout << "8.Exit" << std::endl;
}

void View::subCommands() {
    std::cout << "Film was found, what do you want to do?" << std::endl;
    std::cout << "1.Print information" << std::endl;
    std::cout << "2.Change information" << std::endl;
    std::cout << "3.Delete film" << std::endl;
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

pair<string, int> View::search() {
    std::cout << "Searching for film" << std::endl;
    string name = View::inputName("Film's title: ", "", false);
    int year = View::inputNumber("Film's year (if you dont remember, enter 0): ");
    return pair<string, int>(name, year);
}

Film View::getNewFilm() {
    std::cout << "Input new film data" << std::endl;
    return View::inputFilm();
}

void View::newFilmStatus(const string &status) {
    std::cout << "Film " << status << " successfully" << std::endl;
}

void View::print(Film film) {
    std::cout << "Film information:" << std::endl;
    std::cout << "Producer: " << film.getProducer() << std::endl;
    std::cout << "Screenwriter: " << film.getScreenwriter() << std::endl;
    std::cout << "Composer: " << film.getComposer() << std::endl;
    std::cout << "Release date: " << film.getDate() << std::endl;
    std::cout << "Box office: " << film.getBoxOffice() << std::endl;
}

void View::shortPrint(Film film) {
    std::cout <<film.getName() << " " << "year:" << film.getYear()
              << "  box office:" << film.getBoxOffice() << std::endl;
}

void View::filmNotFound() {
    std::cout << "Film hasnt been found, please try again" << std::endl;
}

void View::empty(const string &reason) {
    std::cout << "There are no films of/in that " << reason << std::endl;
}

void View::noFilms(bool fewer) {
    if(fewer){
        std::cout<<"There are fewer films in library than you requested"<<std::endl;
    }else{
        std::cout<<"There are no films in library "<<std::endl;
    }
}

void View::count(int number){
    std::cout<<"There are "<<number<<" films"<<std::endl;
}

void View::exit(){
    std::cout<<"Exiting from library"<<std::endl;
}

Film View::inputFilm() {
    string name = View::inputName("Film title:", "", false);
    string producer = View::inputName("Producer:", "You need to enter lastname with one word");
    string writer = View::inputName("Screenwriter:", "You need to enter lastname with one word");
    string composer = View::inputName("Composer:", "You need to enter lastname with one word");
    int day = View::inputNumber("Day, when film was released:");
    int month = View::inputNumber("Month, when film was released:");
    int year = View::inputNumber("Year, when film was released:");
    int box_office = View::inputNumber("Film box office:");
    return Film(name, producer, writer, composer, Date(day, month, year), box_office);
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
