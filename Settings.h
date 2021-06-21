#pragma once

enum Difficulty {
    Beginner     = 0,
    Medium       = 1,
    Professional = 2
};

class Settings {
    public:
        Settings(Difficulty difficulty = Beginner);

        int getNumberOfMines() const;
        int getLength() const;
        int getWidth() const;
        int getPercentageMines() const;
        Difficulty getDifficulty() const;
        int getFullSize() const;

    private:
        Difficulty difficulty;
        int sizeLength;
        int sizeWidth;
        int fullGridSize;
        int numberOfMines;
        int percentageMines;
};
