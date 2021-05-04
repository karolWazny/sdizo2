#ifndef SDIZO_1_NODEREPLACER_H
#define SDIZO_1_NODEREPLACER_H

#include "trees_lib/nodes/Node.h"
#include "Side.h"
#include "NodeUtility.h"

template <typename T>
class NodeReplacer : public NodeUtility<T>
{
public:
    explicit NodeReplacer(NodePointer<T> nodeToReplace);
    void replaceWithNode(NodePointer<T> replacementNode);
private:
    void replace();

    NodePointer<T> replacement;
};

template<typename T>
NodeReplacer<T>::NodeReplacer(NodePointer<T> nodeToReplace) {
    this->currentNode = nodeToReplace;
}

template<typename T>
void NodeReplacer<T>::replaceWithNode(NodePointer<T> replacementNode) {
    this->replacement = replacementNode;
    replace();
}

template<typename T>
void NodeReplacer<T>::replace() {
    auto parent = currentNode->getParent();
    Side nodeToReplaceSide= Side::RIGHT;
    if(parent->getLeft() == currentNode)
    {
        nodeToReplaceSide = Side::LEFT;
    }
    if(!parent->isNil())
    {
        parent->setSide(replacement, nodeToReplaceSide);
    }
    replacement->setParent(parent);

    if(!replacement->isNil())
    {
        auto left = currentNode->getLeft();
        replacement->setLeft(left);
        left->setParent(replacement);

        auto right = currentNode->getRight();
        replacement->setRight(right);
        right->setParent(replacement);

        currentNode = replacement;
    }
}

#endif //SDIZO_1_NODEREPLACER_H
