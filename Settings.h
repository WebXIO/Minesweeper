#pragma once

enum Difficulty {
    Beginner     = 0,
    Medium       = 1,
    Professional = 2
};

class Settings {
    public:
        Settings(Difficulty difficulty = Beginner);

    private:
        Difficulty difficulty;
        int sizeLength;
        int sizeWidth;
        int numberOfMines;
        int percentageMines;
};
