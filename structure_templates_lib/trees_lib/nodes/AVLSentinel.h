#ifndef SDIZO_1_AVLSENTINEL_H
#define SDIZO_1_AVLSENTINEL_H

#include "trees_lib/nodes/AVLNode.h"

template <typename T>
class AVLSentinel : public AVLNode<T>
{
public:
     T getKey() override;
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

     static NodePointer<T> getInstance();

private:
    static T key;
    static NodePointer<T> instance;
};

template <typename T>
NodePointer<T> AVLSentinel<T>::instance = AVLNodePtr<T>(new AVLSentinel<T>());

template <typename T>
T AVLSentinel<T>::key = NULL;

template<typename T>
T AVLSentinel<T>::getKey() {
    return key;
}

template<typename T>
void AVLSentinel<T>::setParent(NodePointer <T>) {

}

template<typename T>
NodePointer <T> AVLSentinel<T>::getParent() {
    return instance;
}

template<typename T>
void AVLSentinel<T>::setLeft(NodePointer <T>) {

}

template<typename T>
NodePointer <T> AVLSentinel<T>::getLeft() {
    return instance;
}

template<typename T>
void AVLSentinel<T>::setRight(NodePointer <T>) {

}

template<typename T>
NodePointer <T> AVLSentinel<T>::getRight() {
    return instance;
}

template<typename T>
bool AVLSentinel<T>::isNil() {
    return true;
}

template<typename T>
char AVLSentinel<T>::getBalanceFactor() {
    return 0;
}

template<typename T>
void AVLSentinel<T>::setBalanceFactor(char factor) {

}

template<typename T>
NodePointer<T> AVLSentinel<T>::getInstance() {
    return instance;
}

template<typename T>
std::string AVLSentinel<T>::toString() {
    return std::string();
}


#endif //SDIZO_1_AVLSENTINEL_H
