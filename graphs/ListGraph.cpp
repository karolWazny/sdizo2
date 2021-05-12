#include "ListGraph.h"

bool operator==(const ListGraphVertex& v, const ListGraphVertex& w) {
    return v.id == w.id;
}

bool operator==(const ListGraphEdge& e, const ListGraphEdge& f) {
    return e.finalVertex == f.finalVertex;
}

bool operator==(const Edge& e, const Edge& f) {
    return e.finalVertex == f.finalVertex && e.initialVertex == f.initialVertex;
}

bool operator>=(const Edge& e, const Edge& f) {
    return e.weight >= f.weight;
}

bool operator<=(const Edge& e, const Edge& f) {
    return e.weight <= f.weight;
}

bool operator>(const Edge& e, const Edge& f) {
    return e.weight > f.weight;
}

bool operator<(const Edge& e, const Edge& f) {
    return e.weight < f.weight;
}

void ListGraph::addVertex(vertexId_t vertexId) {
    auto vertex = ListGraphVertex(vertexId);
    if(vertices.contains(vertex))
    {
        //do nothing
    } else {
        vertices.pushBack(vertex);
    }
}

void ListGraph::addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {
    ListGraphVertex v;
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
    this->vertices.remove((ListGraphVertex) vertexId);
}

void ListGraph::removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) {
    auto index = vertices.firstIndexOf(ListGraphVertex(initialVertex));
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

size_t ListGraph::edgesAmountDirected() {
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
    //zwracany podgraf
    auto tree = GraphPointer(static_cast<Graph*>(new ListGraph()));
    //drzewo zawierające identyfikatory już dodanych wierzchołków
    rbtree<vertexId_t> addedVertices;
    //kolejka krawędzi wychodzących z wierzchołków już dodanych
    FixedMinimumHeap<Edge> edgesToAdd(edgesAmountDirected());
    ListGraphVertex lastAddedVertex;
    while(tree->verticesAmount() < this->verticesAmount()) {
        //wybór kolejnego wierzchołka do dodania
        if(edgesToAdd.getSize() == 0) //gdy żadne wierzchołki nie są dostępne z dotychczas dodanych
        {
            auto iterator = vertices.iterator();
            while(iterator.hasNext())
            {
                lastAddedVertex = iterator.next();
                if(!addedVertices.contains(lastAddedVertex.id))
                {
                    tree->addVertex(lastAddedVertex.id);
                    break;
                }
            }
        } else { //dołożenie najlżejszej krawędzi, która nie utworzy cyklu
            while(true){

                auto edge = edgesToAdd.extractRoot();
                //jeżeli na drugim końcu rozważanej krawędzi jest wierzchołek,
                //którego żeśmy jeszcze nie dodali:
                if(!addedVertices.contains(edge.finalVertex))
                {
                    auto iterator = vertices.iterator();
                    while(iterator.hasNext())
                    {
                        lastAddedVertex = iterator.next();
                        if(lastAddedVertex.id == edge.finalVertex)
                        {
                            tree->addVertex(lastAddedVertex.id);
                            tree->addEdgeDirected(edge.initialVertex, edge.finalVertex, edge.weight);
                            tree->addEdgeDirected(edge.finalVertex, edge.initialVertex, edge.weight);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        //dodanie nowego wierzchołka do listy dodanych wierzchołków
        addedVertices.put(lastAddedVertex.id);

        auto iterator = lastAddedVertex.edges.iterator();
        while(iterator.hasNext()) {
            Edge current{};
            current.initialVertex = lastAddedVertex.id;
            auto edge = iterator.next();
            current.finalVertex = edge.finalVertex;
            current.weight = edge.weight;

            edgesToAdd.add(current);
        }

        edgesToAdd.removeWhere([addedVertices](Edge edge) {return addedVertices.contains(edge.finalVertex);});
    }



    return tree;
}

GraphPointer ListGraph::MSTFB() {
    return GraphPointer();
}
