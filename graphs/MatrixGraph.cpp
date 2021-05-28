#include "MatrixGraph.h"
#include <iomanip>

void MatrixGraph::addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept {
    try {
        //jeżeli przynajmniej jeden z wierzchołków nie istnieje,
        //wyszukanie rzuci wyjątkiem, który złapiemy;
        //operacja zakończy się cichum niepowodzeniem
        auto& initVer = vertexWithId(initialVertex);
        auto& finVer = vertexWithId(finalVertex);
        //jeżeli taka krawędź jeszcze nie istnieje
        for(size_t i = 0; i < verticesAmount(); i++) {
            if(edgesAmount() == vertices[i].incidences.getLength())
                vertices[i].incidences.pushBack(Incidence::NONE);
            if(i != initialVertex && i != finalVertex) {
                vertices[i].incidences[edgesAmount()] = Incidence::NONE;
            }
        }
        initVer.incidences[edgesAmount()] = Incidence::OUT;
        finVer.incidences[edgesAmount()] = Incidence::IN;
        if(weights.getLength() == edgesAmount())
            weights.pushBack(weight);
        else
            weights[edgesAmount()] = weight;
        edgesNumber++;
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
}

void MatrixGraph::removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept {
    try {
        //jeżeli przynajmniej jeden z wierzchołków nie istnieje,
        //wyszukanie rzuci wyjątkiem, który złapiemy;
        //operacja zakończy się cichum niepowodzeniem
        auto& initVer = vertexWithId(initialVertex);
        auto& finVer = vertexWithId(finalVertex);
        for(size_t i = 0; i < edgesAmount(); i++) {
            //sprawdzamy, czy taka krawędź istnieje
            if(initVer.incidences[i] == Incidence::OUT) {
                //jeżeli ta krawędź jest skierowana
                //to ją usuwamy całkiem
                if(finVer.incidences[i] == Incidence::IN){
                    auto iterator = vertices.iterator();
                    while(iterator.hasNext()){
                        auto& ver = iterator.next();
                        ver.incidences.removeAt(i);
                    }
                    weights.removeAt(i);
                    edgesNumber--;
                    return;
                } else if(finVer.incidences[i] == Incidence::OUT) {
                    // jeżeli krawędź była nieskierowana, zamienia się
                    // w skierowaną;
                    // ten feature służy głównie ujednoliceniu
                    // zachowania z ListGraphem
                    initVer.incidences[i] = Incidence::IN;
                    return;
                }
            }
        }
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
}

vertexId_t MatrixGraph::verticesAmount() {
    return vertices.getLength();
}

vertexId_t MatrixGraph::edgesAmount() {
    return edgesNumber;
}

PathPointer MatrixGraph::shortestPathDijkstra(vertexId_t initialVertex, vertexId_t finalVertex) {
    //kolejka z wierzchołkami
    FixedMinimumHeap<PathVertex> pathVertices(verticesAmount());
    LinkedList<PathVertex> visitedVertices;
    for(size_t i = 0; i < verticesAmount(); i++) {
        pathVertices.add(PathVertex(i));
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
        MatrixGraphVertex currentVertex = vertices[pathVertex.id];

        //iteracja po krawędziach, żeby znaleźć sąsiadów aktualnego węzła
        for(size_t i = 0; i < edgesAmount(); i++) {
            if(currentVertex.incidences[i] == Incidence::OUT) {
                for(size_t k = 0; k < verticesAmount(); k++) {
                    if(vertices[k].incidences[i] != Incidence::NONE && k != pathVertex.id) {
                        Edge edge = Edge(pathVertex.id, k, weights[i]);
                        pathVertices.modifyIf([edge, pathVertex](PathVertex& vertex)->void {
                            if(vertex.pathLength > edge.weight + pathVertex.pathLength&& pathVertex.pathLength != INT64_MAX) {
                                vertex.pathLength = edge.weight + pathVertex.pathLength;
                                vertex.parent = pathVertex.id;
                            }
                        }, [edge](PathVertex vertex)->bool {
                            return edge.finalVertex == vertex.id;
                        });
                    }
                }
            }
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

PathPointer MatrixGraph::shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) {
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
    pathVertices[initialVertex].pathLength = 0;
    //wrzucenie do kolejki krawędzi wychodzących z pierwszego wierzchołka
    {
        auto& initial = vertexWithId(initialVertex);
        for(size_t i = 0; i < edgesAmount(); i++) {
            if(vertices[initialVertex].incidences[i] == Incidence::OUT) {
                for(size_t k = 0; k < verticesAmount(); k++) {
                    if(vertices[k].incidences[i] != Incidence::NONE && k != initialVertex) {
                        queue.pushFront(Edge(initialVertex, k, weights[i]));
                        break;
                    }
                }
            }
        }
    }
    //przebiegi pętli, czyli relaksacje
    for(size_t i = 0; i < verticesAmount() - 1; i++) {
        auto iterator = queue.iterator();
        while(iterator.hasNext()) {
            auto edge = iterator.next();
            auto parentVertex = pathVertices[edge.initialVertex];
            //tu relaksacja i-tej krawędzi z kolejki
            bool verticesAffected{false};
            if(pathVertices[edge.finalVertex].pathLength > edge.weight + parentVertex.pathLength) {
                pathVertices[edge.finalVertex].pathLength = edge.weight + parentVertex.pathLength;
                pathVertices[edge.finalVertex].parent = edge.initialVertex;
                verticesAffected = true;
            }
            //jeżeli dokonano relaksacji
            if(verticesAffected) {
                //trzeba dodać krawędzie wychodzące
                //z końcowego wierzcholka zrelaksowanej krawedzi
                //do kolejki
                auto& initial = vertexWithId(edge.finalVertex);
                for(size_t j = 0; j < edgesAmount(); j++) {
                    if(initial.incidences[j] == Incidence::OUT) {
                        for(size_t k = 0; k < verticesAmount(); k++) {
                            if(vertices[k].incidences[j] != Incidence::NONE && k != edge.finalVertex) {
                                queue.pushFront(Edge(edge.finalVertex,
                                                     k,
                                                     weights[j]));
                                break;
                            }
                        }
                    }
                }
            }
            iterator.remove();
        }
        /*if(i == verticesAmount() - 1) {
            //jest ujemny cykl i trzeba z tym żyć
        }*/
    }
    path->totalWeight = pathVertices[finalVertex].pathLength;
    vertexId_t currentVertex = finalVertex;
    while(currentVertex != INT32_MAX) {
        path->vertices.pushFront(currentVertex);
        currentVertex = pathVertices[currentVertex].parent;
    }
    return path;
}

GraphPointer MatrixGraph::MSTPrim() {
    //zwracany podgraf
    auto tree = GraphPointer(static_cast<Graph*>(new MatrixGraph(verticesAmount(), verticesAmount() - 1)));
    size_t numberOfAddedVertices{};
    //drzewo zawierające identyfikatory już dodanych wierzchołków
    rbtree<vertexId_t> addedVertices;
    //kolejka krawędzi wychodzących z wierzchołków już dodanych
    FixedMinimumHeap<Edge> edgesToAdd(edgesAmount());
    vertexId_t lastAddedVertex{};
    while(numberOfAddedVertices < this->verticesAmount()) {
        //wybór kolejnego wierzchołka do dodania
        if(edgesToAdd.getSize() == 0) //gdy żadne wierzchołki nie są dostępne z dotychczas dodanych
        {
            for(size_t i = 0; i < verticesAmount(); i++) {
                if(!addedVertices.contains(i))
                {
                    numberOfAddedVertices++;
                    lastAddedVertex = i;
                    break;
                }
            }
        } else { //dołożenie najlżejszej krawędzi, która nie utworzy cyklu
            auto edge = edgesToAdd.extractRoot();
            for(size_t i = 0; i < verticesAmount(); i++) {
                if(i == edge.finalVertex)
                {
                    //tree->addVertex(lastAddedVertex.id);
                    tree->addEdgeUndirected(edge.initialVertex, edge.finalVertex, edge.weight);
                    numberOfAddedVertices++;
                    lastAddedVertex = i;
                    break;
                }
            }
        }
        //dodanie nowego wierzchołka do listy dodanych wierzchołków
        addedVertices.put(lastAddedVertex);

        //dodajemy krawędzie wyjściowe z nowego wierzchołka do kolejki
        for(size_t i = 0; i < edgesAmount(); i++) {
            if(vertices[lastAddedVertex].incidences[i] == Incidence::OUT) {
                for(size_t k = 0; k < verticesAmount(); k++) {
                    if(vertices[k].incidences[i] != Incidence::NONE && k != lastAddedVertex) {
                        Edge current{};
                        current.initialVertex = lastAddedVertex;
                        current.finalVertex = k;
                        current.weight = weights[i];

                        edgesToAdd.add(current);
                        break;
                    }
                }
            }
        }
        //usuwamy krawędzie, których dodanie powodowałoby powstanie cyklu
        edgesToAdd.removeWhere([addedVertices](Edge edge) {return addedVertices.contains(edge.finalVertex);});
    }



    return tree;
}

GraphPointer MatrixGraph::MSTKruskal() {
    auto mst = GraphPointer(static_cast<Graph*>(new MatrixGraph(verticesAmount(), verticesAmount() - 1)));
    Array<vertexId_t> colorMappings(verticesAmount());
    FixedMinimumHeap<Edge> edges(edgesAmount() * 2);
    //przygotowanie struktur pomocniczych
    for(size_t i = 0; i < verticesAmount(); i++) {
        colorMappings[i] = i;

        for(size_t k = 0; k < edgesAmount(); k++) {
            if(vertices[i].incidences[k] == Incidence::OUT) {
                for(size_t otherVertexIndex = 0; otherVertexIndex < verticesAmount(); otherVertexIndex++){
                    if(vertices[otherVertexIndex].incidences[k] != Incidence::NONE && otherVertexIndex != i) {
                        edges.add(Edge(i, otherVertexIndex, weights[k]));
                        break;
                    }
                }
            }
        }
    }
    size_t addedEdges{};
    //dodawanie do mst kolejnych krawędzi
    while(edges.getSize() && addedEdges < verticesAmount() - 1) {
        auto edge = edges.extractRoot();
        vertexId_t initialColor{};
        vertexId_t finalColor{};
        //do tego dobrze by było użyć słownik, ale jeszcze nie ma napisanego słownika
        for(int i = 0; i < colorMappings.getLength(); i++) {
            if(i == edge.initialVertex)
            {
                initialColor = colorMappings[i];
            } else if(i == edge.finalVertex) {
                finalColor = colorMappings[i];
            }
        }
        //jeżeli dodanie tej krawędzi nie spowoduje powstania cyklu
        if(initialColor != finalColor) {
            //przekolorowanie węzłów
            for(int i = 0; i < colorMappings.getLength(); i++) {
                if(colorMappings[i] == initialColor) {
                    colorMappings[i] = finalColor;
                }
            }
            mst->addEdgeUndirected(edge.initialVertex, edge.finalVertex, edge.weight);
            addedEdges++;
        }
    }

    return mst;
}

std::string MatrixGraph::getRepresentation() {
    std::ostringstream stream;

    stream << "[";

    for(size_t i = 0; i < verticesAmount(); i++) {
        stream << "\n" << i << ":";
        for(size_t k = 0; k < edgesAmount(); k++) {
            auto toBeWritten = 0;
            if(vertices[i].incidences[k] == Incidence::OUT)
                toBeWritten = weights[k];
            else if(vertices[i].incidences[k] == Incidence::IN)
                toBeWritten = -weights[k];
            stream << std::setw(4) /*<< std::internal*/ << toBeWritten;
        }
    }
    if(verticesAmount())
        stream << "\n";
    stream << "]";
    return stream.str();
}

void MatrixGraph::addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) noexcept {
    try {
        //jeżeli przynajmniej jeden z wierzchołków nie istnieje,
        //wyszukanie rzuci wyjątkiem, który złapiemy;
        //operacja zakończy się cichum niepowodzeniem
        auto& initVer = vertexWithId(initialVertex);
        auto& finVer = vertexWithId(finalVertex);
        //jeżeli taka krawędź jeszcze nie istnieje
        for(size_t i = 0; i < verticesAmount(); i++) {
            if(edgesAmount() == vertices[i].incidences.getLength())
                vertices[i].incidences.pushBack(Incidence::NONE);
            if(i != initialVertex && i != finalVertex) {
                vertices[i].incidences[edgesAmount()] = Incidence::NONE;
            }
        }
        initVer.incidences[edgesAmount()] = Incidence::OUT;
        finVer.incidences[edgesAmount()] = Incidence::OUT;
        if(weights.getLength() == edgesAmount())
            weights.pushBack(weight);
        else
            weights[edgesAmount()] = weight;
        edgesNumber++;
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
}

void MatrixGraph::removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) noexcept {
    try {
        //jeżeli przynajmniej jeden z wierzchołków nie istnieje,
        //wyszukanie rzuci wyjątkiem, który złapiemy;
        //operacja zakończy się cichum niepowodzeniem
        auto& initVer = vertexWithId(initialVertex);
        auto& finVer = vertexWithId(finalVertex);
        for(size_t i = 0; i < edgesAmount(); i++) {
            //sprawdzamy, czy taka krawędź istnieje
            if(initVer.incidences[i] == Incidence::OUT && finVer.incidences[i] == Incidence::OUT) {
                //jeżeli ta krawędź jest skierowana
                //to ją usuwamy całkiem
                if(finVer.incidences[i] == Incidence::IN){
                    auto iterator = vertices.iterator();
                    while(iterator.hasNext()){
                        auto& ver = iterator.next();
                        ver.incidences.removeAt(i);
                    }
                    weights.removeAt(i);
                    edgesNumber--;
                    return;
                }
            }
        }
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
}

MatrixGraphVertex &MatrixGraph::vertexWithId(vertexId_t id) {
    return vertices[id];
}

MatrixGraph::MatrixGraph(size_t size) {
    vertices = Array<MatrixGraphVertex>(size);
    weights = Array<int>();
    edgesNumber = 0;
}

MatrixGraph::MatrixGraph(size_t size, size_t edges) {
    edgesNumber = 0;
    vertices = Array<MatrixGraphVertex>(size);
    for(size_t i = 0; i < size; i ++) {
        vertices[i].incidences = Array<Incidence>(edges);
    }
    weights = Array<int>(edges);
}
