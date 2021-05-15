#ifndef SDIZO2_MATRIXGRAPH_H
#define SDIZO2_MATRIXGRAPH_H

#include "Graph.h"

struct MatrixGraphVertex;

class MatrixGraph : public Graph{
public:
    explicit MatrixGraph(size_t size);
    void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) override;
    void addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) override;
    void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) override;
    void removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) override;
    size_t verticesAmount() override;
    size_t edgesAmount() override;

    PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) override;
    PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) override;
    GraphPointer MSTPrim() override;
    GraphPointer MSTKruskal() override;

    std::string getRepresentation() override;

private:
    MatrixGraphVertex& vertexWithId(vertexId_t id);

    Array<MatrixGraphVertex> vertices;
    Array<int> weights;
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
