#include "ListGraph.h"

bool operator==(const ListGraphVertix& v, const ListGraphVertix& w) {
    return v.id == w.id;
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
