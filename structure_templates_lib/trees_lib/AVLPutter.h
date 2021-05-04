#ifndef SDIZO_1_AVLPUTTER_H
#define SDIZO_1_AVLPUTTER_H

#include "node_util/NodeUtility.h"
#include "node_util/NodePutter.h"
#include "nodes/AVLFactory.h"
#include "AVLPutRestorer.h"

template <typename T>
class AVLPutter : public NodeUtility<T>
{
public:
    explicit AVLPutter(NodePointer<T> root);
    void put(T key);
private:
    NodePointer<T> root;
};

template<typename T>
AVLPutter<T>::AVLPutter(NodePointer<T> root) {
    this->root = root;
}

template<typename T>
void AVLPutter<T>::put(T key) {
    auto putter = NodePutter<T>(root, new AVLFactory<T>());
    putter.put(key);
    auto freshNode = putter.getFreshNode();
    auto restorer = AVLPutRestorer<T>();
    restorer.restoreFrom(avlcast(freshNode));
    if(freshNode->getParent()->isNil())
        freshNode->setParent(nullptr);
    currentNode = putter.obtainRoot();
}

#endif //SDIZO_1_AVLPUTTER_H
