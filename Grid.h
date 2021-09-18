#pragma once
#include "myconio.h"
#include "Cell.h"
#include "Settings.h"
#include <string>
#include "Timer.h"

class Grid{
public:
    Grid(Difficulty dif = Beginner, std::string label = "M I N E S W E E P E R");
    ~Grid();

    Cell* getCell(int x, int y) const;
    void moveCursor(int pushX, int pushY);
    void switchFlag();
    bool checkField();
    bool checkWon() const;
    void update();

    void switchDevTools();
    void switchShowBomb();

    void restart();

    void setLabel(std::string label);

    std::string getLabel() const;

    void render() const;
private:
    Cell* *board;
    Timer timer;

    int currentX;
    int currentY;
    Settings sett;
    int rightBombCounter;
    int flagCounter;
    int openFieldCounter;
    bool showCursor;
    bool showDevTools;
    bool showAllBombs;
    bool firstBomb;
    std::string label;

    int getIndex(int x, int y) const;
    bool inRange(int x, int y) const;
    void drawBox(int x, int y, int color = GREEN, int bgC = GREEN, char sign = 219) const;
    void drawNumber(int x, int y, int number) const;
    void setRandomMines();
    int countBombs(int x, int y) const;
    void showBombs(bool state);
    void openFields(int x, int y);
    void setNumbers();
    void displayLabel() const;
    void displayDevTools() const;
};
