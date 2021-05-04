#ifndef SDIZO_1_SENTINEL_H
#define SDIZO_1_SENTINEL_H

#include "Node.h"

template <typename T>
class Sentinel : public Node<T>
{
public:
    T getKey();
    void setParent(NodePointer<T>);
    NodePointer<T> getParent();
    void setLeft(NodePointer<T>) override;
    NodePointer<T> getLeft() override;
    void setRight(NodePointer<T>) override;
    NodePointer<T> getRight() override;
    bool isNil() override;
    std::string toString() override;

    static NodePointer<T> getInstance();
private:
    static T key;
    static NodePointer<T> instance;
};

template <typename T>
NodePointer<T> Sentinel<T>::instance = NodePointer<T>(new Sentinel<T>());

template <typename T>
T Sentinel<T>::key = NULL;

template<typename T>
NodePointer<T> Sentinel<T>::getParent() {
    return getInstance();
}

template<typename T>
NodePointer<T> Sentinel<T>::getLeft() {
    return getInstance();
}

template<typename T>
NodePointer<T> Sentinel<T>::getRight() {
    return getInstance();
}

template<typename T>
T Sentinel<T>::getKey() {
    return key;
}

template<typename T>
bool Sentinel<T>::isNil() {
    return true;
}

template<typename T>
void Sentinel<T>::setLeft(NodePointer<T>) {
    //nil z definicji jest bezdzietny
}

template<typename T>
void Sentinel<T>::setRight(NodePointer<T>) {
    //nil z definicji jest bezdzietny
}

template<typename T>
void Sentinel<T>::setParent(NodePointer<T> parent) {

}

template<typename T>
NodePointer<T> Sentinel<T>::getInstance() {
    return instance;
}

template<typename T>
std::string Sentinel<T>::toString() {
    return "NIL";
}

#endif //SDIZO_1_SENTINEL_H
