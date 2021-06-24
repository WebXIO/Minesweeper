#pragma once

enum STATES{
    START,
    PAUSE,
    OVER
};
class GameManager{

public:
    GameManager();

private:
    Grid field;
    STATES gameState;
};
