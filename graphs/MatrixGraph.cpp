#include "MatrixGraph.h"

void MatrixGraph::addVertex(vertexId_t vertexId) {

}

void MatrixGraph::addEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex, int weight) {

}

void MatrixGraph::removeVertex(vertexId_t vertexId) {

}

void MatrixGraph::removeEdgeDirected(vertexId_t initialVertex, vertexId_t finalVertex) {

}

vertexId_t MatrixGraph::verticesAmount() {
    return 0;
}

vertexId_t MatrixGraph::edgesAmountDirected() {
    return 0;
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
