#ifndef SDIZO_1_NODEUTILITY_H
#define SDIZO_1_NODEUTILITY_H

#include "trees_lib/nodes/Node.h"
#include "RootFinder.h"

template <typename T>
class NodeUtility
{
public:
    NodePointer<T> obtainRoot();
protected:
    NodePointer<T> currentNode;
};

template<typename T>
NodePointer<T> NodeUtility<T>::obtainRoot(){
    auto rootFinder = RootFinder<T>(currentNode);
    rootFinder.find();
    return rootFinder.getFound();
}

#endif //SDIZO_1_NODEUTILITY_H
