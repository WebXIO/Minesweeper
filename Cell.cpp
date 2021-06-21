#include "Cell.h"

Cell::Cell(int number, bool mine) : number(number), mine(mine){
    this->visit = false;
    this->flag = false;
}
