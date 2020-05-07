//
// Created by Kirill Lakhov on 13.03.2020.
//

#include <codecvt>
#include <utility>
#include "../include/Film.h"
#include "regex"

Film::Film(string name, string producer, string screenwriter, string composer, Date date, int box_office) {
    this->name =name;
    this->producer = Film::parser(producer) ? producer : "NotSet";
    this->screenwriter = Film::parser(screenwriter) ? screenwriter : "NotSet";
    this->composer = Film::parser(composer) ? composer : "NotSet";
    this->date = date;
    this->box_office = box_office;
}

bool Film::parser(const string &str) {
    regex oneWord(R"(^[a-zA-Z]+$)");
    smatch match;
    return regex_search(str,match,oneWord);
}
