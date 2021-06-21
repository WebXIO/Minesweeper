#include "Cell.h"
#include <cstring>
#include <cstdio>

Cell::Cell(int number, bool mine) : number(number), mine(mine){
    this->visit = false;
    this->flag = false;
}
void Cell::setNumber(int number){
    this->number = number;
}
void Cell::setMine(bool mine){
    this->mine = mine;
}
void Cell::setVisit(bool visit){
    this->visit = visit;
}
void Cell::setFlag(bool flag){
    this->flag = flag;
}

int Cell::getNumber() const{
    return this->number;
}
bool Cell::isMine() const{
    return this->mine;
}
bool Cell::isVisit() const{
    return this->visit;
}
bool Cell::isFlag() const{
    return this->flag;
}
std::string Cell::toString() const{

    char str[100];


    if(this->visit){
        sprintf(str, "-----\n| %d | \n-----", this->number);
    }else{
        sprintf(str, "-----\n|   | \n-----");
    }
    if(this->flag){
        sprintf(str, "-----\n| %c | \n-----", 187);
    }

    return std::string(str);

}
