//
// Created by Kirill Lakhov on 19.02.2020.
//

#include "Dictionary.h"
#include <string>
#include <vector>
#include <iostream>
#include "Word.h"
#include "fstream"

using namespace std;

Dictionary::Dictionary() {
    this->words = vector<Word *>{};
}

Dictionary::Dictionary(string filename) {
    this->in(filename);
}

Dictionary::Dictionary(Dictionary *dictionary) {
    this->words = dictionary->getAll();
}

bool Dictionary::addWord(Word *word) {
    if (word->getWord().length() && word->getTranslations().size()) {
        if (!this->find(*word)) {
            this->words.push_back(word);
            word->setId(this->wordsCount());
            return true;
        } else {
            this->deleteWord(*word);
            this->words.push_back(word);
            word->setId(this->wordsCount());
            return false;
        }
    }
    return false;
}

bool Dictionary::mergeAddWord(Word *word) {
    if (!this->find(*word)) {
        this->words.push_back(word);
        word->setId(this->wordsCount());
    } else {
        auto wordInDictionary = this->get(*word);
        wordInDictionary->addTranslation(word->getTranslations());
    }
    return true;
}

int Dictionary::find(Word word) {
    for (int i = 0; i < this->wordsCount(); ++i) {
        if (this->words[i]->getWord() == word.getWord()) return i + 1;
    }
    return 0;
}

int Dictionary::find(string word) {
    for (int i = 0; i < this->wordsCount(); ++i) {
        if (this->words[i]->getWord() == word) return i + 1;
    }
    return 0;
}

Word *Dictionary::get(Word word) {
    int id = this->find(word) - 1;
    return this->words[id];
}

Word *Dictionary::get(string word) {
    int id = this->find(word) - 1;
    return this->words[id];
}

vector<Word *> Dictionary::getAll() const {
    return this->words;
}

bool Dictionary::deleteWord(Word word) {
    for (int i = 0; i < this->wordsCount(); ++i) {
        if (this->words[i]->getWord() == word.getWord()) {
            this->words.erase(this->words.begin() + i);
            this->shuffleIds();
            return true;
        }
    }
    return false;
}

bool Dictionary::deleteWord(string word) {
    for (int i = 0; i < this->wordsCount(); ++i) {
        if (this->words[i]->getWord() == word) {
            this->words.erase(this->words.begin() + i);
            this->shuffleIds();
            return true;
        }
    }
    return false;
}

int Dictionary::wordsCount() {
    return this->words.size();
}

void Dictionary::shuffleIds() {
    for (int i = 0; i < this->wordsCount(); ++i) {
        this->words[i]->setId(i);
    }
}

bool Dictionary::out(string filename) {
    fstream file;
    file.open(filename, fstream::out);
    if (file.is_open()) {
        file << this->wordsCount() << "\n";
        for (Word *word : this->words) {
            file << word->getWord() << " ";
            file << word->getTranslations().size() << " ";
            for (const string &translation : word->getTranslations()) {
                file << translation << " ";
            }
            file << "\n" << "";
        }
        return true;
    }
    return false;
}

bool Dictionary::in(string filename) {
    ifstream file;
    file.open(filename, fstream::in);
    if (file.is_open()) {
        int count;
        file >> count;
        vector<Word *> newWords;
        for (int i = 0; i < count; ++i) {
            string word;
            int translationCount;
            vector<string> translations;
            file >> word;
            file >> translationCount;
            for (int j = 0; j < translationCount; ++j) {
                string translation;
                file >> translation;
                translations.push_back(translation);
            }
            newWords.push_back(new Word(word, translations, i));
        }
        this->words = newWords;
        return true;
    } else {
        return false;
    }
}

void Dictionary::destroy() {
    this->words = vector<Word *>{};
}

Dictionary::~Dictionary() {
//    std::cout<<"dictionary destroyed"<<std::endl;
}

bool Dictionary::merge(Dictionary *toMerge) {
    for (Word *word : toMerge->getAll()) {
        if (!this->find(*word)) this->addWord(word);
    }
    return true;
}

bool Dictionary::merge(string filename) {
    auto toMerge = new Dictionary();
    if (toMerge->in(filename)) {
        this->merge(toMerge);
        return true;
    }
    return false;
}

bool Dictionary::merge(const Dictionary &toMerge) {
    for (Word *word : toMerge.getAll()) {
        if (!this->find(*word)) this->addWord(word);
    }
    return true;
}

Dictionary &Dictionary::operator+=(const Dictionary &toAdd) {
    this->merge(toAdd);
    return *this;
}

Dictionary operator+(const Dictionary &first, const Dictionary &second) {
    Dictionary dictionary = Dictionary(first);
    dictionary+=second;
    return dictionary;
}

Dictionary &Dictionary::operator=(const Dictionary &copy) {
    this->words = copy.getAll();
    return *this;
}