#ifndef SDIZO_1_CONSEQUENTFINDER_H
#define SDIZO_1_CONSEQUENTFINDER_H

#include "trees_lib/nodes/Node.h"
#include "trees_lib/node_util/NodeFinder.h"

template <typename T>
class ConsequentFinder : public NodeFinder<T>
{
public:
    explicit ConsequentFinder(NodePointer<T> initialNode);

    NodePointer<T> find();
    NodePointer<T> getFound();
    bool nodeFound();
    Side getConsequentSide();

private:
    NodePointer<T> obtainCurrentChildOnTheSide(Side side);

    NodePointer<T> currentNode;
    Side consequentSide;
    bool nodeWasFound;
};

template<typename T>
ConsequentFinder<T>::ConsequentFinder(NodePointer<T> initialNode) {
    currentNode = initialNode;
}

template<typename T>
NodePointer<T> ConsequentFinder<T>::find() {
    auto buffer = currentNode->getRight();
    consequentSide = Side::RIGHT;
    if(buffer->isNil())
    {
        consequentSide = Side::LEFT;
        buffer = currentNode->getLeft();
    }
    if(buffer->isNil())
    {
        currentNode = buffer;
    }
    while(!buffer->isNil())
    {
        currentNode = buffer;
        buffer = obtainCurrentChildOnTheSide(!consequentSide);
    }
    return currentNode;
}

template<typename T>
NodePointer<T> ConsequentFinder<T>::obtainCurrentChildOnTheSide(Side side) {
    return (side == Side::LEFT ? currentNode->getLeft() : currentNode->getRight());
}

template<typename T>
NodePointer<T> ConsequentFinder<T>::getFound() {
    return currentNode;
}

template<typename T>
bool ConsequentFinder<T>::nodeFound() {
    return nodeWasFound;
}

template<typename T>
Side ConsequentFinder<T>::getConsequentSide() {
    return consequentSide;
}

#endif //SDIZO_1_CONSEQUENTFINDER_H
