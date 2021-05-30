#ifndef SDIZO2_LISTGRAPH_H
#define SDIZO2_LISTGRAPH_H

#include "Graph.h"
#include "../structure_templates_lib/structures.h"

class ListGraphEdge;
class ListGraphVertex;

class ListGraph : public Graph {
public:
    explicit ListGraph(size_t vertices);

    void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept override;
    void addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept override;
    void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept override;
    void removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept override;
    size_t verticesAmount() override;
    size_t edgesAmount() override;

    virtual PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex);
    virtual GraphPointer MSTPrim();
    virtual GraphPointer MSTKruskal();
    std::string getRepresentation() override;
private:
    ListIterator<ListGraphEdge> edgesFromVertex(vertexId_t vertexId);

    Array<ListGraphVertex> vertices;
};

class ListGraphEdge {
public:
    vertexId_t finalVertex;
    int weight{};

    explicit ListGraphEdge(vertexId_t vertex) : finalVertex{vertex} {};
    ListGraphEdge(vertexId_t vertex, int w) : finalVertex{vertex}, weight{w} {};
    ListGraphEdge() : finalVertex{0} {};
};

class ListGraphVertex {
public:
    std::string toString();

    vertexId_t id{};
    LinkedList<ListGraphEdge> edges;
    explicit ListGraphVertex(vertexId_t vertexId) : id{vertexId} {};
    ListGraphVertex() : id{0} {};
};


#endif //SDIZO2_LISTGRAPH_H
