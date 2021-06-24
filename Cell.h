#pragma once
#include <string>
class Cell{

public:
    Cell(int number = 0, bool mine = false);

    void setNumber(int number);
    void setCurrentSign(char currentSign);
    void setLastSign(char lastSign);
    void setMine(bool mine);
    void setVisit(bool visit);
    void setFlag(bool flag);
    void setColor(int color);
    void setBgC(int bgC);

    int getNumber() const;
    char getCurrentSign() const;
    char getLastSign() const;
    bool isMine() const;
    bool isVisit() const;
    bool isFlag() const;
    int getColor() const;
    int getBgC() const;
    bool canOpen() const;

private:
    int number;
    char currentSign;
    char lastSign;
    bool mine;
    bool visit;
    bool flag;

    int color;
    int bgC;
};
