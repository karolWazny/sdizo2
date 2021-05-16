#ifndef SDIZO2_TIMEMEASURER_H
#define SDIZO2_TIMEMEASURER_H

#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include "../structure_templates_lib/structures.h"
#include "../graphs/MatrixGraphFactory.h"
#include "../graphs/ListGraphFactory.h"
#include "../graphs/GraphGenerator.h"
#include "StopWatch.h"
#include "Randomizer.h"

struct SingleMeasurement;

class TimeMeasurer {
public:
    void runMeasurement();
private:
    SingleMeasurement singleMeasurement(int densityOption,
                                        int sizeOption,
                                        int reprOption,
                                        int probOption,
                                        int algOption);

    static unsigned long long prim(GraphPointer);
    static unsigned long long kruskal(GraphPointer);
    static unsigned long long dijkstra(GraphPointer);
    static unsigned long long bFord(GraphPointer);

    static unsigned long long (*(measuringMethods[2][2]))(GraphPointer);

    static constexpr unsigned char densities[4] = {25, 50, 75, 99};
    static constexpr size_t sizes[5] = {10, 20, 50, 100, 200};
    static std::string representations[2];
    static std::string problems[2];
    static std::string algorithms[2][2];
    static std::string columnHeaders;
};

struct SingleMeasurement {
public:
    unsigned long time;
    unsigned char density;
    size_t size;
    std::string representation;
    std::string problem;
    std::string algorithm;
};


#endif //SDIZO2_TIMEMEASURER_H
