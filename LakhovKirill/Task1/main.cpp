#include <iostream>
#include "Time.h"
using namespace std;

int main() {
    //Обзор конструкторов
    Time *empty = new Time();//без аргументов
    empty->getTime();//инициализируется как 00:00:00

    Time *inSecI = new Time(120);// int, понимаем его как количество секунд
    inSecI->getTime(); // 00:02:00

    Time *inSecS = new Time("180");  // аналогично со строкой
    inSecS->getTime();//00:03:00

    Time *pair = new Time("12:25"); //пара с : понимаем ее как часы-минуты
    pair->getTime(); // 12:25:00

    Time *full = new Time("13:33:15"); //полный набор
    full->getTime();//13:33:15

    Time *overflow = new Time("72:120:9999"); //переполненные значения часов/минут/секунд (можно чего-то одного)
    //они будут cast'нуты в корректное время с отбрасыванием лишних суток
    overflow->getTime();//04:46:39

    Time *incorrect = new Time("wasd:12:56"); //некоректное значение будет инициализировано как нулевое
    incorrect->getTime();//00:00:00

    //Getters Setters
    Time *toSetS = new Time();
    toSetS->setSec("30"); // Установить значения любого из параметров строкой
    toSetS->setMin("45");
    toSetS->setHour("23");
    toSetS->getTime(); //23:45:30

    Time *toSetI = new Time();
    toSetI->setSec(30); // Аналогично числом
    toSetI->setMin(45);
    toSetI->setHour(23);
    toSetI->getTime(); //23:45:30

    Time *set = new Time("12:20");
    //переопределить уже имеющееся время
    set->setTime("15:30");
    set->getTime();// 15:30

    set->setTime(1200);//то же самое в секундах
    set->getTime();//00:20:00

    //получить какое либо значение
    int sec = toSetI->getSec();
    int min = toSetI->getMin();
    int hour = toSetI->getHour();

    //Операция сравнения

    //сравнивать можно как экземпляры Time
    Time *a = new Time("12:00");
    Time *b = new Time(1200);
    bool result = a->moreThan(*b); //метод moreThan() возвращает bool с результатом операции (сравнение строгое)
    cout<<result<<endl;//true

    //так и некий экземпляр Time с сформированным временем
    Time *c = new Time();
    result = c->moreThan("1:23");
    cout<<result<<endl;//false

    // Операции сложения
    Time *d = new Time("2:00");
    Time *e = new Time("3:00");
    //Сложение двух экземляров Time
    d->addTime(*e); //05:00:00
    d->getTime();

    //Сложение Time и строки
    d->addTime("5:20");
    d->getTime();//10:20:00

    //Операции вычитания
    d->subtractTime(*e);
    d->getTime();//07:20:00

    //при переполнении (появление отрицательного времени) происходит сдвиг назад
    //07:20:00 - 10:00:00 = 21:20:00
    d->subtractTime("10:00");
    d->getTime();//21:20:00
    return 0;
}

