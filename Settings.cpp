#include "Settings.h"
#include <cstdlib>
#include <time.h>

Settings::Settings(Difficulty diff) : difficulty(diff) {
    if (diff == Beginner) {
        this->sizeLength = 8;
        this->sizeWidth = 8;
        this->percentageMines = 16;
    }
    if (diff == Medium) {
        this->sizeLength = 16;
        this->sizeWidth = 16;
        this->percentageMines = 16;
    }
    if (diff == Professional) {
        this->sizeLength = 30;
        this->sizeWidth = 16;
        this->percentageMines = 21;
    }
    srand(time(NULL));
    this->numberOfMines = ((this->sizeLength * this->sizeWidth) * (rand() % this->percentageMines)) / 100;
}
