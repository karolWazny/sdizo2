#ifndef SDIZO2_LISTGRAPH_H
#define SDIZO2_LISTGRAPH_H

#include "Graph.h"
#include "../structure_templates_lib/structures.h"

struct ListGraphEdge;
struct ListGraphVertix;

class ListGraph : Graph {
public:
    virtual void addVertex();
    virtual void addEdge(size_t initialVertex, size_t finalVertex, int weight);
    virtual void removeVertex(size_t vertexId);
    virtual void removeEdge(size_t initialVertex, size_t finalVertex);
    virtual size_t verticesAmount();
    virtual size_t edgesAmount();

    virtual PathPointer shortestPathPrim(size_t initialVertex, size_t finalVertex);
    virtual PathPointer shortestPathKruskal(size_t initialVertex, size_t finalVertex);
    virtual GraphPointer MSTDijkstra();
    virtual GraphPointer MSTFB();
private:
    LinkedList<ListGraphVertix> vertices;
    size_t size{0};
    size_t usedVertixIds{0};
};

struct ListGraphEdge {
public:
    size_t finalVertex;
    int weight;
};

struct ListGraphVertix {
public:
    size_t id{};
    LinkedList<ListGraphEdge> edges;
};

#endif //SDIZO2_LISTGRAPH_H
