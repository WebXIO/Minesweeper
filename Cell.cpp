#include "Cell.h"
#include "myconio.h"
#include <cstring>
#include <cstdio>

Cell::Cell(int number, bool mine) : number(number), mine(mine){
    this->visit = false;
    this->flag = false;
    this->currentSign = 219;
    this->color = GREEN;
}
void Cell::setNumber(int number){
    this->number = number;
}
void Cell::setCurrentSign(char currentSign){
    this->currentSign = currentSign;
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
void Cell::setColor(int color){
    this->color = color;
}

int Cell::getNumber() const{
    return this->number;
}
char Cell::getCurrentSign() const{
    return this->currentSign;
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
int Cell::getColor() const{
    return this->color;
}
