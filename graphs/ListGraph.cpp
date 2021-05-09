#include "ListGraph.h"

bool operator==(const ListGraphVertix& v, const ListGraphVertix& w) {
    return v.id == w.id;
}

bool operator==(const ListGraphEdge& e, const ListGraphEdge& f) {
    return e.finalVertex == f.finalVertex;
}

void ListGraph::addVertex() {
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
        auto &initVer = vertices.get(index);
        index = initVer.edges.firstIndexOf((ListGraphEdge)finalVertex);
        if(index > -1)
        {
            //jeżeli taka krawędź już istnieje, aktualizujemy jej wagę
            initVer.edges.get(index).weight = weight;
        } else {
            //jeżeli nie istnieje, po prostu ją tworzymy
            auto edge = ListGraphEdge(finalVertex);
            edge.weight = weight;
            initVer.edges.pushBack(edge);
        }
    } else {
        //nie wiem... rzucić wyjątek? na razie będzie ciche niepowodzenie
    }
}

void ListGraph::removeVertex(vertexId_t vertexId) {
    auto iterator = this->vertices.iterator();
    while(iterator.hasNext())
    {
        auto &currentVertex = iterator.next();
        currentVertex.edges.remove((ListGraphEdge)vertexId);
    }
    this->vertices.remove((ListGraphVertix) vertexId);
}

void ListGraph::removeEdge(vertexId_t initialVertex, vertexId_t finalVertex) {
    auto index = vertices.firstIndexOf(ListGraphVertix(initialVertex));
    if(index > -1)
    {
        auto& initVer = vertices.get(index);
        initVer.edges.remove(ListGraphEdge(finalVertex));
    }
    //jeżeli próbujemy usunąć coś czego nie ma, robimy ciche niepowodzenie
}

size_t ListGraph::verticesAmount() {
    return vertices.getLength();
}

size_t ListGraph::edgesAmount() {
    size_t sum = 0;
    auto iterator = this->vertices.iterator();
    while(iterator.hasNext())
    {
        sum += iterator.next().edges.getLength();
    }
    return sum;
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
