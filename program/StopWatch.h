#ifndef SDIZO_1_STOPWATCH_H
#define SDIZO_1_STOPWATCH_H

#include <windows.h>

class StopWatch {
public:
    StopWatch();
    void start();
    void stop();
    unsigned long long getLastMeasurmentPiccosec();
private:
    LARGE_INTEGER startStamp;
    LARGE_INTEGER stopStamp;
    LARGE_INTEGER frequency;
    LARGE_INTEGER timeElapsedPiccosec;
};


#endif //SDIZO_1_STOPWATCH_H
