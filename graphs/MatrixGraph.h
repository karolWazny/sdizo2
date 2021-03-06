#ifndef SDIZO2_MATRIXGRAPH_H
#define SDIZO2_MATRIXGRAPH_H

#include <sstream>
#include "Graph.h"
#include "GraphGenerator.h"

struct MatrixGraphVertex;

class MatrixGraph : public Graph{
public:
    explicit MatrixGraph(size_t size);
    explicit MatrixGraph(size_t size, size_t edges);
    void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept override;
    void addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept override;
    void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept override;
    void removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept override;
    size_t verticesAmount() override;
    size_t edgesAmount() override;

    PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) override;
    PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) override;
    GraphPointer MSTPrim() override;
    GraphPointer MSTKruskal() override;

    std::string getRepresentation() override;

    long getWeight() override;

private:
    MatrixGraphVertex& vertexWithId(vertexId_t id);

    Array<MatrixGraphVertex> vertices;
    Array<int> weights;
    size_t edgesNumber;
};

enum Incidence : char {
    NONE = 0,
    IN = 1,
    OUT = 2,
};

struct MatrixGraphVertex {
    vertexId_t id;
    Array<Incidence> incidences;
};

#endif //SDIZO2_MATRIXGRAPH_H
