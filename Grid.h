#pragma once
#include "Cell.h"
#include "Settings.h"

class Grid{
    Grid(Difficulty dif = Beginner);
private:
    Cell* board;
    Cell* currentCell;

    Settings sett;
};
