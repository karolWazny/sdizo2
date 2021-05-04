#ifndef SDIZO2_GRAPH_H
#define SDIZO2_GRAPH_H

#include <memory>
#include "Path.h"

class Graph;

using GraphPointer = std::shared_ptr<Graph>;

class Graph {
public:
    virtual void addVertex() = 0;
    virtual void addEdge(size_t initialVertex, size_t finalVertex, int weight) = 0;
    virtual void removeVertex(size_t vertexId) = 0;
    virtual void removeEdge(size_t initialVertex, size_t finalVertex) = 0;
    virtual size_t verticesAmount() = 0;
    virtual size_t edgesAmount() = 0;

    virtual PathPointer shortestPathPrim(size_t initialVertex, size_t finalVertex) = 0;
    virtual PathPointer shortestPathKruskal(size_t initialVertex, size_t finalVertex) = 0;
    virtual GraphPointer MSTDijkstra() = 0;
    virtual GraphPointer MSTFB() = 0;
};

#endif //SDIZO2_GRAPH_H
