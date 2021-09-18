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
    this->currentX = 0;
    this->currentY = 0;
    this->rightBombCounter = 0;
    this->flagCounter = 0;
    this->openFieldCounter = 0;

    this->showCursor = true;
    this->showDevTools = false;
    this->showAllBombs = false;
    this->firstBomb = true;
}
Grid::~Grid(){
    for(int i = 0; i < this->sett.getFullSize(); i++){
        delete this->board[i];
    }
    delete[] board;
}
Cell* Grid::getCell(int x, int y) const{

    if(!this->inRange(x, y)) return NULL;

    return this->board[this->getIndex(x, y)];

}
void Grid::switchFlag(){



    if(this->board[this->getIndex(this->currentX, this->currentY)]->isFlag()){
        if(this->board[this->getIndex(this->currentX, this->currentY)]->isMine()) this->rightBombCounter--;
        this->board[this->getIndex(this->currentX, this->currentY)]->setFlag(false);
        this->board[this->getIndex(this->currentX, this->currentY)]->setCurrentSign(this->board[this->getIndex(this->currentX, this->currentY)]->getLastSign());
        this->board[this->getIndex(this->currentX, this->currentY)]->setColor(GREEN);
        this->flagCounter--;
    }
    else{
        if(this->board[this->getIndex(this->currentX, this->currentY)]->isVisit() || this->flagCounter > this->sett.getNumberOfMines() - 1) return;
        if(this->board[this->getIndex(this->currentX, this->currentY)]->isMine()) this->rightBombCounter++;
        this->board[this->getIndex(this->currentX, this->currentY)]->setFlag(true);
        this->board[this->getIndex(this->currentX, this->currentY)]->setCurrentSign(178);
        this->board[this->getIndex(this->currentX, this->currentY)]->setColor(BLUE);
        this->flagCounter++;
    }
}
bool Grid::checkField(){
    if(this->firstBomb){
        this->firstBomb = false;
        this->setRandomMines();
        this->setNumbers();
    }
    if(this->board[this->getIndex(this->currentX, this->currentY)]->isFlag())return false;

    if(this->board[this->getIndex(this->currentX, this->currentY)]->isMine()){
        this->showCursor = false;
        this->showBombs(true);
        return true;
    }else if(!this->board[this->getIndex(this->currentX, this->currentY)]->isVisit()){
        this->openFields(this->currentX, this->currentY);
    }
    return false;

}
int Grid::countBombs(int x, int y) const{
    int counter = 0;
    if(this->board[this->getIndex(this->currentX, this->currentY)]->isMine()){
        return -1;
    }
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
          if(this->inRange(i + x, j + y) && this->board[this->getIndex(i + x, j + y)]->isMine()) counter++;
        }
    }
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

    this->displayLabel();

    for(int i = 0; i < this->sett.getFullSize(); i++){
        y = i / this->sett.getLength() + 1;
        x = i % this->sett.getLength() + 1;

        if(this->board[i]->isVisit()){
            if(this->board[i]->getNumber() > 0){
                //this->drawBox(x + x, y, BLACK, BROWN,this->board[i]->getCurrentSign());
                this->drawNumber(x + x, y, this->board[i]->getNumber());
            }else{
                this->drawBox(x + x, y, this->board[i]->getColor(), this->board[i]->getBgC(),this->board[i]->getCurrentSign());
            }
        }else{
            this->drawBox(x + x, y, this->board[i]->getColor(), this->board[i]->getBgC(),this->board[i]->getCurrentSign());
        }
    }

    if(this->showCursor) this->drawBox(this->currentX + this->currentX + 2, this->currentY + 1, MAGENTA, this->board[this->getIndex(this->currentX, this->currentY)]->getBgC(), '+');

    gotoxy(this->sett.getLength() * 2 + 5, 1);
    std::cout << this->sett.getNumberOfMines() - this->flagCounter << " Flags ( " << (char) 178 << (char) 178 <<" )";

    if(this->showDevTools) this->displayDevTools();
}
void Grid::displayLabel() const{
    for(int i = 0; i < (int)(this->label.length()); i++){
        gotoxy(this->sett.getLength() - (this->label.length() / 2) + i + 2, 0);
        std::cout << this->label[i];
    }
}
void Grid::update(){
    this->timer.updateTime();
    gotoxy(this->sett.getLength() * 2 + 5, 2);
    std::cout << this->timer.toString();
}
void Grid::switchDevTools(){

    if(this->showDevTools){
        system("cls");
        this->showDevTools = false;
    }else{
        this->showDevTools = true;
    }
}
void Grid::switchShowBomb(){
    if(this->showAllBombs){
        this->showAllBombs = false;
    }else{
        this->showAllBombs = true;
    }

    this->showBombs(this->showAllBombs);
}
void Grid::displayDevTools() const{

    gotoxy(this->sett.getLength() * 2 + 5, 4);
    std::cout << "Dev Tools {";
    gotoxy(this->sett.getLength() * 2 + 5, 5);
    std::cout << "   RightBombsCounter: " << this->rightBombCounter;
    gotoxy(this->sett.getLength() * 2 + 5, 6);
    std::cout << "   openFieldCounter: " << this->openFieldCounter;
    gotoxy(this->sett.getLength() * 2 + 5, 7);
    std::cout << "   MaxopenFields: " << this->sett.getFullSize() - this->sett.getNumberOfMines();
    gotoxy(this->sett.getLength() * 2 + 5, 8);
    std::cout << "   CurrentCell: [ isMine: " << this->board[this->getIndex(this->currentX, this->currentY)]->isMine()
                              <<" | isFlag: " << this->board[this->getIndex(this->currentX, this->currentY)]->isFlag()
                              <<" | isVisit: "<< this->board[this->getIndex(this->currentX, this->currentY)]->isVisit()
                              <<" | Number: " << this->board[this->getIndex(this->currentX, this->currentY)]->getNumber() << " ]";
    gotoxy(this->sett.getLength() * 2 + 5, 9);
    std::cout << "}";
}

void Grid::drawBox(int x, int y, int color, int bgC,char sign) const{
    setColorAndBackground(color, bgC);
    gotoxy(x, y);
    std::cout << sign << sign;
    setColorAndBackground(WHITE, BLACK);
}
void Grid::drawNumber(int x, int y, int number) const{
    setColorAndBackground(BLACK, BROWN);
    gotoxy(x, y);
    std::cout << number;
    setColor(BROWN);
    std::cout << (char) 219;
    setColorAndBackground(WHITE, BLACK);
}
void Grid::moveCursor(int pushX, int pushY){
    int newX = this->currentX + pushX;
    int newY = this->currentY + pushY;

    if(!this->inRange(newX, newY)) return;

    this->currentX += pushX;
    this->currentY += pushY;

}
void Grid::setRandomMines(){
    srand(time(NULL));

    int index;
    int y, x;
    for(int i = 0; i < this->sett.getNumberOfMines(); i++){
        index = rand() % this->sett.getFullSize() + 0;
        y = index / this->sett.getLength();
        x = index % this->sett.getLength();
        if(this->board[index]->isMine() || (this->currentX -1 == x && this->currentY - 1 == y)
                                        || (this->currentX == x && this->currentY - 1 == y)
                                        || (this->currentX + 1 == x && this->currentY - 1 == y)
                                        || (this->currentX - 1 == x && this->currentY == y)
                                        || (this->currentX == x && this->currentY == y)
                                        || (this->currentX + 1 == x && this->currentY == y)
                                        || (this->currentX -1 == x && this->currentY + 1 == y)
                                        || (this->currentX == x && this->currentY + 1 == y)
                                        || (this->currentX + 1 == x && this->currentY + 1 == y)){
            i--;

        }else{
            this->board[index]->setMine(true);
        }

    }
}
void Grid::showBombs(bool state){

    for(int i = 0; i < this->sett.getFullSize(); i++){

        if(this->board[i]->isMine()){
            if(state){
                this->board[i]->setColor(RED);
            }else{
                this->board[i]->setColor(GREEN);
            }
            this->board[i]->setVisit(state);
        }
    }
    this->render();
}
void Grid::setNumbers(){

    for(int i = 0; i < this->sett.getFullSize(); i++){
        int y = i / this->sett.getLength();
        int x = i % this->sett.getLength();

        if(!this->board[i]->isMine()){
            int bombs = this->countBombs(x, y);
            if(bombs > 0){
                this->board[this->getIndex(x, y)]->setCurrentSign(bombs + 48);
                this->board[this->getIndex(x, y)]->setNumber(bombs);
            }
        }
    }
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
    this->board[this->getIndex(x, y)]->setBgC(BROWN);
    this->openFieldCounter++;

    if(this->board[this->getIndex(x, y)]->getNumber() == 0){

        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
              if(this->inRange(i + x, j + y) && this->board[this->getIndex(i + x, j + y)]->canOpen()) this->openFields(i + x, j + y);
            }
        }
    }
}
void Grid::restart() {
    for(int i = 0; i < this->sett.getFullSize(); i++){
        delete this->board[i];
    }
    delete[] board;

    this->board = new Cell*[this->sett.getFullSize()];
    for(int i = 0; i < this->sett.getFullSize(); i++){
        this->board[i]  = new Cell(0, false);
    }
    this->currentX = 0;
    this->currentY = 0;
    this->rightBombCounter = 0;
    this->flagCounter = 0;
    this->openFieldCounter = 0;

    this->showCursor = true;
    this->showDevTools = false;
    this->showAllBombs = false;
    this->firstBomb = true;
}
bool Grid::checkWon() const{

    return (this->openFieldCounter >= this->sett.getFullSize() - this->sett.getNumberOfMines());
}
