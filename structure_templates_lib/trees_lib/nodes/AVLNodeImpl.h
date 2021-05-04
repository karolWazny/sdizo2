#ifndef SDIZO_1_AVLNODEIMPL_H
#define SDIZO_1_AVLNODEIMPL_H

#include "trees_lib/nodes/AVLNode.h"
#include "AVLSentinel.h"

template <typename T>
class AVLNodeImpl : public AVLNode<T>
{
public:
    explicit AVLNodeImpl(Node<T>*);
    AVLNodeImpl() = delete;

    T getKey()override;
    void setParent(NodePointer<T>) override;
    NodePointer<T> getParent() override;
    void setLeft(NodePointer<T>) override;
    NodePointer<T> getLeft() override;
    void setRight(NodePointer<T>) override;
    NodePointer<T> getRight() override;
    bool isNil() override;
    std::string toString() override;

    char getBalanceFactor() override;
    void setBalanceFactor(char factor) override;

private:
    std::unique_ptr<Node<T>> node;
    char balanceFactor;

    static NodePointer<T> sentinel;
};

template <typename T>
NodePointer<T> AVLNodeImpl<T>::sentinel = AVLSentinel<T>::getInstance();

template<typename T>
AVLNodeImpl<T>::AVLNodeImpl(Node <T> *nodeImpl) {
    node = std::unique_ptr<Node<T>>(nodeImpl);
    node->setParent(sentinel);
    node->setLeft(sentinel);
    node->setRight(sentinel);
    balanceFactor = 0;
}

template<typename T>
T AVLNodeImpl<T>::getKey() {
    return node->getKey();
}

template<typename T>
void AVLNodeImpl<T>::setParent(NodePointer <T> parent) {
    if(parent)
        node->setParent(parent);
    else
        node->setParent(sentinel);
}

template<typename T>
NodePointer <T> AVLNodeImpl<T>::getParent() {
    return node->getParent();
}

template<typename T>
void AVLNodeImpl<T>::setLeft(NodePointer <T> left) {
    if(left)
        node->setLeft(left);
    else
        node->setLeft(sentinel);
}

template<typename T>
NodePointer <T> AVLNodeImpl<T>::getLeft() {
    return node->getLeft();
}

template<typename T>
void AVLNodeImpl<T>::setRight(NodePointer <T> right) {
    if(right)
        node->setRight(right);
    else
        node->setRight(sentinel);
}

template<typename T>
NodePointer <T> AVLNodeImpl<T>::getRight() {
    return node->getRight();
}

template<typename T>
bool AVLNodeImpl<T>::isNil() {
    return node->isNil();
}

template<typename T>
std::string AVLNodeImpl<T>::toString() {
    std::string out;
    switch(balanceFactor)
    {
        case -1:
            out += "-";
            break;
        case 0:
            out += "*";
            break;
        case 1:
            out += "+";
            break;
        default:
            out += std::to_string(balanceFactor);
            break;
    }
    out += "|";
    out += node->toString();
    return out;
}

template<typename T>
char AVLNodeImpl<T>::getBalanceFactor() {
    return balanceFactor;
}

template<typename T>
void AVLNodeImpl<T>::setBalanceFactor(char factor) {
    this->balanceFactor = factor;
}

#endif //SDIZO_1_AVLNODEIMPL_H
