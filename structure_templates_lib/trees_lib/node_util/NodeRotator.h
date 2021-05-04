#ifndef SDIZO_1_NODEROTATOR_H
#define SDIZO_1_NODEROTATOR_H

#include "NodeUtility.h"
#include "trees_lib/nodes/Node.h"

template <typename T>
class NodeRotator : public NodeUtility<T>
{
public:
    void rotateRight(NodePointer<T> nodeToRotate);
    void rotateLeft(NodePointer<T> nodeToRotate);
    void rotate(NodePointer<T> node, Side rotationDirection);
private:
    void rotate(NodePointer<T> nodeToRotate);

    Side direction;
    NodePointer<T> nodeToRotate;
};

template<typename T>
void NodeRotator<T>::rotateRight(NodePointer<T> node) {
    rotate(node, Side::RIGHT);
}

template<typename T>
void NodeRotator<T>::rotateLeft(NodePointer<T> node) {
    rotate(node, Side::LEFT);
}

template<typename T>
void NodeRotator<T>::rotate(NodePointer<T> node) {
    this->nodeToRotate = node;
    auto child = nodeToRotate->get(!direction);
    auto parent = nodeToRotate->getParent();
    child->setParent(parent);
    if(nodeToRotate == parent->getLeft())
        parent->setLeft(child);
    else
        parent->setRight(child);
    auto buffer = child->get(direction);
    child->setSide(nodeToRotate, direction);
    nodeToRotate->setSide(buffer, !direction);
    buffer->setParent(nodeToRotate);
    nodeToRotate->setParent(child);
    currentNode = nodeToRotate;
}

template<typename T>
void NodeRotator<T>::rotate(NodePointer<T> node, Side rotationDirection) {
    this->direction = rotationDirection;
    rotate(node);
}

#endif //SDIZO_1_NODEROTATOR_H
