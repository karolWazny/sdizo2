#include "TimeMeasurer.h"
#include <iomanip>

std::string TimeMeasurer::representations[2] = {"list", "matrix"};
std::string TimeMeasurer::problems[2] = {"mst", "paths"};
std::string TimeMeasurer::algorithms[2][2] = {{"prim", "kruskal"}, {"dijkstra", "b-ford"}};
std::string TimeMeasurer::columnHeaders = "TIME\tDENSITY\tSIZE\tREPRES\tPROBLEM\tALGORITHM";
unsigned long long(*(TimeMeasurer::measuringMethods[2][2]))(GraphPointer) = {{prim, kruskal}, {dijkstra, bFord}};

void gotoxy(short x, short y)
{
    COORD coord;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
}

void clear() {
    system("cls");
}

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
        clear();
        gotoxy(0,0);
        std::cout << "Density: " << std::to_string(densities[dens]) << "% (option "<< dens + 1 << " out of 4)"  << "        ";

        std::string filename = std::to_string(startTime);
        filename += "meas";
        filename += std::to_string(dens);
        filename += ".txt";
        std::ofstream ofstream = std::ofstream(filename);

        ofstream << columnHeaders;
        auto iterator = measurements.iterator();
        while(iterator.hasNext()) {
            ofstream << "\n" << iterator.next();
        }

        ofstream.close();


        for(int si = 0; si < 5; si++) {
#endif
            gotoxy(0,1);
            std::cout << "Size: " << std::setw(6) << std::left << sizes[si] << " (option "<< si + 1 << " out of 5)"  << "        ";
            for(int prob = 0; prob < 2; prob++) {
                gotoxy(0,3);
                std::cout << "Problem: " << std::setw(10) << std::left << problems[prob] << " (option "<< prob + 1 << " out of 2)"  << "        ";
                auto meas = singleMeasurement(dens,
                                              si,
                                              prob);
                for(int i = 0; i < 2; i++){
                    for(int j = 0; j < 2; j++){
                        measurements.pushBack(meas[i][j]);
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
    clear();
}

Array<Array<SingleMeasurement>>
TimeMeasurer::singleMeasurement(int densityOption,
                                int sizeOption,
                                int probOption) {
    Array<FactoryPointer> factories(2);
    factories[0] = FactoryPointer(new ListGraphFactory);
    factories[1] = FactoryPointer(new MatrixGraphFactory);
    Array<GraphPointer> graphs;
    unsigned long long time[2][2]{};
    gotoxy(0, 5);
    std::cout << "Instance: " << "    " << "out of 20";
    for (int i = 0; i < 20; i++) {
        gotoxy(10, 5);
        std::cout << std::setw(3) << i + 1;
        gotoxy(20, 20);
        switch (probOption) {
            case 0:
                graphs = GraphGenerator().generateUndirectedTwin(factories,
                                                                 sizes[sizeOption],
                                                                 densities[densityOption]);
                break;
            case 1:
                graphs = GraphGenerator().generateDirectedTwin(factories,
                                                               sizes[sizeOption],
                                                               densities[densityOption]);
                break;
            default:
                break;
        }
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                unsigned long long tmp = measuringMethods[probOption][j](graphs[k]);
                if (tmp != 0) {
                    time[j][k] += tmp;
                } else {
                    i--;
                }
            }
        }
    }

    time[0][0] /= 128;
    time[1][0] /= 128;
    time[0][1] /= 128;
    time[1][1] /= 128;

    Array<Array<SingleMeasurement>> meas(2);
    for(int i = 0; i < 2; i++){
        meas[i] = Array<SingleMeasurement>(2);

    }
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            meas[j][k].size = sizes[sizeOption];
            meas[j][k].time = time[j][k];
            meas[j][k].density = densities[densityOption];
            meas[j][k].representation = representations[k];
            meas[j][k].algorithm = algorithms[probOption][j];
            meas[j][k].problem = problems[probOption];
        }
    }
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
