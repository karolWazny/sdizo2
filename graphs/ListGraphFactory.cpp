#include "ListGraphFactory.h"

GraphPointer ListGraphFactory::build(size_t vertices) {
    return GraphPointer(new ListGraph(vertices));
}

GraphPointer ListGraphFactory::build(size_t vertices, size_t edges) {
    return GraphPointer(new ListGraph(vertices));
}
