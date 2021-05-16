#ifndef SDIZO2_GRAPHFACTORY_H
#define SDIZO2_GRAPHFACTORY_H

#include "Graph.h"

class GraphFactory {
public:
    virtual GraphPointer build(size_t vertices) = 0;
};

using FactoryPointer = std::shared_ptr<GraphFactory>;

#endif //SDIZO2_GRAPHFACTORY_H
