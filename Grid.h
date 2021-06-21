#pragma once
#include "Cell.h"

class Grid{
    Grid(int sizeX = 8, int sizeY = 8);
private:
    Cell* board;
};
