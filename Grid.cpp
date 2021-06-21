#include "Grid.h"
#include "myconio.h"
#include <iostream>

Grid::Grid(Difficulty dif) : sett(dif) {

    this->board = new Cell*[this->sett.getFullSize()];
    for(int i = 0; i < this->sett.getFullSize(); i++){
        this->board[i]  = new Cell(0, false);
    }
    this->currentCell = this->board[0];
    this->currentX = 0;
    this->currentY = 0;
}
Grid::~Grid(){
    for(int i = 0; i < this->sett.getFullSize(); i++){
        delete this->board[i];
    }
    delete[] board;
    delete currentCell;
}
Cell* Grid::getCell(int x, int y) const{

    if(!this->inRange(x, y)) return NULL;

    return this->board[this->getIndex(x, y)];

}
int Grid::getIndex(int x, int y) const{
    return x + (y * this->sett.getLength());
}
bool Grid::inRange(int x, int y) const{
   if(x > this->sett.getLength() || y > this->sett.getWidth() ||x < 0 || y < 0) return false;
   return true;
}
void Grid::render() const{
    int y, x;
    for(int i = 0; i < this->sett.getFullSize(); i++){
        y = i / this->sett.getLength();
        x = i % this->sett.getLength();
        this->drawBox(x + x, y, GREEN, this->board[i]->getCurrentSign());
    }

    this->drawBox(this->currentX + this->currentX, this->currentY, MAGENTA, GREEN, '+');
}
void Grid::drawBox(int x, int y, int color, int bgC,char sign) const{
    setColorAndBackground(color, bgC);
    gotoxy(x, y);
    std::cout << sign << sign;
    setColorAndBackground(WHITE, BLACK);
}
void Grid::moveCursor(int pushX, int pushY){
    int newX = this->currentX + pushX;
    int newY = this->currentY + pushY;

    if(   newX < 0
       || newX > this->sett.getLength() - 1
       || newY < 0
       || newY > this->sett.getWidth() - 1) return;

    this->currentCell = this->board[this->getIndex(newX, newY)];
    this->currentX += pushX;
    this->currentY += pushY;

}
