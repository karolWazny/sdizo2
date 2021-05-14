#ifndef SDIZO2_MATRIXGRAPH_H
#define SDIZO2_MATRIXGRAPH_H

#include "Graph.h"

class MatrixGraph : public Graph{
public:
    void addVertex(vertexId_t vertexId) override;
    void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) override;
    void removeVertex(vertexId_t vertexId) override;
    void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) override;
    vertexId_t verticesAmount() override;
    vertexId_t edgesAmountDirected() override;

    PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) override;
    PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) override;
    GraphPointer MSTPrim() override;
    GraphPointer MSTKruskal() override;

    std::string getRepresentation() override;
};


#endif //SDIZO2_MATRIXGRAPH_H
