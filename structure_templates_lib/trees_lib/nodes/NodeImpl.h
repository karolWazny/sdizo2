#ifndef SDIZO_1_NODEIMPL_H
#define SDIZO_1_NODEIMPL_H

#include "Node.h"
#include "Sentinel.h"

template <typename T>
class NodeImpl : public Node<T>
{
public:
    explicit NodeImpl(T key);
    T getKey()override;
    void setParent(NodePointer<T>) override;
    NodePointer<T> getParent() override;
    void setLeft(NodePointer<T>) override;
    NodePointer<T> getLeft() override;
    void setRight(NodePointer<T>) override;
    NodePointer<T> getRight() override;
    bool isNil() override;
    std::string toString() override;
private:
    T key;
    NodePointer<T> right;
    NodePointer<T> left;
    NodeWeakPtr<T> parent;
    static NodePointer<T> sentinel;
};

template <typename T>
NodePointer<T> NodeImpl<T>::sentinel = Sentinel<T>::getInstance();


template<typename T>
NodeImpl<T>::NodeImpl(T key) {
    this->key = key;
    right = sentinel;
    left = sentinel;
    parent = sentinel;
}

template<typename T>
T NodeImpl<T>::getKey() {
    return key;
}

template<typename T>
NodePointer<T> NodeImpl<T>::getParent() {
    return parent.lock();
}

template<typename T>
NodePointer<T> NodeImpl<T>::getLeft() {
    return left;
}

template<typename T>
NodePointer<T> NodeImpl<T>::getRight() {
    return right;
}

template<typename T>
bool NodeImpl<T>::isNil() {
    return false;
}

template<typename T>
void NodeImpl<T>::setLeft(NodePointer<T> node) {
    if(node)
        this->left = node;
    else
        this->left = sentinel;
}

template<typename T>
void NodeImpl<T>::setRight(NodePointer<T> node) {
    if(node)
        this->right = node;
    else
        this->right = sentinel;
}

template<typename T>
void NodeImpl<T>::setParent(NodePointer<T> node) {
    if(node)
        this->parent = node;
    else
        this->parent = sentinel;
}

template<typename T>
std::string NodeImpl<T>::toString() {
    return std::to_string(getKey());
}

#endif //SDIZO_1_NODEIMPL_H
