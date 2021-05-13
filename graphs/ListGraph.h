#ifndef SDIZO2_LISTGRAPH_H
#define SDIZO2_LISTGRAPH_H

#include "Graph.h"
#include "../structure_templates_lib/structures.h"

struct ListGraphEdge;
struct ListGraphVertex;

class ListGraph : Graph {
public:
    void addVertex(vertexId_t vertexId) override;
    void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) override;
    void removeVertex(vertexId_t vertexId) override;
    void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) override;
    size_t verticesAmount() override;
    size_t edgesAmountDirected() override;

    virtual PathPointer shortestPathPrim(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual PathPointer shortestPathKruskal(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual GraphPointer MSTDijkstra();
    virtual GraphPointer MSTFB();
    std::string getRepresentation() override;
private:
    LinkedList<ListGraphVertex> vertices;
    long totalWeight;
};

class ListGraphEdge {
public:
    vertexId_t finalVertex;
    int weight{};

    explicit ListGraphEdge(vertexId_t vertex) : finalVertex{vertex} {};
    ListGraphEdge() : finalVertex{0} {};
};

struct Edge {
    vertexId_t initialVertex;
    vertexId_t finalVertex;
    int weight;
};

struct ListGraphVertex {
public:
    std::string toString();

    vertexId_t id{};
    LinkedList<ListGraphEdge> edges;
    explicit ListGraphVertex(vertexId_t vertexId) : id{vertexId} {};
    ListGraphVertex() : id{0} {};
};

#endif //SDIZO2_LISTGRAPH_H
