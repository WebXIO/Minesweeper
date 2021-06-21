#include "Grid.h"

Grid::Grid(Difficulty dif) : sett(dif) {

    this->board = new Cell[8 * 8];
}
