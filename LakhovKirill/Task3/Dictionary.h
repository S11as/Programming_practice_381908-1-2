//
// Created by Kirill Lakhov on 19.02.2020.
//

#ifndef TASK3_DICTIONARY_H
#define TASK3_DICTIONARY_H


#include <string>
#include <vector>
#include "Word.h"
using namespace std;
class Dictionary {
public:
    Dictionary();
    explicit Dictionary(string filename);
    explicit Dictionary(Dictionary* dictionary);
    ~Dictionary();
    bool addWord(Word* word);
    bool mergeAddWord(Word *word);
    bool deleteWord(string word);
    bool deleteWord(Word word);
    int find(string word);
    int find(Word word);
    Word* get(string word);
    Word* get(Word word);
    vector<Word*> getAll();
    int wordsCount();
    bool out(string filename);
    bool in(string filename);
    bool merge(string filename);
    bool merge(Dictionary* toMerge);
    bool merge(Dictionary &toMerge);
    friend Dictionary operator+ (Dictionary& first, Dictionary& second);
    Dictionary operator= (Dictionary &copy);
private:
    void shuffleIds();
    vector<Word*> words;
    void destroy();
};


#endif //TASK3_DICTIONARY_H
