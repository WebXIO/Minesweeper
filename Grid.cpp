#include "Grid.h"

Grid::Grid(Difficulty dif) : sett(dif) {

    this->board = new Cell[this->sett.getLength() * this->sett.getWidth()];
}

Cell* Grid::getCell(int x, int y){
    if(x * y > this->sett.getLength() * this->sett.getWidth()) return NULL;

    return this->board[getIndex(x, y)];

}
int Grid::getIndex(int x, int y) const{
    return y + (x * this->sett.getLength())
}
