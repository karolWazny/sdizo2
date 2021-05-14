#ifndef SDIZO2_MATRIXGRAPH_H
#define SDIZO2_MATRIXGRAPH_H

#include "Graph.h"

struct MatrixGraphVertex;

class MatrixGraph : public Graph{
public:
    void addVertex(vertexId_t vertexId) override;
    void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) override;
    void addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) override;
    void removeVertex(vertexId_t vertexId) override;
    void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) override;
    void removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) override;
    size_t verticesAmount() override;
    size_t edgesAmountDirected() override;

    PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) override;
    PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) override;
    GraphPointer MSTPrim() override;
    GraphPointer MSTKruskal() override;

    std::string getRepresentation() override;

private:
    LinkedList<MatrixGraphVertex> vertices;
    Array<int> weights;
};

enum Incidence : char {
    NONE,
    IN,
    OUT,
    BOTH
};

struct MatrixGraphVertex {
    vertexId_t id;
    Array<Incidence> incidences;
};

#endif //SDIZO2_MATRIXGRAPH_H
