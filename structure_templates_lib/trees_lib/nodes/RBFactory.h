#ifndef SDIZO_1_RBFACTORY_H
#define SDIZO_1_RBFACTORY_H

#include "Node.h"
#include "NodeImpl.h"
#include "RBSentinel.h"
#include "RBNodeImpl.h"
#include "trees_lib/colors/RedBlack.h"

#include "NodeFactory.h"

template <typename T>
class RBFactory : public NodeFactory<T>
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
NodePointer<T> RBFactory<T>::makeNode(T key) {
    return NodePointer<T>(new RBNodeImpl<T>(new NodeImpl<T>(key), new RedBlack()));
}

template<typename T>
NodePointer<T> RBFactory<T>::makeSentinel(void) {
    return RBSentinel<T>::getInstance();
}

template<typename T>
NodePointer<T> RBFactory<T>::makeSentinel(T) {
    return NodePointer<T>();
}

template<typename T>
NodePointer<T> RBFactory<T>::createNode(T key) {
    return makeNode(key);
}

template<typename T>
NodePointer<T> RBFactory<T>::createSentinel(NodePointer<T> parent) {
    return NodePointer<T>(new RBSentinel<T>(parent));
}

template<typename T>
NodePointer<T> RBFactory<T>::createSentinel(void) {
    return makeSentinel();
}

#endif //SDIZO_1_RBFACTORY_H
