#ifndef SDIZO_1_RBNODEIMPL_H
#define SDIZO_1_RBNODEIMPL_H

#include "RBNode.h"
#include "RBSentinel.h"


//todo tylko do testów
#include <iostream>

template <typename T>
class RBNodeImpl : public RBNode<T>
{
public:
    RBNodeImpl(Node<T>*, Colored*);

    bool isBlack() override;
    bool isRed() override;
    void paintBlack() override;
    void paintRed() override;

    T getKey()override;
    void setParent(NodePointer<T>) override;
    NodePointer<T> getParent() override;
    void setLeft(NodePointer<T>) override;
    NodePointer<T> getLeft() override;
    void setRight(NodePointer<T>) override;
    NodePointer<T> getRight() override;
    bool isNil() override;
    std::string toString() override;
#if DEBUG
    int checkAmountOfBlackToLeaves() override;
#endif

private:
    RBNodePtr<T> sentinel();
    std::unique_ptr<Node<T>> node;
    std::unique_ptr<Colored> colored;

};

template<typename T>
RBNodePtr<T> RBNodeImpl<T>::sentinel() {
    return RBSentinel<T>::getInstance();
}

template<typename T>
RBNodeImpl<T>::RBNodeImpl(Node<T> * nodeImpl, Colored * coloredImpl) {
    node = std::unique_ptr<Node<T>>(nodeImpl);
    node->setRight(sentinel());
    node->setLeft(sentinel());
    node->setParent(sentinel());
    colored = std::unique_ptr<Colored>(coloredImpl);
    colored->paintRed();
}

template<typename T>
bool RBNodeImpl<T>::isBlack() {
    return colored->isBlack();
}

template<typename T>
bool RBNodeImpl<T>::isRed() {
    return colored->isRed();
}

template<typename T>
void RBNodeImpl<T>::paintBlack() {
    colored->paintBlack();
}

template<typename T>
void RBNodeImpl<T>::paintRed() {
    colored->paintRed();
}

template<typename T>
T RBNodeImpl<T>::getKey() {
    return node->getKey();
}

template<typename T>
void RBNodeImpl<T>::setParent(NodePointer<T> parent) {
    if(!parent)
        node->setParent(sentinel());
    else
    node->setParent(parent);
}

template<typename T>
NodePointer<T> RBNodeImpl<T>::getParent() {
    return node->getParent();
}

template<typename T>
void RBNodeImpl<T>::setLeft(NodePointer<T> left) {
    if(!left)
        node->setLeft(sentinel());
    else
    node->setLeft(left);
}

template<typename T>
NodePointer<T> RBNodeImpl<T>::getLeft() {
    return node->getLeft();
}

template<typename T>
void RBNodeImpl<T>::setRight(NodePointer<T> right) {
    if(!right)
        node->setRight(sentinel());
    else
    node->setRight(right);
}

template<typename T>
NodePointer<T> RBNodeImpl<T>::getRight() {
    return node->getRight();
}

template<typename T>
bool RBNodeImpl<T>::isNil() {
    return node->isNil();
}

#if DEBUG
template<typename T>
int RBNodeImpl<T>::checkAmountOfBlackToLeaves() {
    int leftNumber, rightNumber;
    leftNumber = rbcast(getLeft())->checkAmountOfBlackToLeaves();
    rightNumber = rbcast(getRight())->checkAmountOfBlackToLeaves();
    if(leftNumber != rightNumber)
    {
        std::cout << "My key: "<<std::to_string(getKey())<<", left blacks: "
            <<std::to_string(leftNumber)<<", right blacks: "
            <<std::to_string(rightNumber)<<std::endl;
        throw "Niezachowane własności drzewa!";
    }
    if(isBlack())
        leftNumber++;
    return leftNumber;
}
#endif
template<typename T>
std::string RBNodeImpl<T>::toString() {
    std::string output;
    output += (isBlack() ? "B" : "R");
    output += node->toString();
    return output;
}

#endif //SDIZO_1_RBNODEIMPL_H
