#include "Graph.h"

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

long Graph::getWeight() {
    return 0;
}
