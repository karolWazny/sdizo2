#ifndef SDIZO_1_KEYFINDER_H
#define SDIZO_1_KEYFINDER_H

#include "trees_lib/node_util/NodeFinder.h"

template <typename T>
class KeyFinder : public NodeFinder<T>
{
public:
    KeyFinder(NodePointer<T> startingNode);
    void setDesiredKey(T key);

    NodePointer<T> find() override;
    NodePointer<T> getFound() override;
    bool nodeFound() override;
private:
    NodePointer<T> currentNode;
    T currentKey;
    T desiredKey;
    bool nodeWasFound;
};

template<typename T>
KeyFinder<T>::KeyFinder(NodePointer<T> startingNode) {
    this->currentNode = startingNode;
    nodeWasFound = false;
}


template<typename T>
void KeyFinder<T>::setDesiredKey(T key) {
    this->desiredKey = key;
}

template<typename T>
NodePointer<T> KeyFinder<T>::find() {
    while(!currentNode->isNil())
    {
        currentKey = currentNode->getKey();
        if(currentKey == desiredKey)
        {
            nodeWasFound = true;
            break;
        }
        else if(currentKey > desiredKey)
        {
            currentNode = currentNode->getLeft();
            continue;
        }
        else
            currentNode = currentNode->getRight();
    }

    return currentNode;
}

template<typename T>
NodePointer<T> KeyFinder<T>::getFound() {
    return currentNode;
}

template<typename T>
bool KeyFinder<T>::nodeFound() {
    return nodeWasFound;
}

#endif //SDIZO_1_KEYFINDER_H
