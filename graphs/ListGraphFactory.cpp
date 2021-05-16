#include "ListGraphFactory.h"

GraphPointer ListGraphFactory::build(size_t vertices) {
    return GraphPointer(new ListGraph(vertices));
}
