#ifndef SDIZO_1_NODEFACTORY_H
#define SDIZO_1_NODEFACTORY_H

#include "Node.h"

template <typename T>
class NodeFactory
{
public:
    virtual NodePointer<T> createNode(T) = 0;

    virtual NodePointer<T> createSentinel(NodePointer<T> parent) = 0;

    virtual NodePointer<T> createSentinel() = 0;
};

#endif //SDIZO_1_NODEFACTORY_H
