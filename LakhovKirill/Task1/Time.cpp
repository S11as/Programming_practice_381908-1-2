//
// Created by Kirill Lakhov on 12.02.2020.
//

#include <iostream>
#include <utility>
#include "Time.h"
#include "regex"

Time::Time(){
    this->hours = 0;
    this->min = 0;
    this->sec = 0;
    this->setForwardingZeros();
    this->calculateFullTime();
}

Time::Time(string s) {
    this->parseAndSet(s);
    this->calculateFullTime();
}

Time::Time(int n){
    this->sec = n;
    this->hours = 0;
    this->min = 0;
    this->castOverflow();
    this->setForwardingZeros();
    this->calculateFullTime();
}
Time::~Time(){
//    cout<<"Time destroyed"<<endl;
}
void Time::setHour(int _h) {
    this->hours = _h;
    if(_h>=24) this->castOverflow();
    this->sHours = Time::withForwardingZero(this->hours);
    this->calculateFullTime();
}
void Time::setHour(string _h){
    int h = stoi(_h);
    this->setHour(h);
}
void Time::setMin(int _m) {
    this->min = _m;
    if(_m>=60) this->castOverflow();
    this->sMin = Time::withForwardingZero(this->min);
    this->calculateFullTime();
}
void Time::setMin(string _m){
    int m = stoi(_m);
    this->setMin(m);
}
void Time::setSec(int _s) {
    this->sec = _s;
    if(_s>=60) this->castOverflow();
    this->sSec = Time::withForwardingZero(this->sec);
    this->calculateFullTime();
}
void Time::setSec(string _s){
    int s = stoi(_s);
    this->setSec(s);
}

void Time::setTime(int s){
    this->nullifyTime();
    this->sec = s;
    this->castOverflow();
    this->setForwardingZeros();
    this->calculateFullTime();
}

void Time::setTime(string s){
    this->nullifyTime();
    this->parseAndSet(s);
    this->calculateFullTime();
}

void Time::setForwardingZeros() {
    this->sSec = Time::withForwardingZero(this->sec);
    this->sMin = Time::withForwardingZero(this->min);
    this->sHours = Time::withForwardingZero(this->hours);
}
int Time::getHour() {
    return this->hours;
}
int Time::getMin() {
    return this->min;
}
int Time::getSec() {
    return this->sec;
}
void Time::getTime(){
    cout<<this->sHours +':' + this->sMin +':' + this->sSec<<endl;
}
string Time::getsTime(){
    return this->sHours +':' + this->sMin +':' + this->sSec;
}

bool Time::moreThan(Time _t) {
    return this->fullTime > _t.fullTime;
}
bool Time::moreThan(string _t) {
    Time *time = new Time(std::move(_t));
    return this->fullTime > time->fullTime;
}

void Time::addTime(Time _t) {
    this->setTime(this->fullTime + _t.fullTime);
}
void Time::addTime(string _s) {
    Time *time = new Time(_s);
    this->setTime(this->fullTime + time->fullTime);
}

void Time::subtractTime(Time _t) {
    int full = this->fullTime - _t.fullTime;
    if(full<0){
        this->setTime(Time::secInDay + full);
    }else{
        this->setTime(full);
    }
}
void Time::subtractTime(string _s) {
    Time *time = new Time(_s);
    int full = this->fullTime - time->fullTime;
    if(full<0){
        this->setTime(Time::secInDay + full);
    }else{
        this->setTime(full);
    }
}
string Time::withForwardingZero(int number) {
    if(number/10==0){
        return "0"+to_string(number);
    }else{
        return to_string(number);
    }
}

void Time::castOverflow() {
    if(this->sec >= 60){
        int secOverflow = this->sec/60;
        this->sec = (this->sec)-(this->sec/60)*60;
        this->min = (this->min)+secOverflow;
    }
    if(this->min >= 60){
        int minOverflow = (this->min)/60;
        this->min = (this->min)-(this->min/60)*60;
        this->hours = (this->hours)+minOverflow;
    }
    if(this->hours >= 24){
        this->hours = (this->hours)-(this->hours/24)*24;
    }
}

void Time::nullifyTime() {
    this->sec = 0;
    this->hours = 0;
    this->min = 0;
    this->setForwardingZeros();
}
void Time::calculateFullTime() {
    this->fullTime = (this->hours)*3600 + (this->min)*60 + this->sec;
}
void Time::parseAndSet(string s) {
    vector<int> times = Time::parser(std::move(s));
    if(!times.empty()){
        switch(times.size()){
            case 1:{
                this->sec=times[0];
                this->castOverflow();
                this->setForwardingZeros();
                break;
            }
            case 2:{
                this->hours= times[0];
                this->min = times[1];
                this->sec = 0;
                this->castOverflow();
                this->setForwardingZeros();
                break;
            }
            case 3:{
                this->hours = times[0];
                this->min = times[1];
                this->sec = times[2];
                this->castOverflow();
                this->setForwardingZeros();
                break;
            }
            default:{
                this->nullifyTime();
            }
        }
    }else{
        this->nullifyTime();
    }
}

vector<int> Time::parser(string s) {
    string templateS;
    try{
        regex regularTemplate(R"(((\d{1,9}:){0,2}\d{1,9}))");
        smatch match;
        if(regex_search(s, match, regularTemplate) && match.size()>1){
            templateS = match.str(1);
            if(templateS.length() == s.length()){
                try{
                    regex re(R"((\d{1,9})(:|\b))");
                    sregex_iterator next(s.begin(), s.end(), re);
                    sregex_iterator end;
                    vector<int>times;
                    while(next != end) {
                        smatch toMatch = *next;
                        string matched = toMatch.str();
                        if (matched.back() == ':') {
                            matched.erase(matched.length() - 1, 1);
                        }
                        times.push_back(stoi(matched));
                        next++;
                    }
                    return times;
                }catch (std::regex_error& e){}
            }
        }
    }catch (regex_error& e){}
    vector<int>a;
    return a;
}