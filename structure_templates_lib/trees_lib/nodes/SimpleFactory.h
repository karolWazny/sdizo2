#ifndef SDIZO_1_SIMPLEFACTORY_H
#define SDIZO_1_SIMPLEFACTORY_H

#include "Node.h"
#include "NodeImpl.h"
#include "Sentinel.h"

#include "NodeFactory.h"

//todo rozwiązać zależność cykliczną

template <typename T>
class SimpleFactory : public NodeFactory<T>
{
public:
    static NodePointer<T> makeNode(T);
    static NodePointer<T> makeSentinel(T);
    static NodePointer<T> makeSentinel(void);

    NodePointer<T> createNode(T) override;
    NodePointer<T> createSentinel(NodePointer<T> parent) override;
    NodePointer<T> createSentinel(void) override;
};

template<typename T>
NodePointer<T> SimpleFactory<T>::makeNode(T key) {
    return NodePointer<T>(new NodeImpl<T>(key));
}

template<typename T>
NodePointer<T> SimpleFactory<T>::makeSentinel(void) {
    return Sentinel<T>::getInstance();
}

template<typename T>
NodePointer<T> SimpleFactory<T>::makeSentinel(T) {
    return NodePointer<T>();
}

template<typename T>
NodePointer<T> SimpleFactory<T>::createNode(T key) {
    return makeNode(key);
}

template<typename T>
NodePointer<T> SimpleFactory<T>::createSentinel(NodePointer<T> parent) {
    return makeSentinel();
}

template<typename T>
NodePointer<T> SimpleFactory<T>::createSentinel(void) {
    return makeSentinel();
}

#endif //SDIZO_1_SIMPLEFACTORY_H
