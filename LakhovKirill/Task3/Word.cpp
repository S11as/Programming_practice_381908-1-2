//
// Created by Kirill Lakhov on 17.02.2020.
//
#include "Word.h"
#include <vector>
#include <iostream>
#include "regex"

using namespace std;
Word::Word(){
    this->setNull();
}

Word::Word(string eng, string translation) {
    if(Word::parser(eng) && Word::parser(translation)){
        this->word = eng;
        vector<string> a;
        a.push_back(translation);
        this->translations = a;
        this->id = 0;
    }else{
        this->setNull();
    }
}

Word::Word(string eng, vector<string> translations) {
    if(Word::parser(eng) && Word::parser(translations)){
        this->word = eng;
        this->translations = translations;
        this->id = 0;
    }else{
        this->setNull();
    }
}

Word::Word(string eng, vector<string> translations, int _id) {
    if(Word::parser(eng) && Word::parser(translations)){
        this->word = eng;
        this->translations = translations;
        this->id = _id;
    }else{
        this->setNull();
    }
}
void Word::setTranslation(string translation) {
    if(Word::parser(translation)){
        vector<string> a;
        a.push_back(translation);
        this->translations = a;
    }
}

void Word::setTranslation(vector<string> translations) {
    if(Word::parser(translations)) this->translations = translations;
}

void Word::setWord(string word){
    if(Word::parser(word)) this->word = word;
}

void Word::addTranslation(string translation) {
    if(this->haveTranslation(translation)) return;
    if(Word::parser(translation)) this->translations.push_back(translation);
}

void Word::addTranslation(vector<string> translations) {
    for (const auto & translation : translations) {
        if(this->haveTranslation(translation)) continue;
        if(Word::parser(translation)) this->translations.push_back(translation);
    }
}

bool Word::haveTranslation(string translation) {
    for (const auto & i : this->translations) {
        if(i == translation) return true;
    }
    return false;
}

bool Word::parser(string word){
    regex onlyWord(R"(^[a-zA-ZÀ-ßà-ÿ¸¨]+$)");
    smatch match;
    bool res = regex_search(word,match, onlyWord);
    return res;
}

bool Word::parser(vector<string> words) {
    for(const auto& item : words){
        if(!Word::parser(item)) return false;
    }
    return true;
}
void Word::setNull(){
    this->word = "";
    this->translations = vector<string>();
    this->id = 0;
}

void Word::setId(int _id) {
    this->id = _id;
}

string Word::getWord() {
    return this->word;
}
int Word::getId(){
    return this->id;
}
vector<string> Word::getTranslations() {
    return this->translations;
}