#include "StopWatch.h"

StopWatch::StopWatch() {
    QueryPerformanceFrequency(&frequency);
}

void StopWatch::start() {
    QueryPerformanceCounter(&startStamp);
}

void StopWatch::stop() {
    QueryPerformanceCounter(&stopStamp);
    timeElapsedPiccosec.QuadPart = stopStamp.QuadPart - startStamp.QuadPart;
    timeElapsedPiccosec.QuadPart *= 1000000000000;//10^6 daje czas w mikrosekundach, 10^12 to piko
    timeElapsedPiccosec.QuadPart /= frequency.QuadPart;
}

unsigned long long StopWatch::getLastMeasurmentPiccosec() {
    return timeElapsedPiccosec.QuadPart;
}
