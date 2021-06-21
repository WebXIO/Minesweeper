#pragma once

class Cell{

public:
    Cell(int number = 0, bool mine = false);

private:
    int number;
    bool mine;
    bool visit;
    bool flag;
};
