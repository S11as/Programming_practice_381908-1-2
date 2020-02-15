//
// Created by Kirill Lakhov on 12.02.2020.
//

#ifndef TASK1_TIME_H
#define TASK1_TIME_H


using namespace std;

#include <string>
#include "vector"
class Time{
public:
    Time();
    Time(string s);
    Time(int n);
    ~Time();
    void setHour(int _h);
    void setMin(int _m);
    void setSec(int _s);
    void setHour(string _h);
    void setMin(string _m);
    void setSec(string _s);
    void setTime(int s);
    void setTime(string s);
    int getHour();
    int getMin();
    int getSec();
    string getsTime();
    void getTime();
    bool moreThan(Time _t);
    bool moreThan(string _t);
    void addTime(Time _t);
    void addTime(string _s);
    void subtractTime(Time _t);
    void subtractTime(string _t);
private:
    int hours;
    int min;
    int sec;
    int fullTime;
    string sHours;
    string sMin;
    string sSec;
    static const int secInDay = 24*60*60;
    void setForwardingZeros();
    static vector<int> parser(string s);
    static string withForwardingZero(int number);
    void castOverflow();
    void nullifyTime();
    void parseAndSet(string s);
    void calculateFullTime();
};

#endif //TASK1_TIME_H
