#ifndef SDIZO2_GRAPH_H
#define SDIZO2_GRAPH_H

#include <memory>
#include "Path.h"

class Graph;

using vertexId_t = size_t;
using GraphPointer = std::shared_ptr<Graph>;

class Graph {
public:
    virtual void addVertex() = 0;
    virtual void addEdge(vertexId_t initialVertex, vertexId_t finalVertex, int weight) = 0;
    virtual void removeVertex(vertexId_t vertexId) = 0;
    virtual void removeEdge(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual vertexId_t verticesAmount() = 0;
    virtual vertexId_t edgesAmount() = 0;

    virtual PathPointer shortestPathPrim(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual PathPointer shortestPathKruskal(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual GraphPointer MSTDijkstra() = 0;
    virtual GraphPointer MSTFB() = 0;
};

#endif //SDIZO2_GRAPH_H
