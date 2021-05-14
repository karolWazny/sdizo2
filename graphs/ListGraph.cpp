#include "ListGraph.h"

#include <memory>

bool operator==(const ListGraphVertex& v, const ListGraphVertex& w) {
    return v.id == w.id;
}

bool operator==(const ListGraphEdge& e, const ListGraphEdge& f) {
    return e.finalVertex == f.finalVertex;
}

bool operator==(const Edge& e, const Edge& f) {
    return e.finalVertex == f.finalVertex && e.initialVertex == f.initialVertex;
}

bool operator==(VertexColor v, VertexColor f) {
    return f.id == v.id;
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

bool operator>=(const PathVertex& e, const PathVertex& f) {
    return e.pathLength >= f.pathLength;
}

bool operator<=(const PathVertex& e, const PathVertex& f) {
    return e.pathLength <= f.pathLength;
}

bool operator>(const PathVertex& e, const PathVertex& f) {
    return e.pathLength > f.pathLength;
}

bool operator<(const PathVertex& e, const PathVertex& f) {
    return e.pathLength < f.pathLength;
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

PathPointer ListGraph::shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) {
    //kolejka z wierzchołkami
    FixedMinimumHeap<PathVertex> pathVertices(verticesAmount());
    LinkedList<PathVertex> visitedVertices;
    {
        auto vertexIterator = vertices.iterator();
        //zapełnienie kolejki
        while (vertexIterator.hasNext()) {
            auto vertex = vertexIterator.next();
            pathVertices.add(PathVertex(vertex.id));
        }
    }
    pathVertices.modifyIf([](PathVertex& vertex)->void {
        vertex.pathLength = 0;
    }, [initialVertex](PathVertex vertex)->bool {
        return vertex.id == initialVertex;
    });
    //relaksacja kolejnych krawędzi
    while(pathVertices.getSize()) {
        auto pathVertex = pathVertices.extractRoot();
        //dodajemy węzeł do zbioru węzłów odwiedzonych
        visitedVertices.pushFront(pathVertex);
        auto vertexIterator = vertices.iterator();
        ListGraphVertex currentVertex;
        //szukamy w grafie dodawanego węzła, żeby dorwać jego listę krawędzi
        while(vertexIterator.hasNext()) {
            currentVertex = vertexIterator.next();
            if(currentVertex.id == pathVertex.id) {
                break;
            }
        }
        auto edgeIterator = currentVertex.edges.iterator();
        //relaksacja krawędzi wychodzących z dodanego wierzchołka
        while(edgeIterator.hasNext()) {
            const auto& edge = edgeIterator.next();
            pathVertices.modifyIf([edge, pathVertex](PathVertex& vertex)->void {
                if(vertex.pathLength > edge.weight + pathVertex.pathLength) {
                    vertex.pathLength = edge.weight + pathVertex.pathLength;
                    vertex.parent = pathVertex.id;
                }
            }, [edge](PathVertex vertex)->bool {
                return edge.finalVertex == vertex.id;
            });
        }
    }
    //opracowanie konkretnej ścieżki z węzła do węzła
    //w opraciu o drzewo najkrótszych ścieżek
    auto path = std::make_shared<Path>();
    auto recentVertex = finalVertex;
    while(recentVertex != INT32_MAX) {
        path->vertices.pushFront(recentVertex);
        auto iterator = visitedVertices.iterator();
        while(iterator.hasNext()) {
            auto vertex = iterator.next();
            if(vertex.id == recentVertex) {
                recentVertex = vertex.parent;
                if(vertex.id == finalVertex) {
                    path->totalWeight = vertex.pathLength;
                }
                break;
            }
        }
    }
    return path;
}

PathPointer ListGraph::shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) {
    auto path = std::make_shared<Path>();
    //utworzenie struktur pomocniczych
    //kolejka
    LinkedList<Edge> queue;
    //tablica pomocnicza wierzchołków
    Array<PathVertex> pathVertices(verticesAmount());
    {
        auto vertexIterator = vertices.iterator();
        vertexId_t index{};
        while(vertexIterator.hasNext()) {
            auto vertex = vertexIterator.next();
            pathVertices[index] = PathVertex(vertex.id);
            index++;
        }
    }
    //wrzucenie pierwszego wierzchołka
    auto& initialVertexObject = pathVertices.find([initialVertex](PathVertex ver)->bool{
        return initialVertex == ver.id;
    });
    initialVertexObject.pathLength = 0;
    //wrzucenie do kolejki krawędzi wychodzących z pierwszego wierzchołka
    {
        auto iterator = edgesFromVertex(initialVertex);
        while(iterator.hasNext()) {
            auto edge = iterator.next();
            queue.pushFront(Edge(initialVertexObject.id, edge.finalVertex, edge.weight));
        }
    }
    //przebiegi pętli, czyli relaksacje
    for(size_t i = 0; i < verticesAmount() - 1/* kolejka jest niepusta */; i++) {
        auto iterator = queue.iterator();
        while(iterator.hasNext()) {
            auto edge = iterator.next();
            auto parentVertex = pathVertices.find([edge](PathVertex vertex)->bool{
                return edge.initialVertex == vertex.id;
            });
            //tu relaksacja i-tej krawędzi z kolejki
            auto verticesAffected = pathVertices.forEach([edge, parentVertex](PathVertex& vertex)->bool {
                if(vertex.id != edge.finalVertex)
                    return false;
                if(vertex.pathLength > edge.weight + parentVertex.pathLength) {
                    vertex.pathLength = edge.weight + parentVertex.pathLength;
                    vertex.parent = parentVertex.id;
                    return true;
                }
                return false;
            });
            //jeżeli dokonano relaksacji
            if(verticesAffected) {
                auto edgeIterator = edgesFromVertex(edge.finalVertex);
                while(edgeIterator.hasNext()) {
                    auto edgeToBeAdded = edgeIterator.next();
                    queue.pushFront(Edge(edge.finalVertex,
                                         edgeToBeAdded.finalVertex,
                                         edgeToBeAdded.weight));
                }
            }
            iterator.remove();
        }
        if(i == verticesAmount() - 1) {
            //jest ujemny cykl i trzeba z tym żyć
        }
    }
    {
        auto vertex = pathVertices.find([finalVertex](PathVertex ver)->bool{
           return finalVertex == ver.id;
        });
        path->totalWeight = vertex.pathLength;
    }
    vertexId_t currentVertex = finalVertex;
    while(currentVertex != INT32_MAX) {
        path->vertices.pushFront(currentVertex);
        auto vertex = pathVertices.find([currentVertex](PathVertex ver)->bool{
            return currentVertex == ver.id;
        });
        currentVertex = vertex.parent;
    }
    return path;
}

GraphPointer ListGraph::MSTPrim() {
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
            auto edge = edgesToAdd.extractRoot();
            auto iterator = vertices.iterator();
            //znajdujemy dodawany, wierzchołek; przyda się, żeby dodać jego krawędzie wyjściowe do kolejki
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
        }
        //dodanie nowego wierzchołka do listy dodanych wierzchołków
        addedVertices.put(lastAddedVertex.id);

        //dodajemy krawędzie wyjściowe z nowego wierzchołka do kolejki
        auto iterator = lastAddedVertex.edges.iterator();
        while(iterator.hasNext()) {
            Edge current{};
            current.initialVertex = lastAddedVertex.id;
            auto edge = iterator.next();
            current.finalVertex = edge.finalVertex;
            current.weight = edge.weight;

            edgesToAdd.add(current);
        }
        //usuwamy krawędzie, których dodanie powodowałoby powstanie cyklu
        edgesToAdd.removeWhere([addedVertices](Edge edge) {return addedVertices.contains(edge.finalVertex);});
    }



    return tree;
}

GraphPointer ListGraph::MSTKruskal() {
    auto mst = GraphPointer(static_cast<Graph*>(new ListGraph()));
    auto iterator = vertices.iterator();
    size_t index = 0;
    Array<VertexColor> colorMappings(verticesAmount());
    FixedMinimumHeap<Edge> edges(edgesAmountDirected());
    //przygotowanie struktur pomocniczych
    while(iterator.hasNext()) {
        auto& vertex = iterator.next();
        mst->addVertex(vertex.id);
        colorMappings[index] = VertexColor(vertex.id, vertex.id);
        auto edgesIterator = vertex.edges.iterator();
        //utworzenie kolejki krawędzi
        while(edgesIterator.hasNext())
        {
            auto edge = edgesIterator.next();
            edges.add(Edge(vertex.id, edge.finalVertex, edge.weight));
        }
        index++;
    }

    size_t addedEdges{};
    //dodawanie do mst kolejnych krawędzi
    while(edges.getSize() && addedEdges < verticesAmount() - 1) {
        auto edge = edges.extractRoot();
        vertexId_t initialColor;
        vertexId_t finalColor;
        //do tego dobrze by było użyć słownik, ale jeszcze nie ma napisanego słownika
        for(int i = 0; i < colorMappings.getLength(); i++) {
            if(colorMappings[i].id == edge.initialVertex)
            {
                initialColor = colorMappings[i].color;
            } else if(colorMappings[i].id == edge.finalVertex) {
                finalColor = colorMappings[i].color;
            }
        }
        //jeżeli dodanie tej krawędzi nie spowoduje powstania cyklu
        if(initialColor != finalColor) {
            //przekolorowanie węzłów
            for(int i = 0; i < colorMappings.getLength(); i++) {
                if(colorMappings[i].color == initialColor) {
                    colorMappings[i].color = finalColor;
                }
            }
            mst->addEdgeDirected(edge.initialVertex, edge.finalVertex, edge.weight);
            mst->addEdgeDirected(edge.finalVertex, edge.initialVertex, edge.weight);
            addedEdges++;
        }
    }

    return mst;
}

std::string ListGraph::getRepresentation() {
    std::string output = "[ \n";
    auto vertexIterator = vertices.iterator();
    while(vertexIterator.hasNext())
    {
        auto vertex = vertexIterator.next();
        output += "\t";
        output += vertex.toString();
        output += "\n";
    }
    output += "]";
    return output;
}

ListIterator<ListGraphEdge> ListGraph::edgesFromVertex(vertexId_t vertexId) {
    auto iterator = vertices.iterator();
    while(iterator.hasNext()) {
        auto& vertex = iterator.next();
        if(vertex.id == vertexId) {
            return vertex.edges.iterator();
        }
    }
    throw std::exception();
}

std::string ListGraphVertex::toString() {
    std::string output = "ID: ";
    output += std::to_string(id);
    output += " -> [";
    auto iterator = edges.iterator();
    while(iterator.hasNext())
    {
        auto edge = iterator.next();
        output += std::to_string(edge.finalVertex);
        output += "(";
        output += std::to_string(edge.weight);
        output += ")";
        if(iterator.hasNext())
            output += ", ";
    }
    output += "]";
    return output;
}
