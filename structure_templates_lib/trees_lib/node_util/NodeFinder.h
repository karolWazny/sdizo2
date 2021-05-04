//
// Created by admin on 21.03.2021.
//

#ifndef SDIZO_1_NODEFINDER_H
#define SDIZO_1_NODEFINDER_H

#include "trees_lib/nodes/Node.h"

template <typename T>
class NodeFinder
{
public:
    virtual NodePointer<T> find() = 0;
    virtual NodePointer<T> getFound() = 0;
    virtual bool nodeFound() = 0;
};

#endif //SDIZO_1_NODEFINDER_H
