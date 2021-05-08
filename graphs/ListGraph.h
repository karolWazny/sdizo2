#ifndef SDIZO2_LISTGRAPH_H
#define SDIZO2_LISTGRAPH_H

#include "Graph.h"
#include "../structure_templates_lib/structures.h"

struct ListGraphEdge;
struct ListGraphVertix;

class ListGraph : Graph {
public:
    void addVertex() override;
    void addEdge(vertexId_t initialVertex, vertexId_t finalVertex, int weight) override;
    virtual void removeVertex(vertexId_t vertexId);
    virtual void removeEdge(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual vertexId_t verticesAmount();
    virtual vertexId_t edgesAmount();

    virtual PathPointer shortestPathPrim(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual PathPointer shortestPathKruskal(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual GraphPointer MSTDijkstra();
    virtual GraphPointer MSTFB();
private:
    LinkedList<ListGraphVertix> vertices;
    vertexId_t size{0};
    vertexId_t usedVertixIds{0};
};

class ListGraphEdge {
public:
    vertexId_t finalVertex;
    int weight{};

    explicit ListGraphEdge(vertexId_t vertex) : finalVertex{vertex} {};
    ListGraphEdge() : finalVertex{0} {};
};

struct ListGraphVertix {
public:
    vertexId_t id{};
    LinkedList<ListGraphEdge> edges;
    explicit ListGraphVertix(vertexId_t vertexId) : id{vertexId} {};
    ListGraphVertix() : id{0} {};
};

#endif //SDIZO2_LISTGRAPH_H
