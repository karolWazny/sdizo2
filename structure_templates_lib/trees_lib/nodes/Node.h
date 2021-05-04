//
// Created by admin on 19.03.2021.
//

#ifndef SDIZO_1_NODE_H
#define SDIZO_1_NODE_H

#include <memory>
#include <string>
#include "trees_lib/node_util/Side.h"

template <typename T>
class Node;

template <typename T>
using NodePointer = std::shared_ptr<Node<T>>;

template <typename T>
using NodeWeakPtr = std::weak_ptr<Node<T>>;

template <typename T>
class Node
{
public:
    virtual T getKey() = 0;
    virtual void setParent(NodePointer<T>) = 0;
    virtual NodePointer<T> getParent() = 0;
    virtual void setLeft(NodePointer<T>) = 0;
    virtual NodePointer<T> getLeft() = 0;
    virtual void setRight(NodePointer<T>) = 0;
    virtual NodePointer<T> getRight() = 0;
    virtual bool isNil() = 0;
    virtual std::string toString() = 0;
    NodePointer<T> get(Side side);
    void setSide(NodePointer<T> node, Side side);
};

template<typename T>
NodePointer<T> Node<T>::get(Side side) {
    if(side == Side::RIGHT)
        return getRight();
    else
        return getLeft();
}

template<typename T>
void Node<T>::setSide(NodePointer<T> node, Side side) {
    if(side == Side::RIGHT)
        return setRight(node);
    else
        return setLeft(node);
}

#endif //SDIZO_1_NODE_H
