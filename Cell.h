#pragma once
#include <string>
class Cell{

public:
    Cell(int number = 0, bool mine = false);

    void setNumber(int number);
    void setCurrentSign(char currentSign);
    void setMine(bool mine);
    void setVisit(bool visit);
    void setFlag(bool flag);

    int getNumber() const;
    char getCurrentSign() const;
    bool isMine() const;
    bool isVisit() const;
    bool isFlag() const;

private:
    int number;
    char currentSign;
    bool mine;
    bool visit;
    bool flag;
};
