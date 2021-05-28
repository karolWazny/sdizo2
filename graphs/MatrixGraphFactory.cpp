#include "MatrixGraphFactory.h"

GraphPointer MatrixGraphFactory::build(size_t vertices) {
    return GraphPointer(new MatrixGraph(vertices));
}

GraphPointer MatrixGraphFactory::build(size_t vertices, size_t edges) {
    return GraphPointer(new MatrixGraph(vertices, edges));
}
