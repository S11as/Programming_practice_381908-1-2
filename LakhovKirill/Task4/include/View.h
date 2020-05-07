//
// Created by Kirill on 29.03.2020.
//

#ifndef TASK4_VIEW_H
#define TASK4_VIEW_H

#include <iostream>
#include "string"
#include "Film.h"

using namespace std;

class View {
public:
    View() = default;

    explicit View(const string &title);

    void welcome();

    void commands();

    void subCommands();

    int getCommand(int min, int max);

    Film getNewFilm();

    void newFilmStatus(const string &status);

    void print(Film film);

    void shortPrint(Film film);

    pair<string, int> search();

    void filmNotFound();

    void empty(const string& reason);

    void count(int number);

    void noFilms(bool fewer = false);

    void exit();

    static string inputName(const string &who, const string &error, bool strict = true);

    static int inputNumber(const string &whatNumber);


private:
    static Film inputFilm();

    static bool parser(const string &str);

private:
    string belongsTo;
};


#endif //TASK4_VIEW_H
