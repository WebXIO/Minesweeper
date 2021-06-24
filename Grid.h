#pragma once
#include "myconio.h"
#include "Cell.h"
#include "Settings.h"

class Grid{
public:
    Grid(Difficulty dif = Beginner);
    ~Grid();

    Cell* getCell(int x, int y) const;
    void moveCursor(int pushX, int pushY);
    void switchFlag();
    void openField();

    void render() const;
private:
    Cell* *board;
    Cell* currentCell;

    int currentX;
    int currentY;
    Settings sett;
    int bombCounter;
    int flagCounter;

    int getIndex(int x, int y) const;
    bool inRange(int x, int y) const;
    void drawBox(int x, int y, int color = GREEN, int bgC = GREEN, char sign = 219) const;
    void setRandomMines();
};
