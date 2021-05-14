#ifndef SDIZO2_GRAPH_H
#define SDIZO2_GRAPH_H

#include <memory>
#include <string>
#include "Path.h"

class Graph;

using vertexId_t = size_t;
using GraphPointer = std::shared_ptr<Graph>;

class Graph {
public:
    virtual void addVertex(vertexId_t vertexId) = 0;
    virtual void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) = 0;
    virtual void addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) = 0;
    virtual void removeVertex(vertexId_t vertexId) = 0;
    virtual void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual void removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual vertexId_t verticesAmount() = 0;
    virtual vertexId_t edgesAmount() = 0;

    virtual PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual GraphPointer MSTPrim() = 0;
    virtual GraphPointer MSTKruskal() = 0;

    virtual std::string getRepresentation() = 0;
};

#endif //SDIZO2_GRAPH_H
