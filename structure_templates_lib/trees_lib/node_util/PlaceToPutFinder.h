#ifndef SDIZO_1_PLACETOPUTFINDER_H
#define SDIZO_1_PLACETOPUTFINDER_H

#include "trees_lib/node_util/NodeFinder.h"
#include "Side.h"


template <typename T>
class PlaceToPutFinder : public NodeFinder<T>
{
public:
    explicit PlaceToPutFinder(NodePointer<T> initialNode);
    NodePointer<T> find();
    NodePointer<T> getFound();
    bool nodeFound();

    void setKeyToBePut(T key);
    Side getPlaceSide();

private:
    bool nodeWasFound;
    NodePointer<T> currentNode;
    T currentNodeKey;
    NodePointer<T> currentChild;
    Side currentChildSide;
    T keyToBePut;
};

template<typename T>
PlaceToPutFinder<T>::PlaceToPutFinder(NodePointer<T> initialNode) {
    currentNode = initialNode;
    nodeWasFound = false;
}

template<typename T>
void PlaceToPutFinder<T>::setKeyToBePut(T key) {
    keyToBePut = key;
}

template<typename T>
NodePointer<T> PlaceToPutFinder<T>::find() {
    currentNodeKey = currentNode->getKey();
    if(currentNodeKey > keyToBePut)
    {
        currentChild = currentNode->getLeft();
        currentChildSide = Side::LEFT;
    }
    else
    {
        currentChild = currentNode->getRight();
        currentChildSide = Side::RIGHT;
    }
    while(!currentChild->isNil()){
        currentNode = currentChild;
        currentNodeKey = currentNode->getKey();
        if(currentNodeKey > keyToBePut)
        {
            currentChild = currentNode->getLeft();
            currentChildSide = Side::LEFT;
        }
        else
        {
            currentChild = currentNode->getRight();
            currentChildSide = Side::RIGHT;
        }
    }
    nodeWasFound = true;
    return currentNode;
}

template<typename T>
NodePointer<T> PlaceToPutFinder<T>::getFound() {
    return currentNode;
}

template<typename T>
bool PlaceToPutFinder<T>::nodeFound() {
    return nodeWasFound;
}

template<typename T>
Side PlaceToPutFinder<T>::getPlaceSide() {
    return currentChildSide;
}

#endif //SDIZO_1_PLACETOPUTFINDER_H
