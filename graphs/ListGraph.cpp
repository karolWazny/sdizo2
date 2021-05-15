#include "ListGraph.h"

#include <memory>

bool operator==(const ListGraphVertex& v, const ListGraphVertex& w) {
    return v.id == w.id;
}

bool operator==(const ListGraphEdge& e, const ListGraphEdge& f) {
    return e.finalVertex == f.finalVertex;
}

void ListGraph::addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {
    if(finalVertex >= verticesAmount())
        return; //ciche niepowodzenie, jeżeli drugi wierzchołek nie istnieje w grafie
    auto index = vertices[initialVertex].edges.firstIndexOf((ListGraphEdge)finalVertex);
    try{
        if(index > -1)
        {
            //jeżeli taka krawędź już istnieje, aktualizujemy jej wagę
            vertices[initialVertex].edges.get(index).weight = weight;
        } else {
            vertices[initialVertex].edges.pushBack(ListGraphEdge(finalVertex, weight));
        }
    } catch (std::exception& exception) {

    }
}

void ListGraph::removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) {
    try {
        auto& initVer = vertices[initialVertex];
        initVer.edges.remove(ListGraphEdge(finalVertex));
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
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

PathPointer ListGraph::shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) {
    //kolejka z wierzchołkami
    FixedMinimumHeap<PathVertex> pathVertices(verticesAmount());
    LinkedList<PathVertex> visitedVertices;
    //zapełnienie kolejki
    for(size_t i = 0; i < verticesAmount(); i++) {
        pathVertices.add(i);
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
        //szukamy w grafie dodawanego węzła, żeby dorwać jego listę krawędzi
        auto edgeIterator = edgesFromVertex(pathVertex.id);
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
    for(size_t i = 0; i < verticesAmount(); i++) {
        pathVertices[i] = PathVertex(i);
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
    auto tree = GraphPointer(static_cast<Graph*>(new ListGraph(verticesAmount())));
    //drzewo zawierające identyfikatory już dodanych wierzchołków
    rbtree<vertexId_t> addedVertices;
    //kolejka krawędzi wychodzących z wierzchołków już dodanych
    FixedMinimumHeap<Edge> edgesToAdd(edgesAmount());
    vertexId_t lastAddedVertex;
    size_t treeVerticesAmount{};
    while(treeVerticesAmount < this->verticesAmount()) {
        //wybór kolejnego wierzchołka do dodania
        if(edgesToAdd.getSize() == 0) //gdy żadne wierzchołki nie są dostępne z dotychczas dodanych
        {
            for(size_t i = 0; i < verticesAmount(); i++) {
                if(!addedVertices.contains(i))
                {
                    lastAddedVertex = i;
                    treeVerticesAmount++;
                    break;
                }
            }
        } else { //dołożenie najlżejszej krawędzi, która nie utworzy cyklu
            auto edge = edgesToAdd.extractRoot();
            lastAddedVertex = edge.finalVertex;
            tree->addEdgeUndirected(edge.initialVertex, edge.finalVertex, edge.weight);
            treeVerticesAmount++;
        }
        //dodanie nowego wierzchołka do listy dodanych wierzchołków
        addedVertices.put(lastAddedVertex);

        //dodajemy krawędzie wyjściowe z nowego wierzchołka do kolejki
        auto iterator = edgesFromVertex(lastAddedVertex);
        while(iterator.hasNext()) {
            Edge current{};
            current.initialVertex = lastAddedVertex;
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
    auto mst = GraphPointer(static_cast<Graph*>(new ListGraph(verticesAmount())));
    auto iterator = vertices.iterator();
    size_t index = 0;
    Array<VertexColor> colorMappings(verticesAmount());
    FixedMinimumHeap<Edge> edges(edgesAmount());
    //przygotowanie struktur pomocniczych
    for(size_t i = 0; i < verticesAmount(); i++) {
        colorMappings[i] = VertexColor(i, i);

        //zapełnianie kolejki krawędzi
        auto edgesIterator = vertices[i].edges.iterator();
        while(edgesIterator.hasNext())
        {
            auto edge = edgesIterator.next();
            edges.add(Edge(i, edge.finalVertex, edge.weight));
        }
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
            mst->addEdgeUndirected(edge.initialVertex, edge.finalVertex, edge.weight);
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
    return vertices[vertexId].edges.iterator();
}

void ListGraph::addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {
    addEdgeDirected(initialVertex, finalVertex, weight);
    addEdgeDirected(finalVertex, initialVertex, weight);
}

void ListGraph::removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) {
    removeEdgeDirected(initialVertex, finalVertex);
    removeEdgeDirected(finalVertex, initialVertex);
}

ListGraph::ListGraph(size_t verticesAmount) {
    vertices = Array<ListGraphVertex>(verticesAmount);
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
