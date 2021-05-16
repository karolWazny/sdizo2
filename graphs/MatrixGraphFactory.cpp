#include "MatrixGraphFactory.h"

GraphPointer MatrixGraphFactory::build(size_t vertices) {
    return GraphPointer(new MatrixGraph(vertices));
}
