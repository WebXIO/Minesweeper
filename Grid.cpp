#include "Grid.h"

Grid::Grid(int sizeX, int sizeY) : sett(Beginner, sizeX, sizeY, 16) {

    this->board = new Cell[sizeX * sizeY];
}
