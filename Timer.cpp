#include "Timer.h"
#include <windows.h>
#include <time.h>
#include <cstdio>
#include <iostream>

///Helpers///
int Timer::getCurrentTime()const{
    SYSTEMTIME st;

    GetSystemTime(&st);

    return ((st.wHour + 2) * 3600) + (st.wMinute * 60) + st.wSecond;
}
int converTime(char from, char to, int time){

    if(from == 's'){
        switch(to){
        case 'h':
            return time / 3600;
        case 'm':
            return time % 3600 / 60;
        case 's':
            return time % 3600 % 60;
        default: std::cout << "Not a Valid Operator";
        }
    }
    if(from == 'h'){
        switch(to){
        case 'h':
            return time;
        case 'm':
            return time * 60;

        case 's':
            return time * 3600;
        default: std::cout << "Not a Valid Operator";
        }
    }
    return -1;
}

Timer::Timer(){
    this->time = 0;
    this->startTime = this->getCurrentTime();
    this->endTime = -1;

    this->state = tr::PAUSE;
}
void Timer::updateTime(){

    this->time++;
}

void Timer::start(){
    this->state = tr::START;
}
void Timer::stop(){
    this->state = tr::STOP;
    this->endTime = this->getCurrentTime();
}
void Timer::pause(){
    this->state = tr::PAUSE;
}

int Timer::getTime() const{
    return this->time;
}
int Timer::getStartTime() const{
    return this->startTime;
}
int Timer::getEndTime() const{
    return this->endTime;
}

std::string Timer::toString() const{
    char str[100];

    sprintf(str, "%dh %dm %ds", converTime('s', 'h', this->time), converTime('s', 'm', this->time), converTime('s', 's', this->time));

    return std::string(str);
}


