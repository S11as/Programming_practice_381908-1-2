//
// Created by Kirill Lakhov on 17.02.2020.
//

#ifndef TASK3_WORD_H
#define TASK3_WORD_H

#include <string>
#include <vector>
using namespace std;
class Word {
public:
    Word();
    Word(string eng, string translation);
    Word(string eng, vector<string> translations);
    Word(string eng, vector<string> translations, int _id);
    void setTranslation(string translation);
    void setTranslation(vector<string> translations);
    void addTranslation(string translation);
    void addTranslation(vector<string> translations);
    void setWord(string word);
    void setId(int _id);
    bool haveTranslation(string translation);
    string getWord();
    int getId();
    vector<string> getTranslations();
private:
    int id;
    string word;
    vector<string> translations;
    static bool parser(string word);
    static bool parser(vector<string> words);
    void setNull();
};


#endif //TASK3_WORD_H
