#include "MatrixGraph.h"

void MatrixGraph::addVertex(vertexId_t vertexId) {
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
    vertices.pushBack(ver);
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
        while(iterator.hasNext()) {
            auto& ver = iterator.next();
            if(ver.id != initialVertex && ver.id != finalVertex) {
                ver.incidences.pushBack(Incidence::NONE);
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
    auto vertexIterator = vertices.iterator();
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
    }
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
        MatrixGraphVertex currentVertex;
        //szukamy w grafie dodawanego węzła, żeby dorwać jego listę krawędzi
        while(vertexIterator.hasNext()) {
            currentVertex = vertexIterator.next();
            if(currentVertex.id == pathVertex.id) {
                break;
            }
        }
        for(size_t i = 0; i < edgesAmount(); i++) {
            if(currentVertex.incidences[i] == Incidence::OUT) {
                auto iterator = vertices.iterator();
                while(iterator.hasNext()) {
                    auto& vertex = iterator.next();
                    if(vertex.incidences[i] != Incidence::NONE && vertex.id != currentVertex.id) {
                        Edge edge = Edge(currentVertex.id, vertex.id, weights[i]);
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
    return PathPointer();
}

GraphPointer MatrixGraph::MSTPrim() {
    //zwracany podgraf
    auto tree = GraphPointer(static_cast<Graph*>(new MatrixGraph()));
    //drzewo zawierające identyfikatory już dodanych wierzchołków
    rbtree<vertexId_t> addedVertices;
    //kolejka krawędzi wychodzących z wierzchołków już dodanych
    FixedMinimumHeap<Edge> edgesToAdd(edgesAmount());
    MatrixGraphVertex lastAddedVertex;
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
                    tree->addEdgeUndirected(edge.initialVertex, edge.finalVertex, edge.weight);
                    break;
                }
            }
        }
        //dodanie nowego wierzchołka do listy dodanych wierzchołków
        addedVertices.put(lastAddedVertex.id);

        //dodajemy krawędzie wyjściowe z nowego wierzchołka do kolejki
        for(size_t i = 0; i < weights.getLength(); i++) {
            if(lastAddedVertex.incidences[i] == Incidence::OUT) {
                auto iterator = vertices.iterator();
                while(iterator.hasNext()) {
                    auto& ver = iterator.next();
                    if(ver.incidences[i] != Incidence::NONE && ver.id != lastAddedVertex.id) {
                        Edge current{};
                        current.initialVertex = lastAddedVertex.id;
                        current.finalVertex = ver.id;
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
    auto mst = GraphPointer(static_cast<Graph*>(new MatrixGraph()));
    auto iterator = vertices.iterator();
    size_t index = 0;
    Array<VertexColor> colorMappings(verticesAmount());
    FixedMinimumHeap<Edge> edges(edgesAmount() * 2);
    //przygotowanie struktur pomocniczych
    while(iterator.hasNext()) {
        auto& vertex = iterator.next();
        mst->addVertex(vertex.id);
        colorMappings[index] = VertexColor(vertex.id, vertex.id);

        //zapełnienie kolejki krawędzi
        for(size_t i = 0; i < edgesAmount(); i++) {
            if(vertex.incidences[i] == Incidence::OUT) {
                auto vertexIterator = vertices.iterator();
                while(vertexIterator.hasNext()) {
                    auto& otherVertex = vertexIterator.next();
                    if(otherVertex.incidences[i] != Incidence::NONE && otherVertex.id != vertex.id) {
                        edges.add(Edge(vertex.id, otherVertex.id, weights[i]));
                        break;
                    }
                }
            }
        }
        index++;
    }

    size_t addedEdges{};
    //dodawanie do mst kolejnych krawędzi
    while(edges.getSize() && addedEdges < verticesAmount() - 1) {
        auto edge = edges.extractRoot();
        vertexId_t initialColor{};
        vertexId_t finalColor{};
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
        auto iterator = vertices.iterator();
        while(iterator.hasNext()) {
            auto& ver = iterator.next();
            if(ver.id != initialVertex && ver.id != finalVertex) {
                ver.incidences.pushBack(Incidence::NONE);
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
    auto iterator = vertices.iterator();
    while(iterator.hasNext()) {
        auto& ver = iterator.next();
        if(ver.id == id) {
            return ver;
        }
    }
    throw std::exception();
}
