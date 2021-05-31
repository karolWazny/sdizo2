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
    virtual void addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept = 0;
    virtual void addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept = 0;
    virtual void removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept = 0;
    virtual void removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept = 0;
    virtual vertexId_t verticesAmount() = 0;
    virtual vertexId_t edgesAmount() = 0;

    virtual PathPointer shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual PathPointer shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) = 0;
    virtual GraphPointer MSTPrim() = 0;
    virtual GraphPointer MSTKruskal() = 0;

    virtual std::string getRepresentation() = 0;

    virtual long getWeight();
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


struct Edge {
    vertexId_t initialVertex;
    vertexId_t finalVertex;
    int weight;
    Edge() : initialVertex{0}, finalVertex{0}, weight{0} {};
    Edge(vertexId_t initial, vertexId_t final, int w) : initialVertex{initial},
                                                        finalVertex{final}, weight{w} {};
};

bool operator==(const Edge& e, const Edge& f);

bool operator==(VertexColor v, VertexColor f);

bool operator>=(const Edge& e, const Edge& f);

bool operator<=(const Edge& e, const Edge& f);

bool operator>(const Edge& e, const Edge& f);

bool operator<(const Edge& e, const Edge& f);

bool operator>=(const PathVertex& e, const PathVertex& f);

bool operator<=(const PathVertex& e, const PathVertex& f);

bool operator>(const PathVertex& e, const PathVertex& f);

bool operator<(const PathVertex& e, const PathVertex& f);

#endif //SDIZO2_GRAPH_H
