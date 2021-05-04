#ifndef SDIZO_1_ROOTFINDER_H
#define SDIZO_1_ROOTFINDER_H

#include "trees_lib/node_util/NodeFinder.h"

template <typename T>
class RootFinder
{
public:
    explicit RootFinder(NodePointer<T> initialNode);

    NodePointer<T> find();
    NodePointer<T> getFound();
    bool nodeFound();
private:
    bool nodeWasFound;
    NodePointer<T> currentNode;
};

template<typename T>
RootFinder<T>::RootFinder(NodePointer<T> initialNode) {
    currentNode = initialNode;
    nodeWasFound = false;
}

template<typename T>
NodePointer<T> RootFinder<T>::find() {
    auto temp = currentNode->getParent();
    while(!temp->isNil())
    {
        currentNode = temp;
        temp = currentNode->getParent();
    }
    nodeWasFound = true;
    return getFound();
}

template<typename T>
NodePointer<T> RootFinder<T>::getFound() {
    return currentNode;
}

template<typename T>
bool RootFinder<T>::nodeFound() {
    return nodeWasFound;
}

#endif //SDIZO_1_ROOTFINDER_H
