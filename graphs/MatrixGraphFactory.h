#ifndef SDIZO2_MATRIXGRAPHFACTORY_H
#define SDIZO2_MATRIXGRAPHFACTORY_H

#include "GraphFactory.h"
#include "MatrixGraph.h"

class MatrixGraphFactory : public GraphFactory {
public:
    GraphPointer build(size_t vertices) override;
    GraphPointer build(size_t vertices, size_t edges) override;
};


#endif //SDIZO2_MATRIXGRAPHFACTORY_H
