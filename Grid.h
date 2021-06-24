#pragma once
#include "myconio.h"
#include "Cell.h"
#include "Settings.h"
#include <string>
#include "Stack.h"

class Grid{
public:
    Grid(Difficulty dif = Beginner, std::string label = "M I N E S W E E P E R");
    ~Grid();

    Cell* getCell(int x, int y) const;
    void moveCursor(int pushX, int pushY);
    void switchFlag();
    bool checkField();

    void setLabel(std::string label);

    std::string getLabel() const;

    void render() const;
private:
    Cell* *board;
    Cell* currentCell;

    int currentX;
    int currentY;
    Settings sett;
    int bombCounter;
    int flagCounter;
    bool showCursor;
    std::string label;

    int getIndex(int x, int y) const;
    bool inRange(int x, int y) const;
    void drawBox(int x, int y, int color = GREEN, int bgC = GREEN, char sign = 219) const;
    void setRandomMines();
    int countBombs() const;
    void showAllBombs();
    void openFields(int x, int y);
    void setNumbers();
};
