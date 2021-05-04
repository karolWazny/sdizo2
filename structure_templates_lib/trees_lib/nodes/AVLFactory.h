#ifndef SDIZO_1_AVLFACTORY_H
#define SDIZO_1_AVLFACTORY_H

#include "NodeFactory.h"
#include "NodeImpl.h"
#include "AVLNodeImpl.h"
#include "AVLSentinel.h"

template <typename T>
class AVLFactory : public NodeFactory<T>
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
NodePointer<T> AVLFactory<T>::makeNode(T key) {
    return NodePointer<T>(new AVLNodeImpl<T>(new NodeImpl<T>(key)));
}

template<typename T>
NodePointer<T> AVLFactory<T>::makeSentinel(void) {
    return AVLSentinel<T>::getInstance();
}

template<typename T>
NodePointer<T> AVLFactory<T>::makeSentinel(T) {
    return AVLSentinel<T>::getInstance();
}

template<typename T>
NodePointer<T> AVLFactory<T>::createNode(T key) {
    return makeNode(key);
}

template<typename T>
NodePointer<T> AVLFactory<T>::createSentinel(NodePointer<T> parent) {
    return makeSentinel();
}

template<typename T>
NodePointer<T> AVLFactory<T>::createSentinel(void) {
    return makeSentinel();
}

#endif //SDIZO_1_AVLFACTORY_H
