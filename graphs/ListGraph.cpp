#include "ListGraph.h"

bool operator==(const ListGraphVertix& v, const ListGraphVertix& w) {
    return v.id == w.id;
}

bool operator==(const ListGraphEdge& e, const ListGraphEdge& f) {
    return e.finalVertex == f.finalVertex;
}

void ListGraph::addVertex() {
    size++;
    auto vertix = ListGraphVertix();
    vertix.id = usedVertixIds;
    usedVertixIds++;
    vertices.pushBack(vertix);
}

void ListGraph::addEdge(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {
    ListGraphVertix v;
    v.id = finalVertex;
    bool containsFinalVertex = this->vertices.contains(v);
    v.id = initialVertex;
    bool containsInitialVertex = this->vertices.contains(v);
    if(containsInitialVertex && containsFinalVertex) {
        auto index = vertices.firstIndexOf(v);
        auto initVer = vertices.get(index);
        if(initVer.edges.contains((ListGraphEdge)finalVertex))
        {
            //do nothing
        } else {
            auto edge = ListGraphEdge(finalVertex);
            edge.weight = weight;
            initVer.edges.pushBack(edge);
        }
    } else {
        //nie wiem... rzucić wyjątek? na razie będzie ciche niepowodzenie
    }
}

void ListGraph::removeVertex(vertexId_t vertexId) {

}

void ListGraph::removeEdge(vertexId_t initialVertex, vertexId_t finalVertex) {
    auto index = vertices.firstIndexOf(ListGraphVertix(initialVertex));
    if(index > -1)
    {
        auto initVer = vertices.get(index);
        initVer.edges.remove(ListGraphEdge(finalVertex));
    }
    //jeżeli próbujemy usunąć coś czego nie ma, robimy ciche niepowodzenie
}

vertexId_t ListGraph::verticesAmount() {
    return vertices.getLength();
}

vertexId_t ListGraph::edgesAmount() {
    return 0;
}

PathPointer ListGraph::shortestPathPrim(vertexId_t initialVertex, vertexId_t finalVertex) {
    return PathPointer();
}

PathPointer ListGraph::shortestPathKruskal(vertexId_t initialVertex, vertexId_t finalVertex) {
    return PathPointer();
}

GraphPointer ListGraph::MSTDijkstra() {
    return GraphPointer();
}

GraphPointer ListGraph::MSTFB() {
    return GraphPointer();
}
