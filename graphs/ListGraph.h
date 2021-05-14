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

    virtual PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual GraphPointer MSTPrim();
    virtual GraphPointer MSTKruskal();
    std::string getRepresentation() override;
private:
    ListIterator<ListGraphEdge> edgesFromVertex(vertexId_t vertexId);

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
    Edge() : initialVertex{0}, finalVertex{0}, weight{0} {};
    Edge(vertexId_t initial, vertexId_t final, int w) : initialVertex{initial},
                finalVertex{final}, weight{w} {};
};

struct ListGraphVertex {
public:
    std::string toString();

    vertexId_t id{};
    LinkedList<ListGraphEdge> edges;
    explicit ListGraphVertex(vertexId_t vertexId) : id{vertexId} {};
    ListGraphVertex() : id{0} {};
};

struct VertexColor {
public:
    vertexId_t id{};
    vertexId_t color{};
    VertexColor(vertexId_t vertexId, vertexId_t vertexColor) : id{vertexId}, color{vertexColor} {};
    VertexColor() : id{0}, color{0} {};
};

struct PathVertex {
public:
    vertexId_t id{};
    vertexId_t parent{INT32_MAX};
    long long pathLength{INT64_MAX};
    PathVertex() : id{0} {};
    PathVertex(vertexId_t vertexId) : id{vertexId} {};
};

#endif //SDIZO2_LISTGRAPH_H
