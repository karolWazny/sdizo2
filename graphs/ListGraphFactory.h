#ifndef SDIZO2_LISTGRAPHFACTORY_H
#define SDIZO2_LISTGRAPHFACTORY_H

#include "GraphFactory.h"
#include "ListGraph.h"

class ListGraphFactory : public GraphFactory{
public:
    GraphPointer build(size_t vertices) override;
    GraphPointer build(size_t vertices, size_t edges) override;
};

#endif //SDIZO2_LISTGRAPHFACTORY_H
