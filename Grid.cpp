#include "Grid.h"
#include "myconio.h"
#include <time.h>
#include <windows.h>
#include <iostream>
#include <bits/stdc++.h>

Grid::Grid(Difficulty dif, std::string label) : sett(dif), label(label){

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
    this->setNumbers();

    this->showCursor = true;
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
        this->board[this->getIndex(this->currentX, this->currentY)]->setCurrentSign(this->board[this->getIndex(this->currentX, this->currentY)]->getLastSign());
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
bool Grid::checkField(){
    if(this->board[this->getIndex(this->currentX, this->currentY)]->isFlag())return false;

    if(this->board[this->getIndex(this->currentX, this->currentY)]->isMine()){
        this->showCursor = false;
        this->showAllBombs();
        return true;
    }else{
        this->openFields(this->currentX, this->currentY);
    }
    return false;

}
int Grid::countBombs() const{
    int counter = 0;

    if(this->inRange(this->currentX - 1, this->currentY - 1) && this->board[this->getIndex(this->currentX - 1, this->currentY - 1)]->isMine()) counter++; //UP Left
    if(this->inRange(this->currentX, this->currentY - 1)     && this->board[this->getIndex(this->currentX, this->currentY - 1)]->isMine()) counter++; //UP Middle
    if(this->inRange(this->currentX + 1, this->currentY - 1) && this->board[this->getIndex(this->currentX + 1, this->currentY - 1)]->isMine()) counter++; //UP Right
    if(this->inRange(this->currentX - 1, this->currentY)     && this->board[this->getIndex(this->currentX - 1, this->currentY)]->isMine() ) counter++; //Middle Left
    if(this->inRange(this->currentX, this->currentY)         && this->board[this->getIndex(this->currentX, this->currentY)]->isMine() ) counter++; //Middle
    if(this->inRange(this->currentX + 1, this->currentY)     && this->board[this->getIndex(this->currentX + 1, this->currentY)]->isMine()) counter++; //Middle Right
    if(this->inRange(this->currentX - 1, this->currentY + 1) && this->board[this->getIndex(this->currentX - 1, this->currentY + 1)]->isMine()) counter++; //Down Left
    if(this->inRange(this->currentX, this->currentY + 1)     && this->board[this->getIndex(this->currentX, this->currentY + 1)]->isMine()) counter++; //Down Middle
    if(this->inRange(this->currentX + 1, this->currentY + 1) && this->board[this->getIndex(this->currentX + 1, this->currentY + 1)]->isMine()) counter++; //Down Right

    return counter;

}
int Grid::getIndex(int x, int y) const{
    return x + (y * this->sett.getLength());
}
bool Grid::inRange(int x, int y) const{
   if(x > this->sett.getLength() - 1 || y > this->sett.getWidth() - 1 || x < 0 || y < 0) return false;
   return true;
}
void Grid::render() const{
    int y, x;
    gotoxy(this->sett.getLength() - (this->label.length() / 2), 0);
    std::cout << this->label;
    for(int i = 0; i < this->sett.getFullSize(); i++){
        y = i / this->sett.getLength() + 1;
        x = i % this->sett.getLength() + 1;

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

    if(this->showCursor) this->drawBox(this->currentX + this->currentX + 2, this->currentY + 1, MAGENTA, GREEN, '+');
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

    if(!this->inRange(newX, newY)) return;

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
void Grid::showAllBombs(){

    for(int i = 0; i < this->sett.getFullSize(); i++){

        if(this->board[i]->isMine()){
            this->board[i]->setColor(RED);
            this->board[i]->setVisit(true);
        }
    }
    this->render();
}
void Grid::setNumbers(){

    for(int i = 0; i < this->sett.getFullSize(); i++){
        this->currentY = i / this->sett.getLength();
        this->currentX = i % this->sett.getLength();

        if(!this->board[i]->isMine()){
            if(this->countBombs() > 0){
                //this->board[this->getIndex(this->currentX, this->currentY)]->setColor(BROWN);
                this->board[this->getIndex(this->currentX, this->currentY)]->setCurrentSign(this->countBombs() + 48);
                this->board[this->getIndex(this->currentX, this->currentY)]->setNumber(this->countBombs());

            }
        }
    }

    this->currentX = 0;
    this->currentY = 0;
}
void Grid::setLabel(std::string label){
    this->label = label;
}

std::string Grid::getLabel() const{

    return this->label;
}
void Grid::openFields(int x, int y){

    this->board[this->getIndex(x, y)]->setVisit(true);
    this->board[this->getIndex(x, y)]->setColor(BROWN);

    if(this->board[this->getIndex(x, y)]->getNumber() == 0){
        int bX = x + 1,
            sX = x - 1,
            bY = y + 1,
            sY = y - 1;

        if(this->inRange(bX, y) && this->board[this->getIndex(bX, y)]->canOpen()) this->openFields(bX, y);
        if(this->inRange(sX, y) && this->board[this->getIndex(sX, y)]->canOpen()) this->openFields(sX, y);
        if(this->inRange(x, bY) && this->board[this->getIndex(x, bY)]->canOpen()) this->openFields(x, bY);
        if(this->inRange(x, sY) && this->board[this->getIndex(x, sY)]->canOpen()) this->openFields(x, sY);
    }
}
