#include "MatrixGraph.h"

void MatrixGraph::addVertex(vertexId_t vertexId) {/*
    //sprawdzamy, czy nie mamy już takiego wierzchołka
    auto iterator = vertices.iterator();
    while(iterator.hasNext()) {
        if(iterator.next().id == vertexId)
            return;
    }
    //jeżeli nie mamy, to dodajemy
    MatrixGraphVertex ver;
    ver.id = vertexId;
    ver.incidences = Array<Incidence>(weights.getLength());
    ver.incidences.forEach([](Incidence& incidence)->bool{
        incidence = Incidence::NONE;
        return false;
    });
    vertices.pushBack(ver);*/
}

void MatrixGraph::addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {
    try {
        //jeżeli przynajmniej jeden z wierzchołków nie istnieje,
        //wyszukanie rzuci wyjątkiem, który złapiemy;
        //operacja zakończy się cichum niepowodzeniem
        auto& initVer = vertexWithId(initialVertex);
        auto& finVer = vertexWithId(finalVertex);
        for(size_t i = 0; i < edgesAmount(); i++) {
            //jeżeli taka krawędź już istnieje, tylko aktualizujemy jej wagę
            if(initVer.incidences[i] == Incidence::OUT && finVer.incidences[i] != Incidence::NONE) {
                weights[i] = weight;
                return;
            }
        }
        //jeżeli taka krawędź jeszcze nie istnieje
        auto iterator = vertices.iterator();
        for(size_t i = 0; i < verticesAmount(); i++) {
            if(i != initialVertex && i != finalVertex) {
                vertices[i].incidences.pushBack(Incidence::NONE);
            }
        }
        initVer.incidences.pushBack(Incidence::OUT);
        finVer.incidences.pushBack(Incidence::IN);
        weights.pushBack(weight);
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
}

void MatrixGraph::removeVertex(vertexId_t vertexId) {
    /*auto vertexIterator = vertices.iterator();
    while(vertexIterator.hasNext()) {
        auto& vertex = vertexIterator.next();
        if(vertex.id == vertexId) {
            for(auto i = edgesAmount(); i > 0; i--) {
                if(vertex.incidences[i - 1] != Incidence::NONE) {
                    weights.removeAt(i - 1);
                    vertices.forEach([i](MatrixGraphVertex& ver)->bool{
                        ver.incidences.removeAt(i - 1);
                        return false;
                    });
                }
            }
            vertexIterator.remove();
            break;
        }
    }*/
}

void MatrixGraph::removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) {
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
    return weights.getLength();
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
        auto vertexIterator = vertices.iterator();
        //szukamy w grafie dodawanego węzła, żeby dorwać jego listę krawędzi
        MatrixGraphVertex currentVertex = vertices[pathVertex.id];

        //iteracja po krawędziach, żeby znaleźć sąsiadów aktualnego węzła
        for(size_t i = 0; i < edgesAmount(); i++) {
            if(currentVertex.incidences[i] == Incidence::OUT) {
                for(size_t k = 0; k < verticesAmount(); k++) {
                    if(vertices[k].incidences[i] != Incidence::NONE && k != pathVertex.id) {
                        Edge edge = Edge(pathVertex.id, k, weights[i]);
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
    auto tree = GraphPointer(static_cast<Graph*>(new MatrixGraph(verticesAmount())));
    size_t numberOfAddedVertices{};
    //drzewo zawierające identyfikatory już dodanych wierzchołków
    rbtree<vertexId_t> addedVertices;
    //kolejka krawędzi wychodzących z wierzchołków już dodanych
    FixedMinimumHeap<Edge> edgesToAdd(edgesAmount());
    vertexId_t lastAddedVertex{};
    //while(tree->verticesAmount() < this->verticesAmount()) {
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
        for(size_t i = 0; i < weights.getLength(); i++) {
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
    auto mst = GraphPointer(static_cast<Graph*>(new MatrixGraph(verticesAmount())));
    Array<vertexId_t> colorMappings(verticesAmount());
    FixedMinimumHeap<Edge> edges(edgesAmount() * 2);
    //przygotowanie struktur pomocniczych
    for(size_t i = 0; i < verticesAmount(); i++) {
        colorMappings[i] = i;

        for(size_t k = 0; k < edgesAmount(); k++) {
            if(vertices[i].incidences[k] == Incidence::OUT) {
                //auto vertexIterator = vertices.iterator();
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
    return std::string();
}

void MatrixGraph::addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {
    try {
        //jeżeli przynajmniej jeden z wierzchołków nie istnieje,
        //wyszukanie rzuci wyjątkiem, który złapiemy;
        //operacja zakończy się cichum niepowodzeniem
        auto& initVer = vertexWithId(initialVertex);
        auto& finVer = vertexWithId(finalVertex);
        for(size_t i = 0; i < edgesAmount(); i++) {
            //jeżeli taka krawędź już istnieje, tylko aktualizujemy jej wagę
            if(initVer.incidences[i] == Incidence::OUT && finVer.incidences[i] == Incidence::OUT) {
                weights[i] = weight;
                return;
            }
        }
        //jeżeli taka krawędź jeszcze nie istnieje
        for(size_t i = 0; i < verticesAmount(); i++) {
            if(i != initialVertex && i != finalVertex) {
                vertices[i].incidences.pushBack(Incidence::NONE);
            }
        }
        initVer.incidences.pushBack(Incidence::OUT);
        finVer.incidences.pushBack(Incidence::OUT);
        weights.pushBack(weight);
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
}

void MatrixGraph::removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) {
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
                    return;
                }
            }
        }
    } catch (std::exception& exception) {
        //ciche niepowodzenie
    }
}

MatrixGraphVertex &MatrixGraph::vertexWithId(vertexId_t id) {
    /*auto iterator = vertices.iterator();
    while(iterator.hasNext()) {
        auto& ver = iterator.next();
        if(ver.id == id) {
            return ver;
        }
    }
    throw std::exception();*/
    return vertices[id];
}

MatrixGraph::MatrixGraph(size_t size) {
    vertices = Array<MatrixGraphVertex>(size);
    weights = Array<int>();
}
