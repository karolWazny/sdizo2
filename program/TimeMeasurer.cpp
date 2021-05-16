#include "TimeMeasurer.h"

std::string TimeMeasurer::representations[2] = {"list", "matrix"};
std::string TimeMeasurer::problems[2] = {"mst", "paths"};
std::string TimeMeasurer::algorithms[2][2] = {{"prim", "kruskal"}, {"dijkstra", "b-ford"}};
std::string TimeMeasurer::columnHeaders = "TIME\tDENSITY\tSIZE\tREPRES\tPROBLEM\tALGORITHM";
unsigned long long(*(TimeMeasurer::measuringMethods[2][2]))(GraphPointer) = {{prim, kruskal}, {dijkstra, bFord}};

std::ostream& operator<<(std::ostream& ostream, const SingleMeasurement meas) {
    ostream << std::to_string(meas.time) << "\t"
            << std::to_string(meas.density) << "\t"
            << std::to_string(meas.size) << "\t"
            << meas.representation << "\t"
            << meas.problem << "\t"
            << meas.algorithm;
    return ostream;
}

void TimeMeasurer::runMeasurement() {
    auto startTime = std::time(0);
    LinkedList<SingleMeasurement> measurements;
#if DEBUG
    for(int dens = 0; dens < 2; dens++) {
        std::cout << "@";
        for(int si = 0; si < 2; si++) {
#else
    for(int dens = 0; dens < 4; dens++) {
        std::cout << "@";
        for(int si = 0; si < 5; si++) {
#endif
            std::cout << "|";
            for(int repr = 0; repr < 2; repr++) {
                std::cout << "*";
                for(int prob = 0; prob < 2; prob++) {
                    std::cout << ";";
                    for(int algo = 0; algo < 2; algo++) {
                        std::cout << ".";
                        measurements.pushBack(singleMeasurement(dens,
                                                                si,
                                                                repr,
                                                                prob,
                                                                algo));
                    }
                }
            }
        }
    }

    std::cout << "\n";
    std::string filename = std::to_string(startTime);
    filename += "meas.txt";
    std::ofstream ofstream = std::ofstream(filename);

    ofstream << columnHeaders;
    auto iterator = measurements.iterator();
    while(iterator.hasNext()) {
        ofstream << "\n" << iterator.next();
    }
}

SingleMeasurement
TimeMeasurer::singleMeasurement(int densityOption,
                                int sizeOption,
                                int reprOption,
                                int probOption,
                                int algOption) {
    FactoryPointer factory;
    switch(reprOption) {
        case 0:
            factory = FactoryPointer(new ListGraphFactory());
            break;
        case 1:
            factory = FactoryPointer(new MatrixGraphFactory());
            break;
        default:
            break;
    }
    GraphPointer graph;
    unsigned long long time{};
    for(int i = 0; i < 128; i++) {
        std::cout << "^";
        switch(probOption) {
            case 0:
                graph = GraphGenerator().generateGraphUndirected(factory,
                                                                 sizes[sizeOption],
                                                                 densities[densityOption]);
                break;
            case 1:
                graph = GraphGenerator().generateGraphDirected(factory,
                                                                 sizes[sizeOption],
                                                                 densities[densityOption]);
                break;
            default:
                break;
        }

        unsigned long long tmp = measuringMethods[probOption][algOption](graph);
        if(tmp != 0) {
            time += tmp;
        } else {
            i--;
        }
    }
    time /= 128;

    SingleMeasurement meas{};
    meas.size = sizes[sizeOption];
    meas.time = time;
    meas.density = densities[densityOption];
    meas.representation = representations[reprOption];
    meas.algorithm = algorithms[probOption][algOption];
    meas.problem = problems[probOption];
    return meas;
}

unsigned long long TimeMeasurer::prim(GraphPointer graph) {
    StopWatch stopWatch;
    stopWatch.start();
    auto mst = graph->MSTPrim();
    stopWatch.stop();
    return stopWatch.getLastMeasurmentPiccosec();
}

unsigned long long TimeMeasurer::kruskal(GraphPointer graph) {
    StopWatch stopWatch;
    stopWatch.start();
    auto mst = graph->MSTKruskal();
    stopWatch.stop();
    return stopWatch.getLastMeasurmentPiccosec();
}

unsigned long long TimeMeasurer::dijkstra(GraphPointer graph) {
    StopWatch stopWatch;
    Randomizer randomizer;
    vertexId_t initial = randomizer.getInt(graph->verticesAmount() - 1);
    vertexId_t final = randomizer.getInt(graph->verticesAmount() - 1);
    stopWatch.start();
    auto path = graph->shortestPathDijkstra(initial, final);
    stopWatch.stop();
    return stopWatch.getLastMeasurmentPiccosec();
}

unsigned long long TimeMeasurer::bFord(GraphPointer graph) {
    StopWatch stopWatch;
    Randomizer randomizer;
    vertexId_t initial = randomizer.getInt(graph->verticesAmount() - 1);
    vertexId_t final = randomizer.getInt(graph->verticesAmount() - 1);
    stopWatch.start();
    auto path = graph->shortestPathBF(initial, final);
    stopWatch.stop();
    return stopWatch.getLastMeasurmentPiccosec();
}
