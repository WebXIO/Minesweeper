#pragma once
#include <string>

namespace tr{
    enum STATE{
        START,
        PAUSE,
        STOP
    };
}
class Timer{

public:
    Timer();

    void updateTime();

    void start();
    void stop();
    void pause();

    int getTime() const;
    int getStartTime() const;
    int getEndTime() const;

    std::string toString() const;

private:
    int time;
    int startTime;
    int endTime;

    tr::STATE state;
private:
    int getCurrentTime() const;
};
