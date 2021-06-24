#include "Grid.h"
#include "myconio.h"
#include <time.h>
#include <windows.h>
#include <iostream>

Grid::Grid(Difficulty dif) : sett(dif) {

    this->board = new Cell*[this->sett.getFullSize()];
    for(int i = 0; i < this->sett.getFullSize(); i++){
        this->board[i]  = new Cell(0, false);
    }
    this->currentCell = this->board[0];
    this->currentX = 0;
    this->currentY = 0;
    this->bombCounter = 0;
    this->flagCounter = 0;
    this->setRandomMines();
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
void Grid::switchFlag(){

    if(this->board[this->getIndex(this->currentX, this->currentY)]->isVisit() || this->flagCounter > this->sett.getNumberOfMines()) return;

    if(this->board[this->getIndex(this->currentX, this->currentY)]->isFlag()){
        this->board[this->getIndex(this->currentX, this->currentY)]->setFlag(false);
        this->board[this->getIndex(this->currentX, this->currentY)]->setCurrentSign(219);
        this->board[this->getIndex(this->currentX, this->currentY)]->setColor(GREEN);
        this->flagCounter--;
    }
    else{
        this->board[this->getIndex(this->currentX, this->currentY)]->setFlag(true);
        this->board[this->getIndex(this->currentX, this->currentY)]->setCurrentSign(178);
        this->board[this->getIndex(this->currentX, this->currentY)]->setColor(BLUE);
        this->flagCounter++;
    }
}
void Grid::openField(){
    if(this->board[this->getIndex(this->currentX, this->currentY)]->isMine()){
        this->board[this->getIndex(this->currentX, this->currentY)]->setColor(RED);
        this->board[this->getIndex(this->currentX, this->currentY)]->setVisit(true);
    }else{
        this->board[this->getIndex(this->currentX, this->currentY)]->setColor(BROWN);
        this->board[this->getIndex(this->currentX, this->currentY)]->setVisit(true);
    }

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

        if(this->board[i]->isVisit()){
            if(this->board[i]->getNumber() > 0){
                this->drawBox(x + x, y, BLACK, BROWN,this->board[i]->getCurrentSign());
            }else{
                this->drawBox(x + x, y, this->board[i]->getColor(), BROWN,this->board[i]->getCurrentSign());
            }
        }else{
            this->drawBox(x + x, y, this->board[i]->getColor(), GREEN,this->board[i]->getCurrentSign());
        }
    }

    this->drawBox(this->currentX + this->currentX, this->currentY, MAGENTA, GREEN, '+');
    gotoxy(this->sett.getLength() * 2 + 5, 1);
    std::cout << this->flagCounter << " / " << this->sett.getNumberOfMines() << " Flags ( " << (char) 178 << (char) 178 <<" )";

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
void Grid::setRandomMines(){
    srand(time(NULL));

    int index;
    for(int i = 0; i < this->sett.getNumberOfMines(); i++){
        index = rand() % this->sett.getFullSize() + 0;
        if(this->board[index]->isMine()){
            i--;
        }else{
            this->board[index]->setMine(true);
        }

    }
}
