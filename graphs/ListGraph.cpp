#include "ListGraph.h"

void ListGraph::addVertex() {
    size++;
    auto vertix = ListGraphVertix();
    vertix.id = usedVertixIds;
    usedVertixIds++;
    vertices.pushBack(vertix);
}
