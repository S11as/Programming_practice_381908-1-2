//
// Created by Kirill Lakhov on 19.02.2020.
//
#include "Word.h"
#include "Dictionary.h"
#include "vector"
#include "iostream"
#include "string"

int main(){
    setlocale(LC_ALL, "Russian");
    //Работа со словами

    //Создание слова
    auto word1 = new Word(); //без перевода и слова
    auto word2 = new Word("cat","кот"); //слово и один перевод
    auto word3 = new Word("cake", vector<string>{"торт","пирожное"}); //слово и несколько перводов

    //установить слово
    word1->setWord("dog");

    //уставновить перевод(заменяет имеющийся) (можно задать несколько переводов вектором)
    word1->setTranslation("собака");

    //добавить перевод(если такого еще нет, добавит) (можно задать несколько переводов вектором)
    word1->addTranslation("собачка");

    word3->setTranslation(vector<string>{"торт123","!@#."}); //строки не из букв не будут допущены

    //Получить значение слова
    string val = word1->getWord();

    //Получить vector переводов
    vector<string> translations = word1->getTranslations();


    //Работа со словарем

    //Пустой словарь
    auto dictionary  = new Dictionary();

    //Словарь из файла

    //**Все операции над словарем возвращают true/false означающие успех или неудачу операции**

    //Добавить слова в словарь
    dictionary->addWord(word1);
    dictionary->addWord(word2);
    dictionary->addWord(word3);
    //изменения на слове влияют на него внутри словаря (если они добавлены, разумеется)
    word1->addTranslation("пес");

    //Если слово с таким значением уже существует, оно будет полностью перезаписано
    auto word4 = new Word("cat", "кошка");
    dictionary->addWord(word4);

    //Используя специальный метод добавления слова, в случае его существования в словаре, переводы будут смешаны
    dictionary->mergeAddWord(word2);

    //проверить наличие слова в словаре (0 - если слова нет, иначе его id)
    dictionary->find("cat");

    //Получить ссылку на слово в словаре (перед этим желательно проверить его наличие в словаре)
    if(dictionary->find("dog")) auto word5 = dictionary->get("dog");

    //Узнать количество слов в словаре
    int amount = dictionary->wordsCount();

    //Записать словарь со всеми изменениями в текстовый файл (.txt)
    dictionary->out("myDictionary.txt");

    //Получить словарь из файла
    auto inDictionary = new Dictionary("myDictionary.txt");

    //Можно полностью переписать уже готовый
    //dictionary->in("myDictionary.txt");

    //совершить некоторые действия со словарем
    if(inDictionary->find("cake")) {
        Word* myWord = inDictionary->get("cake");
        myWord->setTranslation("кекс");
    }
    auto word6 = new Word("beauty", "красота");
    inDictionary->mergeAddWord(word6);

    //вновь записать его куда либо
    inDictionary->out("changedDictionary.txt");

    //Слияние словарей
    auto mergeDictionary1 = new Dictionary();
    mergeDictionary1->addWord(new Word("foraging","фуражировка"));
    mergeDictionary1->addWord(new Word("steelmaker",vector<string>{"сталевар","металлург"}));

    //слияние с проинициализированным ранее
    mergeDictionary1->merge(dictionary);
    mergeDictionary1->out("firstMerge.txt");

    auto mergeDictionary2 = new Dictionary();
    mergeDictionary2->addWord(new Word("mindless",vector<string>{"бессмысленный","глупый"}));
    mergeDictionary2->addWord(new Word("capsule", "капсула"));

    //слияние с словарем из файла
    mergeDictionary2->merge("changedDictionary.txt");
    mergeDictionary2->out("secondMerge.txt");

    //слить два словаря в новый с помощью "+"
    Dictionary md1 = *mergeDictionary1;
    Dictionary md2 = *mergeDictionary2;
    Dictionary md3 = md1 + md2;
    md3.out("thirdMerge.txt");

    //перегрузка присваивания

    //через оператор присваивания
    auto copiedDict1 = md1;
    copiedDict1.addWord(new Word("astronomy", "астрономия"));
    //через конструктор
    auto copiedDict2 = Dictionary(md1);
    copiedDict2.addWord(new Word("hotel","гостиница"));

    //внесенные изменения не влияют на словарь-основу (в выходном файле не должно быть слов astronomy или hotel)
    md1.out("firstMerge.txt");

    copiedDict1.out("firstCopy.txt");
    copiedDict2.out("secondCopy.txt");
    return 0;
}

