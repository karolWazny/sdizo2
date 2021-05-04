#ifndef SDIZO_1_RBSENTINEL_H
#define SDIZO_1_RBSENTINEL_H

#include "RBNode.h"
#include "Sentinel.h"
#include "trees_lib/colors/Black.h"

template <typename T>
class RBSentinel : public RBNode<T>
{
public:
    RBSentinel();
    RBSentinel(NodePointer<T>& node);

    virtual T getKey();
    virtual void setParent(NodePointer<T>);
    virtual NodePointer<T> getParent();
    virtual void setLeft(NodePointer<T>);
    virtual NodePointer<T> getLeft();
    virtual void setRight(NodePointer<T>);
    virtual NodePointer<T> getRight();
    virtual bool isNil();
    std::string toString() override;

    virtual bool isBlack();
    virtual bool isRed();
    virtual void paintBlack();
    virtual void paintRed();
#if DEBUG
    int checkAmountOfBlackToLeaves() override;
#endif
    static RBNodePtr<T> getInstance();

private:
    static T key;
    Black black;

    NodePointer<T>& parent;

    NodePointer<T> parentPointer;

    static NodePointer<T> instance;
};

template <typename T>
NodePointer<T> RBSentinel<T>::instance = RBNodePtr<T>(new RBSentinel<T>());

template <typename T>
T RBSentinel<T>::key = NULL;

template<typename T>
RBSentinel<T>::RBSentinel(NodePointer<T>& node):parent(parentPointer) {
    this->black = Black();
    parent = node;
}

template<typename T>
RBSentinel<T>::RBSentinel():parent(instance) {
    this->black = Black();
}

template<typename T>
T RBSentinel<T>::getKey() {
    return key;
}

template<typename T>
void RBSentinel<T>::setParent(NodePointer<T> node) {
    if(parent != instance)
        parent = node;
}

template<typename T>
NodePointer<T> RBSentinel<T>::getParent() {
    return parent;
}

template<typename T>
void RBSentinel<T>::setLeft(NodePointer<T>) {

}

template<typename T>
NodePointer<T> RBSentinel<T>::getLeft() {
    return getInstance();
}

template<typename T>
void RBSentinel<T>::setRight(NodePointer<T>) {

}

template<typename T>
NodePointer<T> RBSentinel<T>::getRight() {
    return getInstance();
}

template<typename T>
bool RBSentinel<T>::isNil() {
    return true;
}

template<typename T>
RBNodePtr<T> RBSentinel<T>::getInstance() {
    return rbcast(instance);
}

template<typename T>
bool RBSentinel<T>::isBlack() {
    return black.isBlack();
}

template<typename T>
bool RBSentinel<T>::isRed() {
    return black.isRed();
}

template<typename T>
void RBSentinel<T>::paintBlack() {
    black.paintBlack();
}

template<typename T>
void RBSentinel<T>::paintRed() {
    black.paintRed();
}

#if DEBUG
template<typename T>
int RBSentinel<T>::checkAmountOfBlackToLeaves() {
    return 1;
}
#endif

template<typename T>
std::string RBSentinel<T>::toString() {
    return "B-NIL";
}

#endif //SDIZO_1_RBSENTINEL_H
