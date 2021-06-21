#pragma once
#include <string>
class Cell{

public:
    Cell(int number = 0, bool mine = false);

    void setNumber(int number);
    void setMine(bool mine);
    void setVisit(bool visit);
    void setFlag(bool flag);

    int getNumber() const;
    bool isMine() const;
    bool isVisit() const;
    bool isFlag() const;

    std::string toString() const;
private:
    int number;
    bool mine;
    bool visit;
    bool flag;
};
