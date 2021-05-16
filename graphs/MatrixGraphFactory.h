#ifndef SDIZO2_MATRIXGRAPHFACTORY_H
#define SDIZO2_MATRIXGRAPHFACTORY_H

#include "GraphFactory.h"
#include "MatrixGraph.h"

class MatrixGraphFactory : public GraphFactory {
public:
    GraphPointer build(size_t vertices) override;
};


#endif //SDIZO2_MATRIXGRAPHFACTORY_H
