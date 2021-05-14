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
    return PathPointer();
}

PathPointer MatrixGraph::shortestPathBF(vertexId_t initialVertex, vertexId_t finalVertex) {
    return PathPointer();
}

GraphPointer MatrixGraph::MSTPrim() {
    return GraphPointer();
}

GraphPointer MatrixGraph::MSTKruskal() {
    return GraphPointer();
}

std::string MatrixGraph::getRepresentation() {
    return std::string();
}

void MatrixGraph::addEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {

}

void MatrixGraph::removeEdgeUndirected(vertexId_t initialVertex, vertexId_t finalVertex) {

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
