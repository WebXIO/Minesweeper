#pragma once
#include "Cell.h"
#include "Settings.h"

class Grid{
    Grid(Difficulty dif = Beginner);

    Cell* getCell(int x, int y);
private:
    Cell* board;
    Cell* currentCell;

    Settings sett;

    int getIndex(int x, int y) const;
    bool inRange(int x, int y) const;
};
